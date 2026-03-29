# LinuxBasics

![Linux](https://img.shields.io/badge/Platform-Linux-black?logo=linux)
![Bash](https://img.shields.io/badge/Shell-Bash-4EAA25?logo=gnubash&logoColor=white)
![C](https://img.shields.io/badge/Language-C-00599C?logo=c&logoColor=white)
![GCC](https://img.shields.io/badge/Compiler-GCC-red?logo=gnu)
![Status](https://img.shields.io/badge/Status-Active-success)

CREDITS: Računarska sekcija KSET-a

A structured and practical collection of Linux command-line exercises and solutions,  
designed to build strong foundational knowledge in Unix/Linux systems.

This repository focuses on **hands-on learning**, reinforcing essential concepts  
through shell scripting, process management, permissions, signals, and regular expressions.

---

## 🧠 Topics Covered

- Shell fundamentals and command-line usage
- File system operations
- Users, groups, and permission management
- Process inspection and control
- Unix signals
- Wildcards (globbing)
- Regular expressions (grep, sed)
- Introductory C programs interacting with OS-level concepts

---

## 🚨 Special Focus: Signals & Interrupt Handling

The **D-Signals** section is the most conceptually important part of this repository.

It includes:

- Process management (`ps`, `pgrep`, `kill`, `top`)
- Dynamic PID handling (no hardcoding)
- Working with Unix signals:
  - `SIGINT`
  - `SIGTERM`
  - `SIGKILL`
  - `SIGUSR1`
  - `SIGUSR2`
- A C-based signal handling program (`signal_handler.c`)
- A priority-based interrupt simulation (`priority_interrupt_simulation.c`) that demonstrates:
  - Interrupt prioritization
  - Preemption
  - Pending interrupt queues
  - Stack-based context simulation
  - Timeline-based execution tracking

This section bridges practical Linux process management with  
core Operating System concepts such as interrupt handling and context switching.

---

## 🛠 Recommended Workflow

1. Attempt each `exercisesXX.sh` file independently.
2. Avoid hardcoding values (especially usernames and PIDs).
3. Compare with `solutionsXX.sh`.
4. Test everything in a safe environment (VM, WSL, or container).

---

## ⚙️ Requirements

- Linux or Unix-like environment
- Bash shell
- GCC (for compiling C programs in the Signals section)

---

## 🎯 Purpose

This repository is intended for:

- Reinforcing Linux fundamentals
- Preparing for OS / Systems coursework
- Practicing process and signal management
- Strengthening command-line fluency

---

> “Understanding signals and process control is where Linux stops being a shell and starts being an operating system.”