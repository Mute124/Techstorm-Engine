


		#if (TARGET_ENGINE)
			
        # Example 'Hello World' application
			#include(${PHYSICS_REPO_ROOT}/HelloWorld/HelloWorld.cmake)
			#add_executable(HelloWorld ${HELLO_WORLD_SRC_FILES})
			# Engine shared library
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
    "debug/Logging.h" 
    "renderer/objects/PlaneObject.h"
    "world/tools/Terrain.h" 
    "renderer/IGameObjectGate.h"
    "utils/Gate.h" 
    "physics/PhysicsCommon.h"
    "physics/Layers.h" 
    "physics/ObjectLPF.h" 
    "physics/BroadPhaseLayerRegistry.h" 
    "physics/ILayerRegistry.h" 
    "physics/BPLayerInterface.h" 
    "physics/ObjectVsBroadPhaseLayerFilter.h" 
    "physics/ObjectContactListener.h" 
    "physics/BodyActivationListener.h" 
    "physics/Physics.h" 
    "physics/PhysicsInitializer.h" 
    "physics/Physics.cpp"
)

# Link to the engine shared library
#target_link_libraries(project_lib PUBLIC engine_lib)
# Find the Jolt.lib file explicitly
find_library(JOLT_LIB NAMES JoltPhysics 
    PATHS "C:/Dev/Techstorm-v5/lib"
)
# Verify that the library was found
if (JOLT_LIB)
    message(STATUS "Jolt.lib found at: ${JOLT_LIB}")
else()
    message(FATAL_ERROR "Jolt.lib not found!")
endif()

#target_include_directories(main_app PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(engine_lib PUBLIC ${JoltPhysics_SOURCE_DIR}/..)
target_link_libraries(engine_lib raylib eventpp::eventpp Jolt)

# Link to any external libraries here (e.g., glfw, SDL)
# Add include directories if needed (JoltPhysics should automatically include them)
#target_include_directories(engine_lib PUBLIC ${Jolt_SOURCE_DIR})
#target_include_directories(engine_lib PUBLIC ${JPH_SOURCE}/)
#target_link_directories(engine_lib PUBLIC ${Jolt_SOURCE_DIR}) # Ensure correct directory
# include_directories(engine_lib build/x64-debug/_deps/joltphysics-src/Jolt)
# Set output name for Windows/Linux
if(WIN32)
    set_target_properties(engine_lib PROPERTIES OUTPUT_NAME "engine_lib.dll" )
elseif(UNIX)
    set_target_properties(engine_lib PROPERTIES OUTPUT_NAME "engine_lib.so") 
endif()