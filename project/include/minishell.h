/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:51:51 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/26 15:49:14 by kichkiro         ###   ########.fr       */
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
# include <errno.h>
# include <dirent.h>

// Handlers REQUESTS ---------------------------------------------------------->
# define GET		0
# define SET		1
# define PRINT		2
# define PRINT_FREE 3

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

typedef struct s_cmd
{
	char			*token;
	char			type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

void	t_var_add_back(t_var **lst, t_var *new_node);
void	*t_var_free(t_var **lst);
void	t_var_set_to_head(t_var **lst);
t_var	*t_var_new(char	*name, char *value, char type);

// non ancora utilizzate --->
void	t_var_del_last(t_var **lst);
t_var	*t_var_from_arr(long *arr, int size, bool need_to_free);
t_var	*t_var_head(t_var *lst);
int		t_var_index_data(t_var *lst, int data);
t_var	*t_var_last(t_var *lst);
bool	t_var_n_is_inside(t_var *lst, int n);
int		t_var_size(t_var *lst);
int		*t_var_to_arr(t_var *lst);

void	t_cmd_add_back(t_cmd **lst, t_cmd *new_node);
void	*t_cmd_free(t_cmd **lst);
void	t_cmd_set_to_head(t_cmd **lst);
t_cmd	*t_cmd_new(char	*token, char type);

// Structs -------------------------------------------------------------------->
typedef struct s_fd
{
	int		original_fd;
	int		original_std;
	int		redirected_fd;
}	t_fd;

typedef struct s_shell
{
	char	***args;
	char	**envp;
	t_var	**var;
	t_cmd	*cmd;
}	t_shell;

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

// Commands ------------------------------------------------------------------->
void	execution_system(t_cmd **cmd, t_var **var);
void	execute(char *exe, char ***args);
void	redirections(t_cmd **cmd, char *exe, char ***args, t_var **var);
t_fd	heredoc(char *delimiter, char *exe, char ***args, t_var **var);

// Builtins ------------------------------------------------------------------->
bool	is_builtin(char *exe);
void	execute_builtin(char ***args, t_var **var);

// ENV ------------------------------------------------------------------------>
void	ft_env(char ***args, t_var **var);
void	ft_export(char ***args, t_var **var);
void	ft_unset(char ***args, t_var **var);

// History -------------------------------------------------------------------->
void	ft_add_history(char *prompt);
void	print_history(void);

// Variable  ------------------------------------------------------------------>
bool	variable_assignment(t_var **var, char *prompt);
char	*variable_expand(char *prompt, size_t *i, t_var *var);

// Parsing -------------------------------------------------------------------->
bool	invalid_prompt(char *prompt);
void	parsing_system(char *prompt, t_cmd **cmd, t_var *var);

#endif
