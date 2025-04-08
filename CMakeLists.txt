cmake_minimum_required(VERSION 3.10.2)
project(
  GetOptPP
  VERSION 1.0.0
  LANGUAGES CXX)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(GETOPT_PP_BUILD_EXAMPLE "Enable use example" OFF)

# ##############################################################################
#                                    library                                   #
# ##############################################################################

file(GLOB H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/*.h)
file(GLOB CXX_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

set(TARGET_NAME ${PROJECT_NAME})

add_library(${TARGET_NAME} STATIC ${CXX_FILES})

target_link_libraries(${TARGET_NAME} PRIVATE)
target_include_directories(${TARGET_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Define install path
set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_FULL_INCLUDEDIR}/${PROJECT_NAME})
set(INCLUDE_BUILD_DIR "${PROJECT_SOURCE_DIR}/include/")
set(CMAKE_INSTALL_DIR ${CMAKE_INSTALL_FULL_LIBDIR}/cmake/${PROJECT_NAME})

# Print install path
message(VERBOSE "Install includes in: " ${INCLUDE_INSTALL_DIR})
message(VERBOSE "Install cmake file in: " ${CMAKE_INSTALL_DIR})

# Create configuration files
configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
  PATH_VARS INCLUDE_INSTALL_DIR CMAKE_INSTALL_DIR)

write_basic_package_version_file(
  "${TARGET_NAME}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

target_include_directories(
  ${TARGET_NAME} INTERFACE $<BUILD_INTERFACE:${INCLUDE_BUILD_DIR}>
                           $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>)

# Install configuration files
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DIR})

# Install target
install(FILES ${H_FILES} DESTINATION ${INCLUDE_INSTALL_DIR})
install(TARGETS ${PROJECT_NAME} LIBRARY)

# ##############################################################################
#                              example of use                                  #
# ##############################################################################

if(GETOPT_PP_BUILD_EXAMPLE)
  set(TARGET_NAME ${PROJECT_NAME}_example)

  add_executable(${TARGET_NAME} "${PROJECT_SOURCE_DIR}/example/app.cpp")

  target_link_libraries(${TARGET_NAME} PRIVATE ${PROJECT_NAME})
endif()
