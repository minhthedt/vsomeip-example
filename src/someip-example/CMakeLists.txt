# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(receiver)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# DLT
find_package(PkgConfig REQUIRED)
pkg_check_modules(DLT REQUIRED automotive-dlt)

#USE_DLT ON
option(USE_DLT "Enable DLT logging support" ON)
if(USE_DLT)
    add_compile_definitions(USE_DLT=1)
else()
    add_compile_definitions(USE_DLT=0)
endif()

include_directories(${DLT_INCLUDE_DIRS})
link_directories(${DLT_LIBRARY_DIRS})
message(STATUS "DLT_INCLUDE_DIRS: ${DLT_INCLUDE_DIRS}")
message(STATUS "DLT_LIBRARY_DIRS: ${DLT_LIBRARY_DIRS}")
message(STATUS "DL_LIBRARY: ${DL_LIBRARY}")
message(STATUS "DLT_LIBRARIES: ${DLT_LIBRARIES}")
################################################################################
#1. Build routingmanagerd
set(BINARY_NAME routingmanagerd)
# Add the executable target
add_executable(${BINARY_NAME} 
            rountingmanagerd/routingmanagerd.cpp)

# Include directories
target_include_directories(${BINARY_NAME} PRIVATE /usr/local/include)

# Link libraries
target_link_libraries(${BINARY_NAME} 
        PRIVATE 
        vsomeip3
        pthread
        ${DLT_LIBRARIES}
        ${DL_LIBRARY}
)

# Link directories (if needed)
link_directories(/usr/local/lib)

# Install the binary to a subdirectory of the parent directory
install(TARGETS ${BINARY_NAME}
        RUNTIME DESTINATION bin) # Relative to CMAKE_INSTALL_PREFIX

################################################################################
#2. Build request-sample
set(BINARY_NAME request-sample)
# Add the executable target
add_executable(${BINARY_NAME} 
            request-sample.cpp)

# Include directories
target_include_directories(${BINARY_NAME}  PRIVATE /usr/local/include)

# Link libraries
target_link_libraries(${BINARY_NAME}  
        PRIVATE 
        vsomeip3
        pthread
        ${DLT_LIBRARIES}
        ${DL_LIBRARY}
)

# Link directories (if needed)
link_directories(/usr/local/lib)

# Install the binary to a subdirectory of the parent directory
install(TARGETS ${BINARY_NAME} 
        RUNTIME DESTINATION bin) # Relative to CMAKE_INSTALL_PREFIX

################################################################################
#3. Build response-sample
set(BINARY_NAME response-sample)
# Add the executable target
add_executable(${BINARY_NAME} 
            response-sample.cpp)

# Include directories
target_include_directories(${BINARY_NAME}  PRIVATE /usr/local/include)

# Link libraries
target_link_libraries(${BINARY_NAME}  
        PRIVATE 
        vsomeip3
        pthread
        ${DLT_LIBRARIES}
        ${DL_LIBRARY}
)

# Link directories (if needed)
link_directories(/usr/local/lib)

# Install the binary to a subdirectory of the parent directory
install(TARGETS ${BINARY_NAME} 
        RUNTIME DESTINATION bin) # Relative to CMAKE_INSTALL_PREFIX

################################################################################
#3.1 Build response-sample-x
set(BINARY_NAME response-sample-x)
# Add the executable target
add_executable(${BINARY_NAME} 
            response-sample-x.cpp)

# Include directories
target_include_directories(${BINARY_NAME}  PRIVATE /usr/local/include)

# Link libraries
target_link_libraries(${BINARY_NAME}  
        PRIVATE 
        vsomeip3
        pthread
        ${DLT_LIBRARIES}
        ${DL_LIBRARY}
)

# Link directories (if needed)
link_directories(/usr/local/lib)

# Install the binary to a subdirectory of the parent directory
install(TARGETS ${BINARY_NAME} 
        RUNTIME DESTINATION bin) # Relative to CMAKE_INSTALL_PREFIX

################################################################################
#4. Build subscribe-sample
set(BINARY_NAME subscribe-sample)
# Add the executable target
add_executable(${BINARY_NAME} 
            subscribe-sample.cpp)

# Include directories
target_include_directories(${BINARY_NAME}  PRIVATE /usr/local/include)

# Link libraries
target_link_libraries(${BINARY_NAME}  
        PRIVATE 
        vsomeip3
        pthread
        ${DLT_LIBRARIES}
        ${DL_LIBRARY}
)

# Link directories (if needed)
link_directories(/usr/local/lib)

# Install the binary to a subdirectory of the parent directory
install(TARGETS ${BINARY_NAME} 
        RUNTIME DESTINATION bin) # Relative to CMAKE_INSTALL_PREFIX

################################################################################
#5. Build notify-sample
set(BINARY_NAME notify-sample)
# Add the executable target
add_executable(${BINARY_NAME} 
            notify-sample.cpp)

# Include directories
target_include_directories(${BINARY_NAME}  PRIVATE /usr/local/include)

# Link libraries
target_link_libraries(${BINARY_NAME}  
        PRIVATE 
        vsomeip3
        pthread
        ${DLT_LIBRARIES}
        ${DL_LIBRARY}
)

# Link directories (if needed)
link_directories(/usr/local/lib)

# Install the binary to a subdirectory of the parent directory
install(TARGETS ${BINARY_NAME} 
        RUNTIME DESTINATION bin) # Relative to CMAKE_INSTALL_PREFIX
