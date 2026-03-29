#!/usr/bin/bash

# Any hardcoding of solutions is forbidden.

# Tasks 1–8 must be solved without using the grep command.

#!#!#!#!#!#!#
# 1. Sort the output by memory usage.



#!#!#!#!#!#!#
# 2. Now perform task 1 using the top command.



#!#!#!#!#!#!#
# 3. Print all PIDs of your web browser.
# (Here use the special grep-like command intended for processes)

# You can check the default browser using:
# xdg-settings get default-web-browser
# (I know I use Firefox)
# default browser ... so pgrep -f "browser_name"... hard-coded?? :(



#!#!#!#!#!#!#
# 4. Print processes with PPID equal to 2.



#!#!#!#!#!#!#
# 5. Print processes with PID 1, 4, and 7.



#!#!#!#!#!#!#
# 6. Print the process tree for the current user.



#!#!#!#!#!#!#
# 7. Print all signals available on your system.



#!#!#!#!#!#!#
# 8. Print the list of shells available on the system.



#!#!#!#!#!#!#

# Tasks 9–14 refer to the C program signal_handler.c
# Pay special attention that in tasks 12–15 you must not hardcode
# the program PID!

#!#!#!#!#!#!#
# 9. Run the program in the background.
# Note: The program must first be compiled (e.g. gcc signal_handler.c)
# and, if necessary, permissions adjusted (e.g. chmod +x filename).
# Name the output file signal_handler when compiling.
# Do not include the compilation and permission commands in the solution.



#!#!#!#!#!#!#
# 10. Find the PID of that program.



#!#!#!#!#!#!#
# 11. Try to kill the process using kill, then try to kill it
# by sending the appropriate signal.
# Note: Two commands are required.



#!#!#!#!#!#!#
# 12. Run the program in the background and send it the SIGUSR1 signal.
# Note: Two commands are required.



#!#!#!#!#!#!#
# 13. Send it the SIGINT signal.



#!#!#!#!#!#!#
# 14. Run the program in the background and send it the SIGUSR2 signal.
# Note: Two commands are required.



#!#!#!#!#!#!#