cmake_minimum_required(VERSION 3.19)
project(developer_joyofenergy_cpp)

set(CMAKE_CXX_STANDARD 17)

# Include CPM package manager
include(cmake/CPM.cmake)

# Boost (header-only libraries: Beast, Asio, System)
CPMAddPackage(
    NAME Boost
    VERSION 1.84.0
    URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
    URL_HASH SHA256=2e64e5d79a738d0fa6fb546c6e5c2bd28f88d268a2a080546f74e5ff98f29d0e
    OPTIONS
        "BOOST_ENABLE_CMAKE ON"
        "BOOST_INCLUDE_LIBRARIES beast\;asio\;system"
)

CPMAddPackage(
    NAME googletest
    GITHUB_REPOSITORY google/googletest
    GIT_TAG v1.15.2
    VERSION 1.15.2
    OPTIONS
        "INSTALL_GTEST OFF"
        "gtest_force_shared_crt ON"
)

CPMAddPackage(
    NAME nlohmann_json
    GITHUB_REPOSITORY nlohmann/json
    VERSION 3.11.3
)

CPMAddPackage(
    NAME date
    GITHUB_REPOSITORY HowardHinnant/date
    GIT_TAG v3.0.4
    OPTIONS
        "USE_SYSTEM_TZ_DB ON"
        "BUILD_TZ_LIB OFF"
)

add_subdirectory(rest)
add_executable(app main.cpp)
target_link_libraries(app PRIVATE rest)

enable_testing()
add_subdirectory(test)