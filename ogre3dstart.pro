TARGET = ogre3dstart
TEMPLATE = app

SOURCES += \
  main.cpp

DISTFILES += \
  config/ogre.cfg \
  config/plugins.cfg \
  config/resources.cfg \
  config/resources2.cfg \
  data/OgreMeshTool.log \
  data/cube.mesh \
  data/cubev1.8.mesh \
  data/cubev2.1_legacy.mesh \
  data/plugins_tools.cfg

unix:!macx: LIBS += \
  -L/lib/x86_64-linux-gnu/ -lX11 \
  -L/usr/local/lib/ -lOgreHlmsPbs \
  -L/usr/local/lib/ -lOgreHlmsUnlit \
  -L/usr/local/lib/ -lOgreMain \
  -L/usr/local/lib/ -lOgreMeshLodGenerator \
  -L/usr/local/lib/ -lOgreOverlay \
  -L/usr/local/lib/ -lOgreSceneFormat \
  -L/usr/local/lib/OGRE/ -lPlugin_ParticleFX \
  -L/usr/local/lib/OGRE/ -lRenderSystem_GL3Plus

DEPENDPATH += \
  /usr/local/lib/OGRE \
  /usr/local/lib \
  /lib/x86_64-linux-gnu

INCLUDEPATH += \
  /usr/local/lib \
  /lib/x86_64-linux-gnu \
  /usr/local/include/OGRE \
  /usr/local/include/OGRE/Animation/ \
  /usr/local/include/OGRE/CommandBuffer/ \
  /usr/local/include/OGRE/Compositor/ \
  /usr/local/include/OGRE/Compositor/Pass/ \
  /usr/local/include/OGRE/Compositor/Pass/PassClear/ \
  /usr/local/include/OGRE/Compositor/Pass/PassCompute/ \
  /usr/local/include/OGRE/Compositor/Pass/PassDepthCopy/ \
  /usr/local/include/OGRE/Compositor/Pass/PassIblSpecular/ \
  /usr/local/include/OGRE/Compositor/Pass/PassMipmap/ \
  /usr/local/include/OGRE/Compositor/Pass/PassQuad/ \
  /usr/local/include/OGRE/Compositor/Pass/PassScene/ \
  /usr/local/include/OGRE/Compositor/Pass/PassShadows/ \
  /usr/local/include/OGRE/Compositor/Pass/PassStencil/ \
  /usr/local/include/OGRE/Compositor/Pass/PassTargetBarrier/ \
  /usr/local/include/OGRE/Compositor/Pass/PassUav/ \
  /usr/local/include/OGRE/Compute/ \
  /usr/local/include/OGRE/debugbreak/ \
  /usr/local/include/OGRE/Deprecated/ \
  /usr/local/include/OGRE/GLX/ \
  /usr/local/include/OGRE/Hash/ \
  /usr/local/include/OGRE/Hlms/ \
  /usr/local/include/OGRE/Hlms/Common/ \
  /usr/local/include/OGRE/Hlms/Pbs/ \
  /usr/local/include/OGRE/Hlms/Pbs/Cubemaps/ \
  /usr/local/include/OGRE/Hlms/Pbs/InstantRadiosity/ \
  /usr/local/include/OGRE/Hlms/Pbs/IrradianceField/ \
  /usr/local/include/OGRE/Hlms/Pbs/LightProfiles/ \
  /usr/local/include/OGRE/Hlms/Pbs/Vct/ \
  /usr/local/include/OGRE/Hlms/Unlit/ \
  /usr/local/include/OGRE/Math/ \
  /usr/local/include/OGRE/Math/Array/ \
  /usr/local/include/OGRE/Math/Array/NEON/ \
  /usr/local/include/OGRE/Math/Array/NEON/Single/ \
  /usr/local/include/OGRE/Math/Array/SSE2/ \
  /usr/local/include/OGRE/Math/Array/SSE2/Single/ \
  /usr/local/include/OGRE/Math/Simple/ \
  /usr/local/include/OGRE/Math/Simple/C/ \
  /usr/local/include/OGRE/MeshLodGenerator/ \
  /usr/local/include/OGRE/ogrestd/ \
  /usr/local/include/OGRE/Overlay/ \
  /usr/local/include/OGRE/Plugins/ \
  /usr/local/include/OGRE/Plugins/ParticleFX/ \
  /usr/local/include/OGRE/RenderSystems/ \
  /usr/local/include/OGRE/RenderSystems/GL3Plus/ \
  /usr/local/include/OGRE/RenderSystems/GL3Plus/Deprecated/ \
  /usr/local/include/OGRE/RenderSystems/GL3Plus/GL/ \
  /usr/local/include/OGRE/RenderSystems/GL3Plus/GLSL/ \
  /usr/local/include/OGRE/RenderSystems/GL3Plus/GLX/ \
  /usr/local/include/OGRE/RenderSystems/GL3Plus/Vao/ \
  /usr/local/include/OGRE/RenderSystems/GL3Plus/windowing/ \
  /usr/local/include/OGRE/RenderSystems/GL3Plus/windowing/EGL/ \
  /usr/local/include/OGRE/RenderSystems/GL3Plus/windowing/EGL/PBuffer/ \
  /usr/local/include/OGRE/RenderSystems/GL3Plus/windowing/GLX/ \
  /usr/local/include/OGRE/RenderSystems/GL3Plus/windowing/gtk/ \
  /usr/local/include/OGRE/RenderSystems/GL3Plus/windowing/OSX/ \
  /usr/local/include/OGRE/RenderSystems/GL3Plus/windowing/SDL/ \
  /usr/local/include/OGRE/RenderSystems/GL3Plus/windowing/win32/ \
  /usr/local/include/OGRE/RenderSystems/NULL/ \
  /usr/local/include/OGRE/RenderSystems/NULL/include/ \
  /usr/local/include/OGRE/RenderSystems/NULL/include/Deprecated/ \
  /usr/local/include/OGRE/RenderSystems/NULL/include/Vao/ \
  /usr/local/include/OGRE/RenderSystems/Vulkan/ \
  /usr/local/include/OGRE/RenderSystems/Vulkan/include/ \
  /usr/local/include/OGRE/RenderSystems/Vulkan/include/SPIRV-Reflect/ \
  /usr/local/include/OGRE/RenderSystems/Vulkan/include/SPIRV-Reflect/include/ \
  /usr/local/include/OGRE/RenderSystems/Vulkan/include/SPIRV-Reflect/include/spirv/ \
  /usr/local/include/OGRE/RenderSystems/Vulkan/include/SPIRV-Reflect/include/spirv/unified1/ \
  /usr/local/include/OGRE/RenderSystems/Vulkan/include/Vao/ \
  /usr/local/include/OGRE/RenderSystems/Vulkan/include/Windowing/ \
  /usr/local/include/OGRE/RenderSystems/Vulkan/include/Windowing/Android/ \
  /usr/local/include/OGRE/RenderSystems/Vulkan/include/Windowing/win32/ \
  /usr/local/include/OGRE/RenderSystems/Vulkan/include/Windowing/X11/ \
  /usr/local/include/OGRE/SceneFormat/ \
  /usr/local/include/OGRE/Threading/ \
  /usr/local/include/OGRE/Vao/

# ------------------------------------------------------------------------------

# origin paths
CONFIG_SRC_PATH = $$PWD/config
DATA_SRC_PATH   = $$PWD/data

# destiny paths
BIN_DST_PATH    = $$OUT_PWD/bin
CONFIG_DST_PATH = $$OUT_PWD/config
DATA_DST_PATH   = $$OUT_PWD/data

# ------------------------------------------------------------------------------

DST_DIRS = \
  $$BIN_DST_PATH \
  $$CONFIG_DST_PATH \
  $$DATA_DST_PATH

# The rules for creating the directories are defined before construction.
create.commands = $$QMAKE_MKDIR $$DST_DIRS
# Rules are added to PRE_TARGETDEPS and PRE_TARGET.
PRE_TARGETDEPS += create
PRE_TARGET += create
# Custom actions are added to run as part of your build process.
QMAKE_EXTRA_TARGETS += create

# ------------------------------------------------------------------------------

# Copy the configuration files from the config directory.
configFiles.commands = $$quote(cp $$CONFIG_SRC_PATH/* $$CONFIG_DST_PATH/)
# Rules are added to POST_TARGETDEPS to be executed after the project is built.
POST_TARGETDEPS += configFiles
# Custom actions are added to run as part of your build process.
QMAKE_EXTRA_TARGETS += configFiles

# ------------------------------------------------------------------------------

# Copy the data files from the data directory.
dataFiles.commands = $$quote(cp $$DATA_SRC_PATH/* $$DATA_DST_PATH/)
# Rules are added to POST_TARGETDEPS to be executed after the project is built.
POST_TARGETDEPS += dataFiles
# Custom actions are added to run as part of your build process.
QMAKE_EXTRA_TARGETS += dataFiles

# ------------------------------------------------------------------------------

DOT = .
SUFFIX_DEBUG = debug
TARGET_DEBUG = $$TARGET$$DOT$$SUFFIX_DEBUG
# Copy the executable to the final path to the "bin/" directory.
# QMAKE_POST_LINK += $$QMAKE_COPY $$OUT_PWD/$$TARGET_DEBUG $$BIN_DST_PATH/$$TARGET_DEBUG
# QMAKE_POST_LINK += $$QMAKE_COPY $$OUT_PWD/$$TARGET $$BIN_DST_PATH/$$TARGET
QMAKE_POST_LINK += $$QMAKE_MOVE $$OUT_PWD/$$TARGET $$BIN_DST_PATH/$$TARGET

