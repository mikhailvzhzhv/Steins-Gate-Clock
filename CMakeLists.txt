cmake_minimum_required(VERSION 3.5.1)
project(steins_gate_clock)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

file(GLOB source src/*.cpp)

set(SRC ${source})

add_executable(steins_gate_clock ${SRC})
target_link_libraries(steins_gate_clock ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
target_include_directories(steins_gate_clock PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)