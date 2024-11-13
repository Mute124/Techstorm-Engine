

# Project shared library
add_library(engine_lib SHARED 
	"engine.cpp"
    "engine.h" 
    "BasicCore.h" 
    "Project.h" 
    "renderer/Window.h" 
    "renderer/Window.cpp" 
    "renderer/Renderer.h" 
    "renderer/Renderer.cpp"
    "math/Vector.h" 
    "renderer/Color.h" 
    "Utils/Singleton.h" 
    "renderer/GameObject.h" 
    "renderer/GameObject.cpp"
    "input/Input.h" 
    "math/Vector.cpp" 
    "renderer/Camera.h" 
    "Common.h" 
    "renderer/RenderLayer.h" 
    "renderer/GameObjectRegistry.h"
    "renderer/GameObjectRegistry.cpp" 
    "utils/DoublyLinkedList.h" 
    "world/world.h" 
    "renderer/RayStorm.h"   
    "dbg/Logging.h" 
    "renderer/objects/PlaneObject.h"
    "world/tools/Terrain.h" 
    "renderer/IGameObjectGate.h"
    "utils/Gate.h" 
    "physics/PhysicsCommon.h"
    #"physics/Layers.h" 
    #"physics/ObjectLPF.h" 
    #"physics/BroadPhaseLayerRegistry.h" 
    #"physics/ILayerRegistry.h" 
    #"physics/BPLayerInterface.h" 
    #"physics/ObjectVsBroadPhaseLayerFilter.h" 
    #"physics/ObjectContactListener.h" 
    #"physics/BodyActivationListener.h" 
    "physics/Physics.h" 
    #"physics/PhysicsInitializer.h" 
    "physics/Physics.cpp"
    "conf/Config.h"
    "conf/Config.cpp"
    "utils/Globals.h"
    "fs/FileSystem.h"
    "fs/FileSystem.cpp"
)

target_include_directories(engine_lib PRIVATE ${PROJECT_SOURCE_DIR}/include )
target_link_libraries(engine_lib PUBLIC
    raylib 
    ZLIB::ZLIB 
    joltphysics::joltphysics 
    joltphysics_DEPS_TARGET
    libconfig::libconfig
    libconfig_libconfig_libconfig++_DEPS_TARGET
    
)

# Set output name for Windows/Linux
if(WIN32)
    set_target_properties(engine_lib PROPERTIES OUTPUT_NAME "engine_lib.dll" )
elseif(UNIX)
    set_target_properties(engine_lib PROPERTIES OUTPUT_NAME "engine_lib.so") 
endif()