#include <Ogre.h>
#include <OgreArchiveManager.h>
#include <OgreFileSystem.h>
#include <OgreHlms.h>
#include <OgreHlmsUnlit.h>
#include <OgreHlmsPbs.h>
#include <OgrePlatform.h>
#include <OgreWindowEventUtilities.h>
#include <OgreCompositorManager2.h>
#include <OgreWindow.h>
#include <OgreItem.h>
#include <OgreMesh.h>
#include <OgreMeshManager.h>
#include <OgreMesh2.h>
#include <OgreMeshManager2.h>
#include <OgreMesh2Serializer.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#   include "OSX/macUtils.h"
#endif
static void registerHlms( void )
{
    using namespace Ogre;

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    // Note:  macBundlePath works for iOS too. It's misnamed.
    const String resourcePath = Ogre::macResourcesPath();
#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    const String resourcePath = Ogre::macBundlePath() + "/";
#else
    String resourcePath = "../config/";
#endif

    ConfigFile cf;
    cf.load( resourcePath + "resources2.cfg" );

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    String rootHlmsFolder = macBundlePath() + '/' + cf.getSetting( "DoNotUseAsResource", "Hlms", "" );
#else
    String rootHlmsFolder = cf.getSetting( "DoNotUseAsResource", "Hlms", "" );
#endif

    if( rootHlmsFolder.empty() )
        rootHlmsFolder = "./";
    else if( *( rootHlmsFolder.end() - 1 ) != '/' )
        rootHlmsFolder += "/";

    // At this point rootHlmsFolder should be a valid path to the Hlms data folder

    HlmsUnlit *hlmsUnlit = 0;
    HlmsPbs *hlmsPbs = 0;

    // For retrieval of the paths to the different folders needed
    String mainFolderPath;
    StringVector libraryFoldersPaths;
    StringVector::const_iterator libraryFolderPathIt;
    StringVector::const_iterator libraryFolderPathEn;

    ArchiveManager &archiveManager = ArchiveManager::getSingleton();

    {
        // Create & Register HlmsUnlit
        // Get the path to all the subdirectories used by HlmsUnlit
        HlmsUnlit::getDefaultPaths( mainFolderPath, libraryFoldersPaths );
        Archive *archiveUnlit =
            archiveManager.load( rootHlmsFolder + mainFolderPath, "FileSystem", true );
        ArchiveVec archiveUnlitLibraryFolders;
        libraryFolderPathIt = libraryFoldersPaths.begin();
        libraryFolderPathEn = libraryFoldersPaths.end();
        while( libraryFolderPathIt != libraryFolderPathEn )
        {
            Archive *archiveLibrary =
                archiveManager.load( rootHlmsFolder + *libraryFolderPathIt, "FileSystem", true );
            archiveUnlitLibraryFolders.push_back( archiveLibrary );
            ++libraryFolderPathIt;
        }

        // Create and register the unlit Hlms
        hlmsUnlit = OGRE_NEW HlmsUnlit( archiveUnlit, &archiveUnlitLibraryFolders );
        Root::getSingleton().getHlmsManager()->registerHlms( hlmsUnlit );
    }

    {
        // Create & Register HlmsPbs
        // Do the same for HlmsPbs:
        HlmsPbs::getDefaultPaths( mainFolderPath, libraryFoldersPaths );
        Archive *archivePbs = archiveManager.load( rootHlmsFolder + mainFolderPath, "FileSystem", true );

        // Get the library archive(s)
        ArchiveVec archivePbsLibraryFolders;
        libraryFolderPathIt = libraryFoldersPaths.begin();
        libraryFolderPathEn = libraryFoldersPaths.end();
        while( libraryFolderPathIt != libraryFolderPathEn )
        {
            Archive *archiveLibrary =
                archiveManager.load( rootHlmsFolder + *libraryFolderPathIt, "FileSystem", true );
            archivePbsLibraryFolders.push_back( archiveLibrary );
            ++libraryFolderPathIt;
        }

        // Create and register
        hlmsPbs = OGRE_NEW HlmsPbs( archivePbs, &archivePbsLibraryFolders );
        Root::getSingleton().getHlmsManager()->registerHlms( hlmsPbs );
    }

    RenderSystem *renderSystem = Root::getSingletonPtr()->getRenderSystem();
    if( renderSystem->getName() == "Direct3D11 Rendering Subsystem" )
    {
        // Set lower limits 512kb instead of the default 4MB per Hlms in D3D 11.0
        // and below to avoid saturating AMD's discard limit (8MB) or
        // saturate the PCIE bus in some low end machines.
        bool supportsNoOverwriteOnTextureBuffers;
        renderSystem->getCustomAttribute( "MapNoOverwriteOnDynamicBufferSRV",
                                          &supportsNoOverwriteOnTextureBuffers );

        if( !supportsNoOverwriteOnTextureBuffers )
        {
            hlmsPbs->setTextureBufferDefaultSize( 512 * 1024 );
            hlmsUnlit->setTextureBufferDefaultSize( 512 * 1024 );
        }
    }
}

class MyWindowEventListener : public Ogre::WindowEventListener
{
    bool mQuit;

public:
    MyWindowEventListener() : mQuit( false ) {}
    virtual void windowClosed( Ogre::Window *rw ) { mQuit = true; }

    bool getQuit( void ) const { return mQuit; }
};

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR strCmdLine, INT nCmdShow )
#else
int main( int argc, const char *argv[] )
#endif
{
    using namespace Ogre;

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    const String pluginsFolder = macResourcesPath();
    const String writeAccessFolder = macLogPath();
#else
    const String pluginsFolder = "./";
    const String writeAccessFolder = pluginsFolder;
#endif

#ifndef OGRE_STATIC_LIB
#    if OGRE_DEBUG_MODE && \
        !( ( OGRE_PLATFORM == OGRE_PLATFORM_APPLE ) || ( OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS ) )
    const char *pluginsFile = "plugins_d.cfg";
#    else
    const char *pluginsFile = "../config/plugins.cfg";
#    endif
#else
    const char *pluginsFile = 0; // TODO
#endif
    Root *root = OGRE_NEW Root( pluginsFolder + pluginsFile,     //
                                writeAccessFolder + "../config/ogre.cfg",  //
                                writeAccessFolder + "Ogre.log" );

    if( !root->showConfigDialog() )
        return -1;

    // Initialize Root
    root->getRenderSystem()->setConfigOption( "sRGB Gamma Conversion", "Yes" );
    // Window *window = root->initialise( true, "Tutorial 00: Basic" );
    root->initialise( false, "Tutorial 00: Basic" );

    Ogre::NameValuePairList params;
    params.insert ( std::make_pair ( "title", "Tutorial 00: Basic" ) );
    params.insert ( std::make_pair ( "vsync_method", "Render Ahead / FIFO" ) );
    params.insert ( std::make_pair ( "FSAA", "1" ) );
    params.insert ( std::make_pair ( "vsync", "Yes" ) );
    params.insert ( std::make_pair ( "reverse_depth", "Yes" ) );
    Window *window = Ogre::Root::getSingleton ().createRenderWindow ( "Tutorial 00: Basic", 1280, 720, false, &params );

    Ogre::ResourceGroupManager::getSingleton ().addResourceLocation ( "../data", "FileSystem", "General" );
    registerHlms();

    // Create SceneManager
    const size_t numThreads = 1u;
    SceneManager *sceneManager = root->createSceneManager( ST_GENERIC, numThreads, "ExampleSMInstance" );

    // Create & setup camera
    Camera *camera = sceneManager->createCamera( "Main Camera" );
    // Position it at 500 in Z direction
    camera->setPosition( Vector3( 0, 5, 15 ) );
    // Look back along -Z
    camera->lookAt( Vector3( 0, 0, 0 ) );
    camera->setNearClipDistance( 0.2f );
    camera->setFarClipDistance( 1000.0f );
    camera->setAutoAspectRatio( true );

    // Setup a basic compositor with a blue clear colour
    CompositorManager2 *compositorManager = root->getCompositorManager2();
    const String workspaceName( "Demo Workspace" );
    const ColourValue backgroundColour( 0.2f, 0.4f, 0.6f );
    compositorManager->createBasicWorkspaceDef( workspaceName, backgroundColour, IdString() );
    compositorManager->addWorkspace( sceneManager, window->getTexture(), camera, workspaceName, true );

    MyWindowEventListener myWindowEventListener;
    WindowEventUtilities::addWindowEventListener( window, &myWindowEventListener );

    camera->setPosition ( Ogre::Vector3 ( 0, 30, 100 ) );
    sceneManager->setForwardClustered ( true, 16, 8, 24, 96, 0, 0, 5, 500 );

    Ogre::HlmsManager *hlmsManager = root->getHlmsManager ();
    Ogre::Hlms *hlms = hlmsManager->getHlms ( Ogre::HLMS_PBS );

    // ---------------------------------------------------------------------------

    // Ogre::v1::MeshPtr v1Mesh;
    // Ogre::MeshPtr v2Mesh;

    // v1Mesh = Ogre::v1::MeshManager::getSingleton().load(
    //             "../data/cubev1.8.mesh", Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
    //             Ogre::v1::HardwareBuffer::HBU_STATIC, Ogre::v1::HardwareBuffer::HBU_STATIC );

    // bool halfPosition   = true;
    // bool halfUVs        = true;
    // bool useQtangents   = true;

    // v2Mesh = Ogre::MeshManager::getSingleton().createByImportingV1(
    //             "cube.mesh Imported", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    //             v1Mesh.get(), halfPosition, halfUVs, useQtangents );

    // v1Mesh->unload();

    // Ogre::Item *item = sceneManager->createItem( "cube.mesh Imported",
    //                                              Ogre::ResourceGroupManager::
    //                                              AUTODETECT_RESOURCE_GROUP_NAME,
    //                                              Ogre::SCENE_DYNAMIC );
    // Ogre::SceneNode *sceneNode = sceneManager->getRootSceneNode( Ogre::SCENE_DYNAMIC )->
    //         createChildSceneNode( Ogre::SCENE_DYNAMIC );
    // sceneNode->attachObject( item );
    // sceneNode->scale( 0.1f, 0.1f, 0.1f );

    // ---------------------------------------------------------------------------

    // Ogre::Item *cubeItem = sceneManager->createItem ( "../data/cube.mesh", Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME, Ogre::SCENE_DYNAMIC );
    Ogre::Item *cubeItem = sceneManager->createItem ( "cube.mesh", "General", Ogre::SCENE_DYNAMIC );
    cubeItem->setDatablock ( hlms->getDatablock ( "BaseWhite" ) );
    Ogre::SceneNode *cubeNode = sceneManager->getRootSceneNode ( Ogre::SCENE_DYNAMIC )->createChildSceneNode ( Ogre::SCENE_DYNAMIC );
    cubeNode->setPosition ( 0, 0, 0 );
    cubeNode->scale( 0.5f, 0.5f, 0.5f );
    cubeNode->attachObject ( cubeItem );

    bool bQuit = false;

    while( !bQuit )
    {
        WindowEventUtilities::messagePump();
        bQuit |= myWindowEventListener.getQuit();
        if( !bQuit )
            bQuit |= !root->renderOneFrame();
    }

    WindowEventUtilities::removeWindowEventListener( window, &myWindowEventListener );

    OGRE_DELETE root;
    root = 0;

    return 0;
}
