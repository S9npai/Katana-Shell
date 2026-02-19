cmake_minimum_required(VERSION 3.20)
project(Katana-Shell
        VERSION 1.0.0
        DESCRIPTION "A POSIX-compliant linux shell"
        LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Katana-Shell
        src/main.cpp
        src/parser.cpp
        src/executor.cpp
        src/execindex.cpp
        src/pipeline.cpp
        src/commands/filesys.cpp
        src/commands/sysinfo.cpp
        src/helpers.cpp
)

target_include_directories(Katana-Shell PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
target_compile_features(Katana-Shell PRIVATE cxx_std_20)

