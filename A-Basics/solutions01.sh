#!/usr/bin/bash

#!#!#!#!#!#!#
# 1. Print the path of the current working directory.

pwd

#!#!#!#!#!#!#
# 2. Print the contents of the .bash_history file in your home directory.

cat ~/.bash_history

#!#!#!#!#!#!#
# 3. Print the contents of the current user's home directory sorted by
# size, in descending order.

ls -S ~

#!#!#!#!#!#!#
# 4. Without changing the working directory, create a directory named
# "Linux Basics" inside /tmp which will contain the directories Monday,
# Tuesday, Wednesday, Thursday, Friday and a hidden directory Saturday.

mkdir -p /tmp/"Linux Basics"/{monday,tuesday,wednesday,thursday,friday,.saturday}

#!#!#!#!#!#!#
# 5. Without changing the working directory, in the hidden directory Saturday
# from the previous task create empty files named lectures, labs, assignment1,
# assignment2 ... assignment5.

touch /tmp/"Linux Basics"/.saturday/{lectures,labs,assignment{1-5}}

#!#!#!#!#!#!#
# 6. Copy the directory Saturday into the directory Monday.

cp -r /tmp/"Linux Basics"/.saturday /tmp/"Linux Basics"/monday

#!#!#!#!#!#!#
# 7. Print the entire contents of the directory "/tmp/Linux Basics" and the
# contents of all its subdirectories.

ls -R /tmp/"Linux Basics"

#!#!#!#!#!#!#
# 8. In your home directory create a symbolic link named Gatorade to the
# directory /var.

ln -s /var ~/Gatorade

#!#!#!#!#!#!#
# 9. Print the contents of the /var directory using the link created in the
# previous task.

ls ~/Gatorade

#!#!#!#!#!#!#
# 10. Delete the symbolic link Gatorade.

rm ~/Gatorade

#!#!#!#!#!#!#
# 11. Determine how much free disk space remains on the disk mounted on the
# / directory. Make sure the output is in a human-readable format.

df -h /

#!#!#!#!#!#!#
# 12. Determine the type of the files /bin/bash, /etc/passwd and /boot, in
# that order.

file /bin/bash /etc/passwd /boot

#!#!#!#!#!#!#
# 13. Print the inode number and the creation time of the file /etc/hostname
# expressed in seconds since the Epoch.

stat -c '%i %W' /etc/hostname

#!#!#!#!#!#!#