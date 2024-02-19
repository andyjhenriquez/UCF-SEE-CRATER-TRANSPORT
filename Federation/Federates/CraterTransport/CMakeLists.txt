set(TARGET_NAME CraterTransport)

add_executable(${TARGET_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/src/CraterTransport.cpp
)

target_include_directories(${TARGET_NAME}
	PUBLIC
	"${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(${TARGET_NAME}
	"${CMAKE_SOURCE_DIR}/build/Release/SEE_Crater_Transport.lib"
	"${DEVSTUDIO_LIBDIR}"
)