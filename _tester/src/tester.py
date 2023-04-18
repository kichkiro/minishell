#!/usr/bin/python3

"""
A class to run a set of tests on a given project and evaluate the 
results.
"""

# Libraries ------------------------------------------------------------------>

import signal
import subprocess

from termcolor import colored
import args

# Authorship ----------------------------------------------------------------->

__author__ = "Kirill Chkirov"
__license__ = "other"
__email__ = "kichkiro@student.42firenze.it"
__slack__ = "kichkiro"
__status__ = "Prototype"

# Functions ------------------------------------------------------------------>

class Tester:
    """
    Attributes
    --------------------------------------------------------------------
    project_path : str
        The path to the project to be tested.
    test : str
        The name of the test to run.

    Methods
    --------------------------------------------------------------------
    run():
        Runs the test cases and prints the results.

    Private Methods
    --------------------------------------------------------------------
    __parsing(process, stdout, stderr, args, i):
        Checks if only one philosopher is alive and died in a specific 
        sequence.
    
    """
    
    def __init__(self, project_path: str, exe: str, test: str) -> None:
        self.project_path = project_path
        if test == "single_quotes":
            self.args = args.single_quotes
            self.cmd = [f"{project_path}/{exe}"]
            self.test = lambda process, stdout, stderr, args, i: \
                self.__single_quotes(process, stdout, stderr, args, i)


    def run(self):
        i = 0
        for args in self.args:
            process = subprocess.Popen(
                self.cmd,
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE, 
                stderr=subprocess.PIPE
            )
            try:
                # print(args)
                stdout, stderr = process.communicate(input=b"echo ' \"\" ' '42'", timeout=5)
                self.test(process, stdout, stderr, args, i)
            except subprocess.TimeoutExpired:
                process.send_signal(signal.SIGINT)
                print(colored(
                    f"TEST {i}: KO\n\n    Deadlock detected\n\n    "
                    f"ARGS: {' '.join(args)}\n", 
                    "red"
                ))
            i += 1


    def __single_quotes(self, process, stdout, stderr, args, i):
        if stdout.decode().count('\n') != 2:
            print(colored(
                f"TEST {i}: KO\n\n"
                f"    ARGS: {' '.join(args)}\n",
                "red"
            ))
            print(colored(f"{stdout.decode()}\n", 'white'))
        else:
            print(colored(f"TEST {i}: OK\n", "green"))

