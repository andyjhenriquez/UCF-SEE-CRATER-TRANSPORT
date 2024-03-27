set(TARGET_NAME CraterTransport)

# Option to run the code without using HLA to avoid errors and focusing only on the physics of the simulation
option(USE_HLA "Choose whether to attempt an HLA connection when running the simulation" ON)
if (USE_HLA)
	add_compile_definitions(USE_HLA)
endif()

add_executable(${TARGET_NAME}
	"${CMAKE_CURRENT_SOURCE_DIR}/src/CraterTransport.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/PhysicsManager.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/PhysicsManager.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/sim_utils.cpp" 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/sim_utils.h" 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/OmniPvd.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/ModelLoader.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/ModelLoader.cpp"
)

target_include_directories(${TARGET_NAME}
	PUBLIC
	"${CMAKE_SOURCE_DIR}/include/PhysX"
	"${CMAKE_SOURCE_DIR}/include"
)

set(PHYSX_LIBS_DEBUG
	"${CMAKE_SOURCE_DIR}/build/Debug/SceneQuery_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/LowLevel_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/LowLevelAABB_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXPvdSDK_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXTask_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXVehicle2_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PVDRuntime_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/SimulationController_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXExtensions_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXVehicle_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXCharacterKinematic_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/LowLevelDynamics_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysX_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXCommon_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXCooking_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXFoundation_64.lib"
	CACHE INTERNAL ""
)

set(PHYSX_LIBS_RELEASE
	"${CMAKE_SOURCE_DIR}/build/Debug/SceneQuery_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/LowLevel_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/LowLevelAABB_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PhysXPvdSDK_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PhysXTask_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PhysXVehicle2_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PVDRuntime_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/SimulationController_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PhysXExtensions_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PhysXVehicle_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PhysXCharacterKinematic_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/LowLevelDynamics_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PhysX_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PhysXCommon_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PhysXCooking_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PhysXFoundation_64.lib"
	CACHE INTERNAL ""
)

target_link_libraries(${TARGET_NAME}
	debug     "${CMAKE_SOURCE_DIR}/build/Debug/SEE_Crater_Transport.lib"
	optimized "${CMAKE_SOURCE_DIR}/build/Release/SEE_Crater_Transport.lib"
	debug     "${PHYSX_LIBS_DEBUG}"
	optimized "${PHYSX_LIBS_RELEASE}"
)