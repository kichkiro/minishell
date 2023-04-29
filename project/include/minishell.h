/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:51:51 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/29 20:58:35 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Libraries ------------------------------------------------------------------>
# include "../lib/libft/include/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>

// Handlers REQUESTS ---------------------------------------------------------->
# define RESTORE	0
# define GET		1
# define SET		2

# define PRINT		3
# define PRINT_FREE 4

# define SET_LAST	5
# define GET_LAST	8

// Token TYPES ---------------------------------------------------------------->
# define NONE		0
# define STANDARD	1
# define REDIRECT	2
# define PIPE		3
# define BOOLEAN    4
# define WILDCARD	5

// Variables TYPES ------------------------------------------------------------>
# define ENV		0
# define EXPORT		1
# define SHELL		2

// Linked Lists --------------------------------------------------------------->
typedef struct s_var
{
	char			*name;
	char			*value;
	char			type;
	struct s_var	*next;
	struct s_var	*prev;
}	t_var;

void	t_var_add_back(t_var **lst, t_var *new_node);
void	*t_var_free(t_var **lst);
t_var	*t_var_new(char	*name, char *value, char type);
void	t_var_set_to_head(t_var **lst);

typedef struct s_cmd
{
	char			*token;
	char			type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

void	t_cmd_add_back(t_cmd **lst, t_cmd *new_node);
void	*t_cmd_free(t_cmd **lst);
t_cmd	*t_cmd_new(char	*token, char type);
void	t_cmd_set_to_head(t_cmd **lst);

typedef struct s_fd
{
	int			redirect;
	int			prev_fd;
	int			new_fd;
	struct s_fd	*next;
	struct s_fd	*prev;
}	t_fd;

void	t_fd_add_back(t_fd **lst, t_fd *new_node);
void	t_fd_free_last(t_fd **lst);
t_fd	*t_fd_new(int redirect, int prev_fd, int new_fd);
void	t_fd_set_to_head(t_fd **lst);
void	t_fd_set_to_last(t_fd **lst);

// Init ----------------------------------------------------------------------->
void	init_all(char **envp, t_var **var);

// Prompt --------------------------------------------------------------------->
char	*ft_whoami(void);

// Signals Handler ------------------------------------------------------------>
void	signal_handler(int sig);
int		close_shell(char *prompt);
bool	signals_controller(char request, char value);

// Errors Handler ------------------------------------------------------------->
int		error_handler(char request, char *msg, int code, bool print_perror);

// Execution ------------------------------------------------------------------>
void	execution_system(t_cmd **cmd, t_var **var);
void	execute(char *exe, char ***args);

// Redirections --------------------------------------------------------------->
void	redirections(t_cmd **cmd, char *exe, char ***args, t_var **var);
t_fd	*redirect_handler(char request, t_fd *new_node);
void	heredoc(char *delimiter, t_cmd **cmd);

// Builtins ------------------------------------------------------------------->
bool	is_builtin(char *exe);
void	execute_builtin(char ***args, t_var **var);

// Variables ------------------------------------------------------------------>
bool	variable_assignment(t_var **var, char *prompt);
void	ft_env(char ***args, t_var **var);
void	ft_export(char ***args, t_var **var);
void	ft_unset(char ***args, t_var **var);

// History -------------------------------------------------------------------->
void	ft_add_history(char *prompt);
void	print_history(void);

// Parsing -------------------------------------------------------------------->
bool	invalid_prompt(char *prompt);
void	parsing_system(char *prompt, t_cmd **cmd, t_var *var);
char	*variable_expand(char *prompt, size_t *i, t_var *var);

#endif
