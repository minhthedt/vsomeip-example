# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(sender)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# DLT
find_package(PkgConfig REQUIRED)
pkg_check_modules(DLT REQUIRED automotive-dlt)

include_directories(${DLT_INCLUDE_DIRS})
link_directories(${DLT_LIBRARY_DIRS})
message(STATUS "DLT_INCLUDE_DIRS: ${DLT_INCLUDE_DIRS}")
message(STATUS "DLT_LIBRARY_DIRS: ${DLT_LIBRARY_DIRS}")
message(STATUS "DL_LIBRARY: ${DL_LIBRARY}")
message(STATUS "DLT_LIBRARIES: ${DLT_LIBRARIES}")

# Add the executable target
add_executable(sender sender.cpp)

# Include directories
target_include_directories(sender PRIVATE /usr/local/include)

# Link libraries
target_link_libraries(sender
        PRIVATE 
        vsomeip3
        pthread
        ${DLT_LIBRARIES}
        ${DL_LIBRARY}
)

# Link directories (if needed)
link_directories(/usr/local/lib)

# Install the binary to a subdirectory of the parent directory
install(TARGETS sender
        RUNTIME DESTINATION bin) # Relative to CMAKE_INSTALL_PREFIX