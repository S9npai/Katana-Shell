# Katana Shell
**Katana Shell** is a POSIX-compliant command line shell for Linux and other UNIX-like systems, 
built from the ground-up to explore core operating systems concepts and kernel system calls

Inspired by **Operating Systems: Three Easy Pieces (OSTEP) 📕**

![Screenshot](assets/)

## Installation

### Prerequisites
- Linux distribution (Ubuntu, Fedora, etc.. )
- CMake ≥ 3.20
- Ninja
- A **C/C++ >= 20** compatible compiler **(GCC 13+ or Clang 19+)**

**Setup & Install**
```
git clone https://github.com/S9npai/Katana-Shell
cd Katana-Shell
cmake -S . -B build -G Ninja
cmake --build build
cmake --install build
```
**This installs:**
- ```Binary → ~/.local/bin/Katana-Shell```
- ```Manual → ~/.local/share/katana-shell/```


**Note:** Make sure ~/.local/bin is in your PATH. If not, add this to your ~/.bashrc or ~/.zshrc:
```export PATH="$HOME/.local/bin:$PATH"```<br> 
Then run ```source ~/.bashrc``` or ```source ~/.zshrc``` to apply 

**Uninstall:** ```cmake --build build --target uninstall``` <br>
This removes the binary and the manual directory. Your history file (~/.katana_history) is left untouched — delete it manually if needed:

---

## Project Structure
```
.
├── CMakeLists.txt                  # Build configuration
├── Katana-Shell reference.txt      # User-facing command reference manual
├── README.md
└── src/
    ├── main.cpp                    # Entry point — REPL loop, signal setup, input dispatch
    ├── parser.cpp                  # Tokenizer: parses raw input into Command and pipeline structs
    ├── executor.cpp                # Executes single commands (builtins or external via fork/exec)
    ├── pipeline.cpp                # Handles multi-command pipelines with pipe()/fork()
    ├── signals.cpp                 # Signal handling: parent/child sigaction setup, SIGCHLD blocking
    ├── helpers.cpp                 # Utilities: env var expansion, path expansion
    ├── execindex.cpp               # Builtin command registry (maps names → function pointers)
    ├── redirection.cpp             # I/O redirection handler (<, >, >>, 2>)
    ├── utils.cpp                   # History management (load, save, add, display) + manual display
    ├── commands/
    │   ├── filesys.cpp             # Filesystem builtins: cd, ls, mkdir, rm, cp, mv, etc...
    │   └── sysinfo.cpp             # System info builtins: username, hostname, etc...
    └── include/
        ├── types.hpp               # Core data structures: Command, pipeline, RedirectMode
        ├── parser.hpp
        ├── executor.hpp
        ├── pipeline.hpp
        ├── signals.h
        ├── helpers.hpp
        ├── execindex.hpp
        ├── redirection.hpp
        ├── utils.h
        ├── logo.h                  # ASCII art logo drawn on startup
        ├── commands.h              # Aggregated include for all builtin command headers
        └── cmdheaders/
            ├── filesys.hpp         # Declarations for filesystem builtins
            └── sysinfo.hpp         # Declarations for system info builtins
```

## To-Do
### 1- Project Setup
- [x] README guide

### 2- Core
- [x] Shell prompt & logo
- [x] Exit
- [x] Session hostname & username (**whoami** + **hostname**)

### 3- Commands
- [x] Command parsing
- [x] Fork & controlling processes via **fork()**, **execvp()** and **waitpid()**
- [x] List directory contents **(ls)**
- [x] Current directory (pwd)
- [x] Moving files and directories **(mv)** 
- [x] Deleting directories **(rmdir)**
- [X] File finder **(find)**
- [X] File creation and deletion **(touch) & (rm)**

### 4- Advanced Features
- [x] Command pipes **( | )**
- [X] **Input/Output** Redirection **(>, >>, <, <<)**
- [ ] Command history


