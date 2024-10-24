cmake_minimum_required(VERSION 3.20)
project(GameEngine VERSION 0.1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add MSYS2 MinGW paths
set(MINGW_PATH "C:/ProgramApp/ScoopGlobal/apps/msys2/2024-07-27/mingw64")
list(APPEND CMAKE_PREFIX_PATH ${MINGW_PATH})

# Set include and library paths explicitly
include_directories(
    ${MINGW_PATH}/include
    ${MINGW_PATH}/lib/gcc/x86_64-w64-mingw32/14.2.0/include
    ${MINGW_PATH}/include/c++/14.2.0
    ${MINGW_PATH}/include/c++/14.2.0/x86_64-w64-mingw32
)

# Find packages
find_package(glfw3 REQUIRED)
find_package(spdlog REQUIRED)
find_package(OpenGL REQUIRED)

# Add source files
set(SOURCES 
    src/main.cpp
    src/Core/Engine.cpp
    src/Core/Node.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Core
)

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        glfw
        spdlog::spdlog
        OpenGL::GL
)

# Set runtime library path
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Copy necessary DLLs to output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${MINGW_PATH}/bin/libglfw3.dll
        ${MINGW_PATH}/bin/libspdlog.dll
        ${CMAKE_BINARY_DIR}/bin/
)