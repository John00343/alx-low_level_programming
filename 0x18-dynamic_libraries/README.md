# 0x18. C - Dynamic libraries

## Overview

This project involves creating dynamic libraries in C, understanding their usage, creation, and the differences between static and shared libraries. The learning objectives include working with environment variables, using tools like `nm`, `ldd`, and `ldconfig`, and understanding the basics of dynamic linking.

## Resources

Read or watch:

- [Difference between Dynamic and Static library](https://www.geeksforgeeks.org/static-vs-dynamic-libraries/)
- [Create dynamic libraries on Linux](https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html)

## Learning Objectives

By the end of this project, you should be able to:

- Explain what a dynamic library is and how it works.
- Create a dynamic library and understand its usage.
- Use the environment variable `$LD_LIBRARY_PATH`.
- Differentiate between static and shared libraries.
- Utilize basic tools like `nm`, `ldd`, and `ldconfig` for library analysis.

## Copyright - Plagiarism

- Solutions should be developed independently to meet the learning objectives.
- Publishing any content of this project is strictly prohibited.
- Plagiarism will result in removal from the program.

## Requirements

### C

- Editors allowed: vi, vim, emacs
- Compilation on Ubuntu 20.04 LTS using gcc with options -Wall -Werror -Wextra -pedantic -std=gnu89
- Files should end with a new line.
- Mandatory README.md file at the project root describing the project.

### Bash

- Editors allowed: vi, vim, emacs
- Scripts tested on Ubuntu 20.04 LTS
- Files should end with a new line.
- The first line of all scripts should be exactly `#!/bin/bash`.
- A README.md file at the project root describing each script's purpose.
- All scripts must be executable.

## Tasks

### 0. A library is not a luxury but one of the necessities of life

Create the dynamic library `libdynamic.so` containing various functions as specified in the task.

```bash
ls -la lib*
nm -D libdynamic.so
cat 0-main.c
gcc -Wall -pedantic -Werror -Wextra -L. 0-main.c -ldynamic -o len
ldd len
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
ldd len
./len
```

### 1. Without libraries what have we? We have no past and no future

Create a script, `1-create_dynamic_lib.sh`, that creates a dynamic library called `liball.so` from all `.c` files in the current directory.

```bash
ls *.c
./1-create_dynamic_lib.sh
nm -D --defined-only liball.so
```

### 2. Let's call C functions from Python

Create a dynamic library, `100-operations.so`, containing C functions that can be called from Python. An example script (`100-tests.py`) demonstrates the usage.

```bash
cat 100-tests.py
python3 100-tests.py
```

### 3. Code injection: Win the Giga Millions!

Create a shell script, `101-make_me_win.sh`, for code injection to make the user win the Giga Millions jackpot.

```bash
cat 101-make_me_win.sh
```

**Note:** This script is designed for educational purposes and should not be used for any malicious activities. It demonstrates the concept of code injection using `LD_PRELOAD`.
