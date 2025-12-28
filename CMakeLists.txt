cmake_minimum_required(VERSION 3.19)
project(developer_joyofenergy_cpp)

set(CMAKE_CXX_STANDARD 17)

# Set CPM cache directory to avoid re-downloading dependencies
# Can be overridden by environment variable CPM_SOURCE_CACHE
if(NOT CPM_SOURCE_CACHE)
    set(CPM_SOURCE_CACHE "${CMAKE_SOURCE_DIR}/.cpm-cache" CACHE PATH "CPM cache directory")
endif()

# Include CPM package manager
include(cmake/CPM.cmake)

# Boost (header-only libraries: Beast, Asio, System)
CPMAddPackage(
    NAME Boost
    VERSION 1.84.0
    URL https://ghfast.top/https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
    URL_HASH SHA256=2e64e5d79a738d0fa6fb546c6e5c2bd28f88d268a2a080546f74e5ff98f29d0e
    OPTIONS
        "BOOST_ENABLE_CMAKE ON"
        "BOOST_INCLUDE_LIBRARIES beast\;asio\;system"
)

CPMAddPackage(
    NAME googletest
    URL https://ghfast.top/https://github.com/google/googletest/releases/download/v1.15.2/googletest-1.15.2.tar.gz
    URL_HASH SHA256=7b42b4d6ed48810c5362c265a17faebe90dc2373c885e5216439d37927f02926
    VERSION 1.15.2
    OPTIONS
        "INSTALL_GTEST OFF"
        "gtest_force_shared_crt ON"
)

CPMAddPackage(
    NAME nlohmann_json
    URL https://ghfast.top/https://github.com/nlohmann/json/archive/refs/tags/v3.11.3.zip
    URL_HASH SHA256=04022b05d806eb5ff73023c280b68697d12b93e1b7267a0b22a1a39ec7578069

    VERSION 3.11.3
)

CPMAddPackage(
    NAME date
    URL https://ghfast.top/https://github.com/HowardHinnant/date/archive/refs/tags/v3.0.4.tar.gz
    URL_HASH SHA256=56e05531ee8994124eeb498d0e6a5e1c3b9d4fccbecdf555fe266631368fb55f
    VERSION 3.0.4
    OPTIONS
        "USE_SYSTEM_TZ_DB ON"
        "BUILD_TZ_LIB OFF"
)

add_subdirectory(rest)
add_executable(app main.cpp)
target_link_libraries(app PRIVATE rest)

enable_testing()
add_subdirectory(test)