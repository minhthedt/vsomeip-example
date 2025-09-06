# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(MyProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Set the install prefix to the parent directory
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "Install path" FORCE)

# Include all subdirectories
add_subdirectory(src)
add_subdirectory(doc/example/mutilcast_example)
add_subdirectory(doc/example/broadcast_example)

# Add more subdirectories as needed