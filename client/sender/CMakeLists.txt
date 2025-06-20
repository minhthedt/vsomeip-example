# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(sender)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable target
add_executable(sender sender.cpp)

# Include directories
target_include_directories(sender PRIVATE /usr/local/include)

# Link libraries
target_link_libraries(sender PRIVATE vsomeip3 pthread)

# Link directories (if needed)
link_directories(/usr/local/lib)

# Install the binary to a subdirectory of the parent directory
install(TARGETS sender
        RUNTIME DESTINATION bin) # Relative to CMAKE_INSTALL_PREFIX