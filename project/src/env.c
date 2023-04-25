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

void	ft_env(char ***args)
{
	int		i;

	i = -1;
	if (args[0][1])
		printf("env: %s: No such file or directory\n", args[0][1]);
	else
		while (__environ[++i])
			printf("%s\n", __environ[i]);
}

static int	set_export_var(char *arg, t_var **var)
{
	char	**split_arg;
	t_var	*tmp;
	bool	is_new;

	split_arg = ft_split(arg, '=');
	if (!split_arg[1])
	{
		printf("export: `%s': not a valid identifier\n", split_arg[0]);
		return (0);
	}
	tmp = (*var);
	is_new = true;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, split_arg[0], ft_strlen(split_arg[0])))
		{
			tmp->value = split_arg[1];
			is_new = false;
			break ;
		}
		tmp = tmp->next;
	}
	if (is_new)
	{
		t_var_add_back(var, t_var_new(split_arg[0], split_arg[1]));
		t_var_set_to_head(var);
	}
	return (1);
}

void	ft_export(char ***args, t_var **var)
{
	int		i;
	t_var	*tmp;

	i = 0;
	tmp = (*var);
	if (args[0][1])
	{
		while (args[0][++i])
			if (!set_export_var(args[0][i], var))
				break ;
	}
	else
	{
		while (tmp)
		{
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
	}
}

static void	unset_var(char *arg, t_var **var)
{
	t_var	*tmp;

	tmp = (*var);
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, arg, ft_strlen(arg)))
		{
			if (!tmp->prev && !tmp->next)
			{
				free(tmp);
				(*var) = NULL;
				return ;
			}
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
			{
				tmp->next->prev = NULL;
				(*var) = tmp->next;
			}
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			free(tmp);
			t_var_set_to_head(var);
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}

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
