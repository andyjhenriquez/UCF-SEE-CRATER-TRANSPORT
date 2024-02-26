set(TARGET_NAME CraterTransport)

add_executable(${TARGET_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/src/CraterTransport.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/CraterTransport_Physics.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/CraterTransport_Physics.cpp
)

target_include_directories(${TARGET_NAME}
	PUBLIC
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/include/PhysX"
)

set(PHYSX_LIBS_DEBUG
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXExtensions_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXVehicle_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXCharacterKinematic_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/LowLevelDynamics_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysX_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXCommon_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXCooking_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXFoundation_64.lib"
)

set(PHYSX_LIBS_RELEASE
	"${CMAKE_SOURCE_DIR}/build/Release/PhysXExtensions_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PhysXVehicle_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PhysXCharacterKinematic_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/LowLevelDynamics_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PhysX_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PhysXCommon_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PhysXCooking_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PhysXFoundation_64.lib"
)

target_link_libraries(${TARGET_NAME}
	debug     "${CMAKE_SOURCE_DIR}/build/Debug/SEE_Crater_Transport.lib"
	optimized "${CMAKE_SOURCE_DIR}/build/Release/SEE_Crater_Transport.lib"
	debug     "${PHYSX_LIBS_DEBUG}"
	optimized "${PHYSX_LIBS_RELEASE}"
	          "${DEVSTUDIO_LIBDIR}"
)