#!/usr/bin/python3

"""
Arguments for testing.
"""

# Authorship ----------------------------------------------------------------->

__author__ = "Kirill Chkirov"
__license__ = "other"
__email__ = "kichkiro@student.42firenze.it"
__slack__ = "kichkiro"
__status__ = "Prototype"

# ARGS ----------------------------------------------------------------------->

echo = {
    b"echo ": "",
    b"echo hello world !": "hello world !",
    b"echo 42test ' 21 '": "42test  21 ",
    b"echo 42   42    '  '42": "42 42   42",
    b"echo 'echo $v >> file.txt'": "echo $v >> file.txt",
    b"echo ' \"\" ' '42'": " \"\"  42",
	b"echo '$?'": "$?",
    b"echo '${$?}'": "${$?}",
    b"echo 42' '42": "42 42",
    b"echo '$USER'": "$USER",
    b"echo '<< | | >>'42": "<< | | >>42",
    b"echo ''": "",
    b"echo ''''42''": "42",
    b"echo $'USER'": "USER",
    b"echo $'USER'USER": "USERUSER",
    b"echo a'b'c'd'e'f'g'h'i'j'k'l'm'n'o'p'q'r's't'": "abcdefghijklmnopqrst",
    b"echo a'b'c'd'e'f'g'h'i'j'k'l'm''": "abcdefghijklm",
    b"echo \" \"'$USER\"'\"42 \" ''\"  | << -1\"": " $USER\"42    | << -1",
    b"echo \"<< EOF\"": "<< EOF",
}




























































