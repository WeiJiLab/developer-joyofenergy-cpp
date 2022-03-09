cmake_minimum_required(VERSION 3.16)
project(developer_joyofenergy_cpp)

list(APPEND CMAKE_MODULE_PATH
            ${CMAKE_BINARY_DIR}
            ${CMAKE_SOURCE_DIR}/cmake_module)
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)

include(conan)

conan_cmake_configure(REQUIRES boost/1.76.0
                      REQUIRES gtest/1.11.0
                      REQUIRES nlohmann_json/3.9.1
                      REQUIRES date/3.0.1
                      OPTIONS boost:header_only=True
                      OPTIONS date:header_only=True
                      GENERATORS cmake_find_package)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
                    BUILD missing
                    REMOTE conancenter
                    SETTINGS ${settings})

add_subdirectory(rest)
add_executable(app main.cpp)
target_link_libraries(app PRIVATE rest)

enable_testing()
add_subdirectory(test)
