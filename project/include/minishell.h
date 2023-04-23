/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:51:51 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/21 19:30:30 by kichkiro         ###   ########.fr       */
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
# include <fcntl.h>

// Token types ---------------------------------------------------------------->

# define NONE		0
# define STANDARD	1
# define REDIRECT	2
# define HEREDOC	3
# define PIPE		4
# define BOOLEAN    5
# define WILDCARD	6

// Linked Lists --------------------------------------------------------------->

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
	struct s_var	*prev;
}	t_var;

void	t_var_add_back(t_var **lst, t_var *new_node);
void	*t_var_free(t_var **lst);
void	t_var_set_to_head(t_var **lst);
t_var	*t_var_new(char	*name, char *value);


// non ancora utilizzate --->
void	t_var_del_last(t_var **lst);
t_var	*t_var_from_arr(long *arr, int size, bool need_to_free);
t_var	*t_var_head(t_var *lst);
int		t_var_index_data(t_var *lst, int data);
t_var	*t_var_last(t_var *lst);
bool	t_var_n_is_inside(t_var *lst, int n);
int		t_var_size(t_var *lst);
int		*t_var_to_arr(t_var *lst);

typedef struct s_cmd
{
	char			*token;
	char			type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

void	t_cmd_add_back(t_cmd **lst, t_cmd *new_node);
void	*t_cmd_free(t_cmd **lst);
void	t_cmd_set_to_head(t_cmd **lst);
t_cmd	*t_cmd_new(char	*token, char type);

// Prompt --------------------------------------------------------------------->

char	*ft_whoami(void);

// User Signals --------------------------------------------------------------->

void	signals(int sig);
int		close_shell(char *prompt);

// Commands ------------------------------------------------------------------->

void	execution_system(t_cmd *cmd, int *exit_code);
void	temp_commands_control(char *prompt);

// History -------------------------------------------------------------------->

void	init_history(void);
void	ft_add_history(char *prompt);
void	print_history(void);

// Variable  ------------------------------------------------------------------>

bool	variable_assignment(t_var **var, char *prompt, int *exit_code);
char	*variable_expand(char *prompt, size_t *i, t_var *var, int *exit_code);

// Parsing -------------------------------------------------------------------->

bool	invalid_prompt(char *prompt, int *g_exit_code);
void	parsing_system(char *prompt, t_cmd **cmd, t_var *var, int *exit_code);

#endif
