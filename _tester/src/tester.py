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
    ---------------
    __echo(process, stdout, stderr, args, i) -> None
        Runs the "echo" test case.

    Notes
    --------------------------------------------------------------------
    The Tester class is designed to run tests on a project executable. 
    The test cases are run using subprocess.Popen, which allows for 
    running external programs and capturing their output.
    """
    
    def __init__(self, project_path: str, exe: str, test: str) -> None:
        self.project_path = project_path
        if test == "echo":
            self.args = args.echo
            self.cmd = [f"{project_path}/{exe}"]
            self.test = lambda process, stdout, stderr, args, i: \
                self.__echo(process, stdout, stderr, args, i)


    def run(self):
        i = 0
        for test_input, bash_output in self.args.items():
            process = subprocess.Popen(
                self.cmd,
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE, 
                stderr=subprocess.PIPE
            )
            try:
                stdout, stderr = process.communicate(
                    input=test_input, timeout=5)
                self.test(process, stdout, stderr, self.args, i)
            except subprocess.TimeoutExpired:
                process.send_signal(signal.SIGINT)
                print(colored(
                    f"TEST {i}: KO\n\n    Timeout\n\n    "
                    f"ARGS: {' '.join(args)}\n", 
                    "red"
                ))
            i += 1


    def __echo(self, process, stdout, stderr, args, i):
        def output_line(stdout, test_input):
            output = None
            next_line = False
            lines = stdout.decode().split('\n')
            for line in lines:
                if next_line:
                    output = line
                    break
                if test_input in line:
                    next_line = True
            return output

        test_input = (list(args.keys()))[i]
        bash_output = args[test_input]
        minishell_output = output_line(stdout, test_input.decode())
        if bash_output not in minishell_output:
            print(colored(
                f"TEST {i + 1}: KO\n\n"
                f"    Input:     {test_input.decode()}\n"
                f"    Bash:      {bash_output}\n"
                f"    Minishell: {minishell_output}\n",
                "red"
            ))
        else:
            print(colored(
                f"TEST {i + 1}: OK\n\n"
                f"    Input:     {test_input.decode()}\n"
                f"    Output:    {minishell_output}\n",
                "green"
            ))

