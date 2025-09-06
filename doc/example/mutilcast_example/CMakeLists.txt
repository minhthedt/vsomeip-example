# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(mutilcast_example)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable target
add_executable(mutilcast_client mutilcast_client.cpp)

# Include directories
target_include_directories(mutilcast_client PRIVATE /usr/local/include)

# Link libraries
target_link_libraries(mutilcast_client PRIVATE vsomeip3 pthread)

# Link directories (if needed)
link_directories(/usr/local/lib)

# Install the binary to a subdirectory of the parent directory
install(TARGETS mutilcast_client
        RUNTIME DESTINATION bin) # Relative to CMAKE_INSTALL_PREFIX
#/////////////////////////////////////////////////BUILD SERVER////////////////////
# Add the executable target
add_executable(mutilcast_server mutilcast_server.cpp)

# Include directories
target_include_directories(mutilcast_server PRIVATE /usr/local/include)

# Link libraries
target_link_libraries(mutilcast_server PRIVATE vsomeip3 pthread)

# Link directories (if needed)
link_directories(/usr/local/lib)

# Install the binary to a subdirectory of the parent directory
install(TARGETS mutilcast_server
        RUNTIME DESTINATION bin) # Relative to CMAKE_INSTALL_PREFIX