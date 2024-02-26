set(TARGET_NAME Tests)

add_executable(${TARGET_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/src/unittests.cpp
)

target_include_directories(${TARGET_NAME}
	PUBLIC
	"${CMAKE_SOURCE_DIR}/Federates/CraterTransport/src"
	"${CMAKE_SOURCE_DIR}/Federates/CraterEnvironment/src"
)