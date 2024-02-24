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
	"${CMAKE_SOURCE_DIR}/build/Release/PhysX_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PhysXCommon_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PhysXFoundation_64.lib"
	"${CMAKE_SOURCE_DIR}/build/Release/PhysXCooking_64.lib"
)

target_link_libraries(${TARGET_NAME}
	"${CMAKE_SOURCE_DIR}/build/Release/SEE_Crater_Transport.lib"
	"${DEVSTUDIO_LIBDIR}"
	"${PHYSX_LIBS}"
)