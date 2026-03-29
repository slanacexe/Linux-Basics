#!/usr/bin/bash

# Any hardcoding of solutions is forbidden.

# Tasks 1–8 must be solved without using the grep command.

#!#!#!#!#!#!#
# 1. Sort the output by memory usage.

ps aux --sort=-%mem

#!#!#!#!#!#!#
# 2. Now perform task 1 using the top command.

top -b -n 1 -o %MEM

#!#!#!#!#!#!#
# 3. Print all PIDs of your web browser.
# (Here use the special grep-like command intended for processes)

# You can check the default browser using:
# xdg-settings get default-web-browser
# (I know I use Firefox)
# default browser ... so pgrep -f "browser_name"... hard-coded?? :(

pgrep -f firefox

#!#!#!#!#!#!#
# 4. Print processes with PPID equal to 2.

ps --ppid 2

#!#!#!#!#!#!#
# 5. Print processes with PID 1, 4, and 7.

ps -q 1,4,7 # or simply: ps 1 4 7

#!#!#!#!#!#!#
# 6. Print the process tree for the current user.

pstree $USER

#!#!#!#!#!#!#
# 7. Print all signals available on your system.

kill -l

#!#!#!#!#!#!#
# 8. Print the list of shells available on the system.

cat /etc/shells

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

./signal_handler &

#!#!#!#!#!#!#
# 10. Find the PID of that program.

pgrep -nx signal_handler

#!#!#!#!#!#!#
# 11. Try to kill the process using kill, then try to kill it
# by sending the appropriate signal.
# Note: Two commands are required.

kill -SIGTERM "$(pgrep -nx signal_handler)" # or killalll ...
kill -SIGKILL "$(pgrep -nx signal_handler)"

#!#!#!#!#!#!#
# 12. Run the program in the background and send it the SIGUSR1 signal.
# Note: Two commands are required.

./signal_handler &
kill -SIGUSR1 "$(pgrep -nx signal_handler)"

#!#!#!#!#!#!#
# 13. Send it the SIGINT signal.

kill -SIGINT "$(pgrep -nx signal_handler)"

#!#!#!#!#!#!#
# 14. Run the program in the background and send it the SIGUSR2 signal.
# Note: Two commands are required.

./signal_handler &
kill -SIGUSR2 "$(pgrep -nx signal_handler)"

#!#!#!#!#!#!#