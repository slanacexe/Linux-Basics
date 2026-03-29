#!/usr/bin/bash

#!#!#!#!#!#!#
# 1. Using the echo command and redirection, create a file named testFile.dat
# that contains today’s date inside it. (The date must not be hard-coded)

date > testFile.dat

#!#!#!#!#!#!#
# 2. Using the cat command and a here document, append the string "LINUX"
# on the line below the date in the file from the previous task.
# A multi-line solution is allowed.

cat <<EOF >> testFile.dat
LINUX
EOF

#!#!#!#!#!#!#
# 3. Using the tee command, append the line "linux <3" to the end of the
# file from the previous two tasks.

echo "linux <3" | tee -a testFile.dat

#!#!#!#!#!#!#
# 4. Print all files from the current user's home directory whose last
# modification time was in October. (HINT: it is enough to use ls and grep
# for "Oct")

ls -l ~ | grep " Oct "

#!#!#!#!#!#!#
# 5. Sort the file users.dat in ascending order by the number before
# the username and save the result to the file users.sorted.dat.

sort -n users.dat > users.sorted.dat

#!#!#!#!#!#!#
# 6. Print all unique usernames from the file users.dat into the file
# unique_users.dat. Assume that usernames are case insensitive.

cut -d: -f2 users.dat | sort -f | uniq -i > unique_users.dat

#!#!#!#!#!#!#
# 7. Print all non-unique usernames from the file users.dat into the file
# duplicate_users.dat. Assume that usernames are case insensitive.

cut -d: -f2 users.dat | sort -f | uniq -i -d > duplicate_users.dat

#!#!#!#!#!#!#
# 8. Count how many words from the file /usr/share/dict/words contain
# the text "ping".

grep -w -c "ping" /usr/share/dict/words

#!#!#!#!#!#!#
# 9. Extract all words from /usr/share/dict/words that contain
# the text "you" into the file yous.dat.

grep "you" /usr/share/dict/words > yous.dat

#!#!#!#!#!#!#
# 10. Count the number of words from the previous task.

wc -l yous.dat

#!#!#!#!#!#!#
# 11. Locate the file unique_users.dat using the find command.

find ~ -name "unique_users.dat"

#!#!#!#!#!#!#
# 12. Locate the file unique_users.dat using the locate command.
# A multi-line solution is allowed.

locate unique_users.dat

#!#!#!#!#!#!#