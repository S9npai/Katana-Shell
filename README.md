# Katana Shell
**Katana Shell** is a POSIX-compliant command line shell for Linux and other UNIX-like systems, 
built from the ground-up to explore core operating systems concepts and kernel system calls

Inspired by **Operating Systems: Three Easy Pieces (OSTEP) 📕**

## Installation

### Requirements
- Linux distribution (Ubuntu, Fedora, etc.. )
- GNU C/C++ compiler collection ``CXX>=20`` & development libraries: ``libc, libstdc++``

### Setup

**1- Clone the repo:**
```
git clone https://github.com/S9npai/Katana-Shell.git
cd Katana-Shell
```

**2- Configure and build:**
```
cmake -S .
cmake -B build .. -G ninja

cmake --build build
```

---

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
- [ ] File finder **(find)**
- [ ] File creation and deletion **(touch) & (rm)**

### 4- Advanced Features
- [x] Command pipes **( | )**
- [X] **Input/Output** Redirection **(>, >>, <, <<)**
- [ ] Command history

