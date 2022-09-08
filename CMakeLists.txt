cmake_minimum_required(VERSION 3.2)
project(RayTracer)

set(SOURCE_DIR "src")
set(INCLUDE_DIR "include")
set(BIN_DIR "bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)

# add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/include/*.h
	${CMAKE_SOURCE_DIR}/include/*.hpp)
include_directories(${INCLUDE_DIR})
include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/include"
)

find_package(GLM CONFIG REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${BIN_DIR}")

add_executable(RayTracer ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(RayTracer PRIVATE glm::glm)