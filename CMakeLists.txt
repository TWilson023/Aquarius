cmake_minimum_required(VERSION 3.3.2)
project(Aquarius)

set(CMAKE_SHARED_LINKER_FLAGS "-lglfw")

find_package(OpenGL REQUIRED)

include_directories(glfw/include/GLFW glew/include glm)
set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW
)

add_definitions(
	-DGLEW_STATIC
)

include_directories("include")
file(GLOB SOURCES "src/*.cpp")
add_executable(Aquarius ${SOURCES})

target_link_libraries(Aquarius ${ALL_LIBS})
