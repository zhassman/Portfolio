## Project Overview

### `myshell` - A Simple Shell Program

This C program implements a straightforward shell environment, named `myshell`, which allows users to execute commands interactively or batch process commands from a file. The shell is tailored for Unix-like systems and offers basic functionality necessary for typical shell operations.

### Features

- **Interactive and Batch Modes:** Users can enter commands directly or run a series of commands from a file.
- **Built-in Commands:** Includes basic shell commands like `cd` (change directory), `pwd` (print working directory), and `exit` (exit the shell).
- **Input/Output Redirection:** Redirects the output of commands to files.
- **Advanced Appending Redirection:** Supports appending the output to the end of existing files without overwriting.
- **Command Parsing:** Efficiently parses user input to handle multiple commands separated by semicolons.
- **Error Handling:** Robust error management to handle common user input errors and file handling issues.

### Implementation Details

`myshell` utilizes a variety of system calls and processes control mechanisms such as `fork()`, `execvp()`, and `dup2()` to manage command execution and redirection. This setup ensures that `myshell` behaves similarly to more sophisticated shells while maintaining simplicity and ease of use.

### Usage

To run `myshell` in interactive mode, simply start the program without any arguments. For batch mode, provide the filename containing the batch commands as an argument to `myshell`.

```bash
./myshell               # Start in interactive mode
./myshell batchfile.sh  # Start in batch mode with commands from 'batchfile.sh'
