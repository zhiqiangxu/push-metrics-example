# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)  # Specify the minimum CMake version
project(pushmetric)                     # Set the project name

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)            # Use C++11
set(CMAKE_CXX_STANDARD_REQUIRED True)  # Require C++11

# Add the executable target
add_executable(pushmetric src/main.cpp)   # Create an executable from main.cpp

# find_package(prometheus-cpp CONFIG REQUIRED)
target_link_libraries(pushmetric prometheus-cpp-push prometheus-cpp-core)