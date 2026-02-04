cmake_minimum_required(VERSION 3.30)
project(Katana-Shell VERSION 1.0
        DESCRIPTION "A POSIX-compliant linux shell"
        LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)

add_executable(Katana_Shell src/main.cpp)
#target_link_libraries(Katana_Shell ncurses)
