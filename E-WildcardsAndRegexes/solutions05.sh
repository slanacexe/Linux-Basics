#!/usr/bin/bash

#!#!#!#!#!#!#
# 1. Print the names of all directories in /usr/share whose names
# start with gtk.
# (must be solved using wildcards)

ls -d /usr/share/gtk*

#!#!#!#!#!#!#
# 2. Print the names of all directories in /usr/share whose names
# contain at least two digits.
# (must be solved using wildcards)

ls -d /usr/share/*[0-9]*[0-9]*

#!#!#!#!#!#!#
# 3. Find words that contain digits (if any exist).

grep -E "[0-9]" /usr/share/dict/words  # of course, there are none :)

#!#!#!#!#!#!#
# 4. Find words that start with the letter i and contain an uppercase
# letter somewhere in the middle of the word.
# Note: For simplicity, the middle of the word is defined as the part
# between the first and the last character.

grep -E "^i.+[A-Z].+$" /usr/share/dict/words

#!#!#!#!#!#!#
# 5. Find words that do not contain vowels (neither uppercase nor lowercase).
# Note: Vowels are aeiou. Vowels from other languages are not included.

grep -E "^[^aeiouAEIOU]+$" /usr/share/dict/words

#!#!#!#!#!#!#
# 6. Find words in which at least two vowels appear consecutively.

grep -E "[aeiouAEIOU]{2,}" /usr/share/dict/words

#!#!#!#!#!#!#
# 7. Without using the wc command, count the words that end with ening.

grep -Ec "ening$" /usr/share/dict/words

#!#!#!#!#!#!#
# 8. Without using the wc command, count the words that end with 's.

grep -Ec "'s$" /usr/share/dict/words

#!#!#!#!#!#!#
# 9. Without using the wc command, count the words that end with
# an uppercase letter.

grep -Ec "[A-Z]$" /usr/share/dict/words

#!#!#!#!#!#!#
# 10. For all words that end with 's, remove the character '.

sed -E "s/'s$/s/" /usr/share/dict/words

#!#!#!#!#!#!#
# 11. Move every occurrence of the substring word to the beginning of
# the word in which it appears.

sed -E "s/^(.*)(word)(.*)$/\2\1\3/" /usr/share/dict/words # word is the second of three groups; we move it to the first position

#!#!#!#!#!#!#
# 12. For all words that start with an uppercase letter, change the first
# letter to lowercase and the last letter to uppercase.
# Example: Iowa -> iowA

sed -E "s/^([A-Z])(.*)([[:alpha:]])$/\L\1\2\U\3/" /usr/share/dict/words # first group lower, third group upper (first and last letter)

#!#!#!#!#!#!#