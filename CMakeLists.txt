cmake_minimum_required(VERSION 3.26.4)

set(CMAKE_C_COMPILER "clang")
set(COMPILER_OPTIONS "-wbraced-scalar-init")
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/**.c)

project(ccollection VERSION 1.0.0 LANGUAGES C)

add_library(${PROJECT_NAME}.static STATIC ${SRC})
add_library(${PROJECT_NAME}.shared SHARED ${SRC})

target_include_directories(${PROJECT_NAME}.static PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/priv)
target_include_directories(${PROJECT_NAME}.static PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(${PROJECT_NAME}.shared PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/priv)
target_include_directories(${PROJECT_NAME}.shared PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include)
