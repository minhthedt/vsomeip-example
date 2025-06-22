# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(dlt_example)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable target
add_executable(dlt_example dlt_example.cpp)

# Include directories
target_include_directories(dlt_example PRIVATE /usr/local/include)

# Link libraries
target_link_libraries(dlt_example PRIVATE dlt)

# Link directories (if needed)
link_directories(/usr/local/lib)

# Install the binary to a subdirectory of the parent directory
install(TARGETS dlt_example
        RUNTIME DESTINATION bin) # Relative to CMAKE_INSTALL_PREFIX
