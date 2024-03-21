set(TARGET_NAME Tests)

add_executable(${TARGET_NAME}
	"${CMAKE_CURRENT_SOURCE_DIR}/src/unittests.cpp"
	"${CMAKE_SOURCE_DIR}/Federates/CraterTransport/src/sim_utils.cpp" 
	"${CMAKE_SOURCE_DIR}/Federates/CraterTransport/src/sim_utils.h" 
)

target_include_directories(${TARGET_NAME}
	PUBLIC
	"${CMAKE_SOURCE_DIR}/Federates/CraterTransport/src"
	"${CMAKE_SOURCE_DIR}/Federates/CraterEnvironment/src"
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/include/PhysX"

)

target_link_libraries(${TARGET_NAME}
	debug     "${CMAKE_SOURCE_DIR}/build/Debug/SEE_Crater_Transport.lib"
	optimized "${CMAKE_SOURCE_DIR}/build/Release/SEE_Crater_Transport.lib"
	debug     "${PHYSX_LIBS_DEBUG}"
	optimized "${PHYSX_LIBS_RELEASE}"
)