/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvannin <anvannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:02:34 by anvannin          #+#    #+#             */
/*   Updated: 2023/04/24 18:02:34 by anvannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
* @brief
*	Print all the enviroment variables.
* @param args
*	Arguments passed to the function.
*	If an argument is passed, it will print an error message.
* @param var
*	Enviroment variables.
*/
void	ft_env(char ***args, t_var **var)
{
	int		i;

	i = -1;
	if (args[0][1])
	{
		printf("env: you can't set an env variable, because the ");
		printf("subject says so\n");
	}
	else
	{
		while ((*var)->next)
		{
			if ((*var)->type == ENV || (*var)->type == EXPORT)
				printf("%s=%s\n", (*var)->name, (*var)->value);
			(*var) = (*var)->next;
		}
		if ((*var)->type == ENV || (*var)->type == EXPORT)
			printf("%s=%s\n", (*var)->name, (*var)->value);
		t_var_set_to_head(var);
	}
}

static int	set_export_var(char *arg, t_var **var)
{
	char	**split_arg;
	bool	is_new;

	split_arg = ft_split(arg, '=');
	if (!split_arg[1])
	{
		printf("export: `%s': not a valid identifier\n", split_arg[0]);
		return (0);
	}
	is_new = true;
	while ((*var))
	{
		if (!ft_strncmp((*var)->name, split_arg[0], ft_strlen(split_arg[0])))
		{
			(*var)->value = split_arg[1];
			is_new = false;
			break ;
		}
		(*var) = (*var)->next;
	}
	if (is_new)
	{
		t_var_add_back(var, t_var_new(split_arg[0], split_arg[1], EXPORT));
		t_var_set_to_head(var);
	}
	t_var_set_to_head(var);
	return (1);
}

/*!
* @brief
*	Set one or more enviroment variables.
*	If the variable already exists, it will be updated.
*	If no arguments are passed, it will print all the exportable enviroment
*	variables.
* @param args
*	Arguments passed to the function.
* @param var
*	Enviroment variables.
*/
void	ft_export(char ***args, t_var **var)
{
	int		i;

	i = 0;
	if (args[0][1])
	{
		while (args[0][++i])
			if (!set_export_var(args[0][i], var))
				break ;
	}
	else
	{
		while ((*var)->next)
		{
			if ((*var)->type == EXPORT)
				printf("declare -x %s=\"%s\"\n", (*var)->name, (*var)->value);
			(*var) = (*var)->next;
		}
		if ((*var)->type == EXPORT)
			printf("declare -x %s=\"%s\"\n", (*var)->name, (*var)->value);
	}
	t_var_set_to_head(var);
}

/*!
* @brief
*	Unset an enviroment variable.
* @param	arg
*	The name of the variable to unset.
* @param	var
*	The list of variables.
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
*	Unset an enviroment variable.
*	If no arguments are given, prints a new line.
*/
void	ft_unset(char ***args, t_var **var)
{
	int	i;

	i = 0;
	if (args[0][1])
		while (args[0][++i])
			unset_var(args[0][i], var);
	else
		printf("\n");
}
