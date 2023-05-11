/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvannin <anvannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:02:34 by anvannin          #+#    #+#             */
/*   Updated: 2023/04/24 18:02:34 by anvannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_in_exp(t_var **var, char **split_arg)
{
	while ((*var)->next)
	{
		if (!ft_strncmp((*var)->name, split_arg[0], ft_strlen(split_arg[0])))
		{
			if (split_arg[1])
				(*var)->value = split_arg[1];
			free(split_arg);
			t_var_set_to_head(var);
			return (1);
		}
		(*var) = (*var)->next;
	}
	if (!ft_strncmp((*var)->name, split_arg[0], ft_strlen(split_arg[0])))
	{
		if (split_arg[1])
			(*var)->value = split_arg[1];
		free(split_arg);
		t_var_set_to_head(var);
		return (1);
	}
	return (0);
}

static int	set_export_var(char *arg, t_var **var)
{
	char	**split_arg;

	split_arg = ft_split(arg, '=');

	if (is_in_exp(var, split_arg))
		return (1);
	if (split_arg[1])
		t_var_add_back(var, t_var_new(split_arg[0], split_arg[1], EXPORT));
	else
		t_var_add_back(var, t_var_new(split_arg[0], NULL, EXPORT));
	free(split_arg);
	return (1);
}

/*!
* @brief
	Set one or more enviroment variables.
	If the variable already exists, it will be updated.
	If no arguments are passed, it will print all the exportable enviroment
	variables.
* @param args
	Command to execute.
* @param var
	The list of variables.
*/
void	ft_export(char ***args, t_var **var)
{
	int		i;

	i = 0;
	if (args[0][1])
		while (args[0][++i] && set_export_var(args[0][i], var))
			error_handler(SET, NULL, EXIT_SUCCESS, false);
	else
	{
		if (!(*var))
			return ;
		while ((*var)->next)
		{
			if ((*var)->type == EXPORT && (*var)->value)
				printf("declare -x %s=\"%s\"\n", (*var)->name, (*var)->value);
			else if ((*var)->type == EXPORT)
				printf("declare -x %s\n", (*var)->name);
			(*var) = (*var)->next;
		}
		if ((*var)->type == EXPORT && (*var)->value)
			printf("declare -x %s=\"%s\"\n", (*var)->name, (*var)->value);
		else if ((*var)->type == EXPORT)
			printf("declare -x %s\n", (*var)->name);
	}
	error_handler(SET, NULL, EXIT_SUCCESS, false);
	t_var_set_to_head(var);
}

/*!
* @brief
	Unset an enviroment variable.
* @param arg
	The name of the variable to unset.
* @param var
	The list of variables.
*/
static void	unset_var(char *arg, t_var **var)
{
	while ((*var))
	{
		if (!ft_strncmp((*var)->name, arg, ft_strlen(arg)))
		{
			if (!(*var)->prev && !(*var)->next)
			{
				free((*var));
				(*var) = NULL;
				return ;
			}
			if ((*var)->prev)
				(*var)->prev->next = (*var)->next;
			else
			{
				(*var)->next->prev = NULL;
				(*var) = (*var)->next;
			}
			if ((*var)->next)
				(*var)->next->prev = (*var)->prev;
			free((*var));
			t_var_set_to_head(var);
			return ;
		}
		(*var) = (*var)->next;
	}
	t_var_set_to_head(var);
}

/*!
* @brief
	Unset an enviroment variable.
	If no arguments are given, prints a new line.
* @param args
	Command to execute.
* @param var
	The list of variables.
*/
void	ft_unset(char ***args, t_var **var)
{
	int	i;

	i = 0;
	if (args[0][1])
	{
		while (args[0][++i])
		{
			if (!(*var))
				return ;
			unset_var(args[0][i], var);
		}
	}
	else
		printf("\n");
}
