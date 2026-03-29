#!/usr/bin/bash

# The solutions for subtasks 2-6 must be written into the file created in
# subtask 1, each solution on a new line. All subtasks refer to the current
# user. Subtasks must be solved dynamically – hardcoding the username is not
# allowed. You are not allowed to create your own variables; you must use
# environment variables and/or commands available to you.

#!#!#!#!#!#!#
# 1. Create a file named after the user who is currently using the terminal.

touch "$USER"

#!#!#!#!#!#!#
# 2. Write the user's username into the file (not the real name, but the
# login name).

echo "USER: $USER" >> "$USER"

#!#!#!#!#!#!#
# 3. Write the path of the user's home directory.

echo "HOME DIR: $HOME" >> "$USER"

#!#!#!#!#!#!#
# 4. Write the user's shell.

echo "SHELL: $SHELL" >> "$USER"

#!#!#!#!#!#!#
# 5. Write the names of the groups the user belongs to.

echo "GROUPS: $(groups | cut -d: -f2)" >> "$USER"

#!#!#!#!#!#!#
# 6. Write only the name of the user's primary group.

echo "PRIMARY GROUP: $(id -gn)" >> "$USER"

#!#!#!#!#!#!#
# 7. Delete the file from the previous subtasks.

#cat "$USER"
rm "$USER"

#!#!#!#!#!#!#
# 8. Create a new user named Jonesy.

sudo useradd Jonesy # or adduser - there is a difference though!!

#!#!#!#!#!#!#
# 9. Allow the user Jonesy to temporarily obtain administrative privileges.

sudo usermod -aG sudo Jonesy

#!#!#!#!#!#!#
# 10. Switch to the user Jonesy – log into the shell as that user,
# in their home directory, and with their environment variables.

su - Jonesy

#!#!#!#!#!#!#
# 11. Without changing the current directory, create a new empty file in /tmp.
# Name the file only-me.

touch /tmp/only-me

#!#!#!#!#!#!#
# 12. Make sure that no one (neither group nor others) can do anything with the
# file only-me, except the owner who may only read it.

chmod 400 /tmp/only-me

#!#!#!#!#!#!#
# 13. Without changing other permissions, allow other users to write to
# the file only-me.

chmod o+w /tmp/only-me

#!#!#!#!#!#!#
# 14. Print the group that owns the file only-me.

stat -c %G /tmp/only-me

#!#!#!#!#!#!#
# 15. Using the permission mask command, change the default file creation mode
# so that the owner may only write, while group and others may only read.

umask 244 #default 666 - 244 => 422 r-- -w- -w- valjda??

#!#!#!#!#!#!#
# 16. Log out from the user Jonesy.

exit

#!#!#!#!#!#!#
# 17. Delete the user Jonesy and make sure their home directory
# is also removed.

sudo userdel -r Jonesy

#!#!#!#!#!#!#