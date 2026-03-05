cmake_minimum_required(VERSION 3.16)

# Project name and language
project(DateClass LANGUAGES CXX)

# Make sure clandg picks up the include directories
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard (change to 17 or 20 if you prefer)
# using 23 so I can use the format function for string interpolation
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add all source files
file(GLOB SOURCES "src/*.cpp")

# Add the executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
)

# Add include directory
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

