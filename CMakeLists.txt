cmake_minimum_required(VERSION 3.3.2)
project(Aquarius)

set(GLFW_SOURCE_DIR "lib/glfw")
set(GLM_SOURCE_DIR "lib/glm")
set(GLEW_SOURCE_DIR "lib/glew")

find_package(OpenGL REQUIRED)

# Building only the GLFW lib
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")

add_subdirectory(${GLFW_SOURCE_DIR} ${GLEW_SOURCE_DIR})

include_directories(
	${GLFW_SOURCE_DIR}/include
	${GLFW_SOURCE_DIR}/deps
	${GLM_SOURCE_DIR}
	${GLEW_SOURCE_DIR}/include
)

add_library(glew STATIC
	${GLEW_SOURCE_DIR}/src/glew.c
	${GLEW_SOURCE_DIR}/include
)

target_link_libraries(glew ${OPENGL_LIBRARY} ${GLFW_LIBRARIES})

add_definitions(
	-DGLEW_STATIC
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories("include")
file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp")
add_executable(Aquarius ${SOURCES})

target_link_libraries(Aquarius glfw ${OPENGL_LIBRARY} ${GLFW_LIBRARIES} glew)
