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
        src/signals.cpp
        src/redirection.cpp
        src/utils.cpp
        src/commands/filesys.cpp
        src/commands/sysinfo.cpp
        src/helpers.cpp
)

target_include_directories(Katana-Shell PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
target_compile_features(Katana-Shell PRIVATE cxx_std_20)

target_compile_definitions(Katana-Shell PRIVATE
        KATANA_DATA_SUFFIX=".local/share/katana-shell"
        KATANA_HISTORY_SUFFIX=".katana_history"
)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local" CACHE PATH "Install prefix" FORCE)
endif()

install(TARGETS Katana-Shell
        RUNTIME DESTINATION bin)

install(FILES "Katana-Shell reference.txt"
        DESTINATION share/katana-shell)

add_custom_target(uninstall
        COMMAND rm -f "$ENV{HOME}/.local/bin/Katana-Shell"
        COMMAND rm -rf "$ENV{HOME}/.local/share/Katana-shell"
        COMMENT "Uninstalling Katana-Shell..."
)

