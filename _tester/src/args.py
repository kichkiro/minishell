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

single_quotes = {
	# ("v=42", "echo '$v'"): "$v",
    # ("v=42", "echo '$v'$v"): "$v42",
    "echo 'echo $v >> file.txt'": "echo $v >> file.txt",
    "echo ' \"\" ' '42'": "\"\"  42",
	"echo '$?'": "$?",
    "echo '${$?}'": "${$?}",
}

# double_quotes = {
    
# }

# var_expands = {
    
# }
