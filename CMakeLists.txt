cmake_minimum_required(VERSION 3.19)
project(GameEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL_INCLUDE_DIR "D:/SDL/SDL3-3.2.4/x86_64-w64-mingw32/include")
set(SDL_LIBRARY "D:/SDL/SDL3-3.2.4/x86_64-w64-mingw32/lib/libSDL3.dll.a")

set(ENGINE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(ENGINE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

set(
        HEADERS
        ${ENGINE_INCLUDE_DIR}/utils/Vector.hpp
)
set(
        SOURCES
        ${ENGINE_SOURCE_DIR}/utils/Vector.cpp
)

add_library(Engine SHARED ${HEADERS} ${SOURCES})

target_include_directories(Engine PUBLIC ${ENGINE_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${ENGINE_SOURCE_DIR}/tests/test.cpp)

include_directories(${SDL_INCLUDE_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_INCLUDE_DIR})

find_package(SDL REQUIRED)
target_link_libraries(${PROJECT_NAME} Engine SDL::SDL)
