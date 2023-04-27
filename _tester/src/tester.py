#!/usr/bin/python3

"""
A class to run a set of tests on a given project and evaluate the 
results.
"""

# Libraries ------------------------------------------------------------------>

import os
import re
import signal
import shutil
import subprocess
import tempfile
import pprint as pp

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
    __echo(...) <- DOCUMENT FROM HERE

    Notes
    --------------------------------------------------------------------
    The Tester class is designed to run tests on a project executable. 
    The test cases are run using subprocess.Popen, which allows for 
    running external programs and capturing their output.
    """
    
    def __init__(self, project_path: str, exe: str, test: str) -> None:

        self.project_path = project_path
        if test == "echo":
            self.name = "echo"
            self.cmd = ([f"{project_path}/{exe}"])
            self.args = args.echo
            self.test = lambda process, stdout, stderr, args, i, test_files, \
                lab: self.__echo(process, stdout, stderr, args, i, test_files,\
                lab)
        elif test == "redirects":
            self.name = "redirects"
            self.cmd = ([f"{project_path}/{exe}"])
            self.args = args.redirect
            self.test = lambda process, stdout, stderr, args, i, test_files, \
                lab: self.__redirects(process, stdout, stderr, args, i, \
                test_files, lab)


    def run(self):  
        
        i = 0
        for test_input in self.args:
            lab = tempfile.mkdtemp()
            os.chdir(lab)
            test_files = self.init_lab(lab)
            process = subprocess.Popen(
                self.cmd,
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE, 
                stderr=subprocess.PIPE,
            )
            try:
                stdout, stderr = process.communicate(
                    input=test_input.encode(), 
                    timeout=1
                )
                if process.returncode == -11:
                    print(colored(
                    f"TEST {i + 1}: KO\n    Segmentation fault\n    "
                    f"ARGS: {test_input}\n", 
                    "red"
                ))
                else:
                    self.test(process, stdout, stderr, test_input, i, \
                        test_files, lab)
            except subprocess.TimeoutExpired:
                process.send_signal(signal.SIGINT)
                print(colored(
                    f"TEST {i}: KO\n    Timeout\n    "
                    f"ARGS: {test_input}\n", 
                    "red"
                ))
            finally:
                i += 1
                shutil.rmtree(lab)


    # def output_line(self, stdout, test_input):

    #         output = ""
    #         next_line = False
    #         try:
    #             lines = stdout.decode().split('\n')
    #         except UnicodeDecodeError:
    #             lines = stdout.decode('latin-1').split('\n')
    #         for line in lines:
    #             if next_line:
    #                 for char in line:
    #                     if char not in "!@#$%^&*()_+-=[]{}|;':\"<>,.?/\\":
    #                         output += char
    #                     else:
    #                         break
    #             if test_input in line:
    #                 next_line = True
    #         # regex_bytes = br'\x1b\[([0-9]{1,2}(;[0-9]{1,2})?)?[m|K]'
    #         # output = re.sub(regex_bytes, b'', output.encode()).decode()
    #         print(output)
    #         return output
    
    def output_line(self, stdout, test_input):
        output = ""
        next_line = False
        try:
            lines = stdout.decode().split('\n')
        except UnicodeDecodeError:
            lines = stdout.decode('latin-1').split('\n')
        for line in lines:
            if next_line:
                for char in line:
                    if char != '\x1b':
                        output += char
                    else:
                        break
                break
            if test_input in line:
                next_line = True
        return output


    

    def init_lab(self, lab: str) -> tuple:

        filenames = ["file1", "file2", "file3", "file4"]
        paths = [os.path.join(lab, filename) for filename in filenames]
        contents = [filename[-1] for filename in filenames]

        for path, content in zip(paths, contents):
            with open(path, 'w') as file:
                file.write(content)

        return tuple(paths)


    def clean_lab(self, files: tuple) -> None:

        for file in files:
            if os.path.exists(file):
                os.remove(file)


    def __echo(self, process, stdout, stderr, args, i, test_files, lab):

        def print_result(status, bash_output, minishell_output):
            if status == "OK":
                color = "green"
                print(colored(
                    f"TEST {i + 1}: {status}\n",
                    color
                ))
            else:
                color = "red"
                print(colored(
                    f"TEST {i + 1}: {status}\n"
                    f"    Input:     {args}\n"
                    f"    Bash:      {bash_output}\n"
                    f"    Minishell: {minishell_output}\n",
                    color
                ))

        minishell_output = self.output_line(stdout, args)
        bash_path = subprocess.check_output("which bash", shell=True).decode()
        bash_output = subprocess.check_output(
            args, 
            shell=True, 
            executable=bash_path.strip('\n')
        ).decode().strip("\n")

        if minishell_output == bash_output or minishell_output[:-1] == bash_output:
            print_result("OK", bash_output, minishell_output)
        else:
            print_result("KO", bash_output, minishell_output)
    

    def __redirects(self, process, stdout, stderr, args, i, test_files, lab):

        def print_result(status, bash_output, minishell_output, \
            bash_file_content, minishell_file_content):

            if status == "OK":
                color = "green"
                print(colored(
                    f"TEST {i + 1}: {status}\n",
                    color
                ))
            else:
                color = "red" 
                print(colored(
                    f"TEST {i + 1}: {status}\n"
                    f"    Input:     {args}\n"
                    f"    Bash:      {bash_output}\n"
                    f"    Minishell: {minishell_output}\n\n"
                    f"    Files content BASH:",
                    color
                ))
                for key, value in bash_file_content.items():
                    print(colored(
                        f"      {key}: {value}",
                        color
                    ))
                print(colored("\n    Files content MINISHELL:", color))
                for key, value in bash_file_content.items():
                    print(colored(
                        f"      {key}: {value}",
                        color
                    ))
                print()

        minishell_output = self.output_line(stdout, args)
        minishell_file_content = {}
        for file in test_files:
            with open(file, 'r') as f:
                minishell_file_content[file[-5:]] = f.read()

        self.clean_lab(test_files)
        self.init_lab(lab)

        bash_path = subprocess.check_output("which bash", shell=True).decode()
        bash_output = subprocess.check_output(
            args, 
            shell=True, 
            executable=bash_path.strip('\n')
        ).decode().strip("\n")

        bash_file_content = {}
        for file in test_files:
            with open(file, 'r') as f:
                bash_file_content[file[-5:]] = f.read()

        self.clean_lab(test_files)

        if minishell_output == bash_output and minishell_file_content \
            == bash_file_content:
            print_result("OK", bash_output, minishell_output,\
                bash_file_content, minishell_file_content)
        else:
            print_result("KO", bash_output, minishell_output,\
                bash_file_content, minishell_file_content)
