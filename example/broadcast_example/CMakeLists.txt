# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(broadcast_example)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable target
add_executable(broadcast_client broadcast_client.cpp)

# Include directories
target_include_directories(broadcast_client PRIVATE /usr/local/include)

# Link libraries
target_link_libraries(broadcast_client PRIVATE vsomeip3 pthread)

# Link directories (if needed)
link_directories(/usr/local/lib)

# Install the binary to a subdirectory of the parent directory
install(TARGETS broadcast_client
        RUNTIME DESTINATION bin) # Relative to CMAKE_INSTALL_PREFIX
#/////////////////////////////////////////////////BUILD SERVER////////////////////
# Add the executable target
add_executable(broadcast_server broadcast_server.cpp)

# Include directories
target_include_directories(broadcast_server PRIVATE /usr/local/include)

# Link libraries
target_link_libraries(broadcast_server PRIVATE vsomeip3 pthread)

# Link directories (if needed)
link_directories(/usr/local/lib)

# Install the binary to a subdirectory of the parent directory
install(TARGETS broadcast_server
        RUNTIME DESTINATION bin) # Relative to CMAKE_INSTALL_PREFIX