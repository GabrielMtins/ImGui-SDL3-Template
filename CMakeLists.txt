cmake_minimum_required(VERSION 3.16)
project(imgui-template)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE all_SRCS
		"${PROJECT_SOURCE_DIR}/src/*.cpp"
		"${PROJECT_SOURCE_DIR}/src/*.c"
        )

file(GLOB IMGUI_SRCS
		"${PROJECT_SOURCE_DIR}/external/imgui/imgui*.cpp"
		"${PROJECT_SOURCE_DIR}/external/imgui/backends/imgui_impl_sdlrenderer3.cpp"
		"${PROJECT_SOURCE_DIR}/external/imgui/backends/imgui_impl_sdl3.cpp"
		)

add_executable(
	${PROJECT_NAME}
	${all_SRCS}
	${IMGUI_SRCS}
)

include(FindPkgConfig)
pkg_search_module(SDL3 REQUIRED sdl3)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL3_INCLUDE_DIRS}
	"${PROJECT_SOURCE_DIR}/include/"
	"${PROJECT_SOURCE_DIR}/external/imgui/"
	"${PROJECT_SOURCE_DIR}/external/imgui/backends/"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL3_LIBRARIES}
	m
)

target_compile_options(${PROJECT_NAME} PRIVATE 
    -Wall
    -Wextra
    -Wpedantic
)
