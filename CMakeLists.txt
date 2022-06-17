cmake_minimum_required(VERSION 3.10.2)
project(console_opption_handler VERSION 0.0.0.1 LANGUAGES CXX)

file(GLOB H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB CXX_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_library(${PROJECT_NAME} STATIC ${CXX_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
