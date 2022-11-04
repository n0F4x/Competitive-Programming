# cmake version to be used
cmake_minimum_required( VERSION 3.0 )

# set(CMAKE_CXX_COMPILER "C:/Programming/Runtime Systems/msys64/mingw64/bin/g++.exe")

# project name
project(Project)

# flags
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# include
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

file(GLOB source_files CONFIGURE_DEPENDS "./src/*.cpp")

add_executable(main ${source_files})
