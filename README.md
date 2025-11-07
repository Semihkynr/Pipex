# Pipex

The **Pipex** project is part of the 42 curriculum.  
It aims to recreate the shell’s pipe behavior (`|`) between two commands, managing file descriptors, process creation, and command execution.

---

## 📘 Overview

**Pipex** reproduces the shell command behavior:
< infile cmd1 | cmd2 > outfile

yaml
Kodu kopyala
Your program executes `cmd1` and `cmd2` with their input and output redirected as if you were executing the shell pipeline above.

---

## ⚙️ Mandatory Part

### Program Execution

./pipex infile "cmd1" "cmd2" outfile

markdown
Kodu kopyala

- `infile`: input file.  
- `cmd1`: first command, reading from infile.  
- `cmd2`: second command, reading from the output of cmd1.  
- `outfile`: file where the output of cmd2 will be written.  

### Example

```bash
./pipex infile "ls -l" "wc -l" outfile
Equivalent to:

bash
Kodu kopyala
< infile ls -l | wc -l > outfile
🧠 Key Concepts
Processes (fork, execve, waitpid)

File Descriptors (dup2, open, close)

Pipes (pipe() system call)

Error Handling

Environment Variables (PATH)

🧰 Project Structure
arduino
Kodu kopyala
pipex/
├── pipex.c
├── utils.c
├── Makefile
└── pipex.h
🧾 Compilation
bash
Kodu kopyala
make
This will compile all sources and generate the pipex executable.

🧪 Example Run
Input
infile.txt

nginx
Kodu kopyala
Hello world
42 Istanbul
Command:

bash
./pipex infile.txt "cat" "grep 42" outfile.txt
outfile.txt

Kodu kopyala
42 Istanbul
🧹 Cleaning
bash
Kodu kopyala
make clean     # Remove object files
make fclean    # Remove object files + binary
make re        # Rebuild everything
