# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(receiver)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable target
add_executable(receiver receiver.cpp)

# Include directories
target_include_directories(receiver PRIVATE /usr/local/include)

# Link libraries
target_link_libraries(receiver PRIVATE vsomeip3 pthread)

# Link directories (if needed)
link_directories(/usr/local/lib)

# Install the binary to a subdirectory of the parent directory
install(TARGETS receiver
        RUNTIME DESTINATION bin) # Relative to CMAKE_INSTALL_PREFIX