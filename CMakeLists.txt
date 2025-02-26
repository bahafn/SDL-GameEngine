cmake_minimum_required(VERSION 3.19)
project(GameEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL_INCLUDE_DIR "D:/SDL/SDL3-3.2.4/x86_64-w64-mingw32/include")
set(SDL_IMAGE_INCLUDE_DIR "D:/SDL/SDL3_image-3.2.0/x86_64-w64-mingw32/include")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};D:/SDL/SDL3-3.2.4/cmake;D:/SDL/SDL3_image-3.2.0/cmake")

set(ENGINE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(ENGINE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

set(
        HEADERS
        ${ENGINE_INCLUDE_DIR}/utils/Vector.hpp
        ${ENGINE_INCLUDE_DIR}/renderer/Renderer.hpp
        ${ENGINE_INCLUDE_DIR}/renderer/RendererException.hpp
)
set(
        SOURCES
        ${ENGINE_SOURCE_DIR}/utils/Vector.cpp
        ${ENGINE_SOURCE_DIR}/renderer/Renderer.cpp
        ${ENGINE_SOURCE_DIR}/renderer/RendererException.cpp
)

add_library(Engine SHARED ${HEADERS} ${SOURCES})

target_include_directories(Engine PUBLIC ${ENGINE_INCLUDE_DIR} ${SDL_INCLUDE_DIR})
target_link_libraries(Engine PUBLIC SDL3::SDL3)

add_executable(${PROJECT_NAME} ${ENGINE_SOURCE_DIR}/tests/test.cpp)

include_directories(${SDL_INCLUDE_DIR})
include_directories(${SDL_IMAGE_INCLUDE_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} Engine SDL3::SDL3 SDL3_image::SDL3_image)
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
