cmake_minimum_required(VERSION 2.8)
project(packet-babelshark)

# TODO: find this rather than hardcoding it
include_directories(../../../../wireshark)

# TODO: remove this from #ifdef directives
add_definitions(-DHAVE_CONFIG_H)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB_PKG glib-2.0)
include_directories(${GLIB_PKG_INCLUDE_DIRS})
include_directories(include)

add_subdirectory(src)
add_subdirectory(cajun/src)

link_directories(${packet-bableshark_BINARY_DIR}/src)

add_library(packet-babelshark SHARED
	    packet-babelshark.cpp)

target_link_libraries(packet-babelshark babelshark)
