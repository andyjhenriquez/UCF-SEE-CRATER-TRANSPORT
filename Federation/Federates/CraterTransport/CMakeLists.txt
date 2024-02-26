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

set(PHYSX_LIBS
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXExtensions_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXVehicle_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXCharacterKinematic_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/LowLevelDynamics_static_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysX_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXCommon_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXCooking_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Debug/PhysXFoundation_64.lib"
)

target_link_libraries(${TARGET_NAME}
	"${CMAKE_SOURCE_DIR}/build/Debug/SEE_Crater_Transport.lib"
	"${DEVSTUDIO_LIBDIR}"
	"${PHYSX_LIBS}"
)