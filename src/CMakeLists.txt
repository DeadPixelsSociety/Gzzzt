cmake_minimum_required(VERSION 2.8)

project(GZZZT CXX)

include(CPackConfig.cmake)
include(GNUInstallDirs)

find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(ZLIB REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML2 REQUIRED sfml-graphics>=2.1 sfml-audio>=2.1 sfml-network>=2.1)
pkg_check_modules(TINYXML2 REQUIRED tinyxml2)
pkg_check_modules(LIBTMX REQUIRED libtmx0)

add_definitions(-Wall -g -O2)
add_definitions(-std=c++11)

include_directories("${CMAKE_SOURCE_DIR}/include")

add_subdirectory(lib/gzzzt)
add_subdirectory(bin)

install(
  DIRECTORY "${CMAKE_SOURCE_DIR}/include/gzzzt"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(
  DIRECTORY "${CMAKE_SOURCE_DIR}/share/gzzzt"
  DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/games"
)
