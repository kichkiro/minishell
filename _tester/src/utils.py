#!/usr/bin/python3

"""
A set of utils functions.
"""

# Libraries ------------------------------------------------------------------>

import subprocess

from termcolor import colored

# Authorship ----------------------------------------------------------------->

__author__ = "Kirill Chkirov"
__license__ = "other"
__email__ = "kichkiro@student.42firenze.it"
__slack__ = "kichkiro"
__status__ = "Prototype"

# Functions ------------------------------------------------------------------>

def banner():
    """
    Print a formatted banner with ASCII art.
    
    Returns:
        None
    """
    print(colored(        
        "    __  ___ _         _        __           __ __ \n"
        "   /  |/  /(_)____   (_)_____ / /_   ___   / // / \n"
        "  / /|_/ // // __ \ / // ___// __ \ / _ \ / // /  \n"
        " / /  / // // / / // /(__  )/ / / //  __// // /   \n" 
        "/_/  /_//_//_/ /_//_//____//_/ /_/ \___//_//_/    \n" 
        "  ______             __                           \n" 
        " /_  __/___   _____ / /_ ___   _____              \n" 
        "  / /  / _ \ / ___// __// _ \ / ___/              \n" 
        " / /  /  __/(__  )/ /_ /  __// /                  \n" 
        "/_/   \___//____/ \__/ \___//_/                 \n\n",
        "red",
    ))


def makefile(rules: str, must_print: bool, project_path: str):
    """
    Run the make command with specified rules on a given project path.
    
    Args:
        rules (str): The makefile rules to run.
        must_print (bool): Whether to print output or not.
        project_path (str): The path to the project directory.

        Returns:
        None
    """
    if rules != "":
        process = subprocess.Popen(
            ["make", rules, "-C", project_path], 
            stdout=subprocess.PIPE, 
            stderr=subprocess.PIPE
        )
    else:
        process = subprocess.Popen(
            ["make", "-C", project_path], 
            stdout=subprocess.PIPE, 
            stderr=subprocess.PIPE
        )
    stdout, stderr = process.communicate()
    if not process.returncode and must_print:
        print(colored("Make: OK\n", "green",))
    elif process.returncode:
        print(colored(f"Make: KO!\n\n    {stderr.decode('utf-8')}", "red"))
        exit(1)