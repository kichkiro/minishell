<img src="https://github.com/kichkiro/kichkiro/blob/main/assets/minishell_banner.jpg?raw=true" width="100%"/>

# Minishell

<i>
	<p>
		The existence of shells is linked to the very existence of IT.
	</p>
	<p>
		At the time, all developers agreed that communicating with a computer using aligned 1/0 switches was seriously irritating.
	</p>
	<p>
		It was only logical that they came up with the idea of creating a software to communicate with a computer using interactive lines of commands in a language somewhat close to the human language.
	</p>
	<p>
		Thanks to Minishell, you’ll be able to travel through time and come back to problems people faced when Windows didn’t exist.
	</p>
</i>

#### <i>[subject](_subject/en.subject.pdf) v.6</i>

<details>
<summary><i><b>Project Structure  📂</b></i></summary>

``` js
├── README.md
├── LICENSE
├── Dockerfile
├── _notebook
│   ├── bash.ipynb
│   └── minishell.ipynb
├── _subject
│   └── en.subject.pdf
├── _tester
│   └── -> minishell_tester
└── project
    ├── Makefile
    ├── readline.supp
    ├── include
    │   └── minishell.h
    ├── lib
    │   ├── libft.a
    │   └── libft.h
    └── src
        ├── _lst
        │   ├── lst_add_back.c
        │   ├── lst_free.c
        │   ├── lst_free_last.c
        │   ├── lst_new.c
        │   ├── lst_set_to_head.c
        │   └── lst_set_to_last.c
        ├── main
        │   ├── bombfreeall.c
        │   ├── history.c
        │   ├── init.c
        │   ├── main.c
        │   ├── prompt.c
        │   └── signal_handler.c
        ├── parser
        │   ├── parsing_ext.c
        │   ├── parsing_system.c
        │   ├── variable_expand.c
        │   └── wildcards.c
        ├── executor
        │   ├── booleans.c
        │   ├── builtins.c
        │   ├── execution_system.c
        │   ├── fd_handler.c
        │   ├── heredoc.c
        │   ├── pipes.c
        │   └── redirections.c
        ├── errors
        │   ├── errors_handler.c
        │   ├── invalid_prompt.c
        │   └── syntax_errors.c
        └── variables
            ├── env_variables.c
            ├── export_variables.c
            └── shell_variables.c
```
</details>

## 📌 - Key Topics
### Shell 
This project involves the creation of a custom Unix shell, implementing a wide range of shell functionalities, including command execution, redirections, pipes, and signal handling. 

A strong grasp of shell mechanics and Unix system calls is crucial to meeting the project requirements.

### Processes 
Process control is central to this project, with tasks like forking, executing, and waiting for processes to terminate. 

The shell must handle multiple processes, manage pipelines, and ensure correct signal handling, such as handling interrupts (Ctrl+C, Ctrl+D, Ctrl+).

## 🛠️ - Usage

```sh
git clone https://github.com/kichkiro/minishell.git
cd minishell/
docker build -t minishell:42 .
docker run -d --rm --name minishell minishell:42
```

It's now possible to start minishell:

```sh
docker exec -t -it minishell minishell
```

and enjoy yourself...

<img src="https://github.com/kichkiro/kichkiro/blob/main/assets/prompt_minishell.gif?raw=true" width="100%"/>

## 📈 - Tester

The tester [minishell_tester](https://github.com/kichkiro/minishell_tester) performs more than 200 tests on the main features of the project, including:

- Parsing
- Commands
- Redirects
- Pipes
- Exit Status
- Mixed Mandatory
- Booleans
- Wildcards

The tester launches Bash and Minishell processes with the Popen method of Python's subprocess library, inputs the same test, captures the output, and compares it.

<img src="https://github.com/kichkiro/kichkiro/blob/main/assets/minishell_tester_usage.gif?raw=true" width="100%"/>

NOTE: The tester was tested on Ubuntu 20.04 LTS with Python version 3.8.

## ⚖️ - License

See [LICENSE](LICENSE)