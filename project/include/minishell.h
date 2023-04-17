/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvannin <anvannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:51:51 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/17 20:54:19 by anvannin         ###   ########.fr       */
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

// Linked Lists --------------------------------------------------------------->

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
	struct s_var	*prev;
}	t_var;

void	t_var_add_back(t_var **lst, t_var *new_node);
void	t_var_del_last(t_var **lst);
void	*t_var_free(t_var **lst);
t_var	*t_var_from_arr(long *arr, int size, bool need_to_free);
t_var	*t_var_head(t_var *lst);
int		t_var_index_data(t_var *lst, int data);
t_var	*t_var_last(t_var *lst);
bool	t_var_n_is_inside(t_var *lst, int n);
t_var	*t_var_new(char	*name, char *value);
void	t_var_set_to_head(t_var **lst);
int		t_var_size(t_var *lst);
int		*t_var_to_arr(t_var *lst);

// Functions ------------------------------------------------------------------>

bool	invalid_input(char *input, int *g_exit_code);
bool	variable_assignment(t_var **var, char *input, int *exit_code);

#endif
