/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvannin <anvannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:49:42 by anvannin          #+#    #+#             */
/*   Updated: 2023/04/19 17:49:42 by anvannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cd(char ***args)
{
	if (!args[0][1] || args[0][1][0] == '~')
		chdir(getenv("HOME"));
	else if (chdir(args[0][1]) == -1)
		printf("cd: no such file or directory: %s\n", args[0][1]);
	else
		chdir(args[0][1]);
}

static void	ft_echo(char ***args)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	if (!args[0][1])
	{
		printf("\n");
		return ;
	}
	if (!ft_strncmp(args[0][1], "-n", 2) && ++n)
		i++;
	while (args[0][++i])
	{
		if (!args[0][i + 1])
			printf("%s", args[0][i]);
		else
			printf("%s ", args[0][i]);
	}
	if (!n)
		printf("\n");
	error_handler(SET, NULL, EXIT_SUCCESS, false);
}

void	execute_builtin(char ***args, t_var **var)
{
	if (!ft_strncmp(*args[0], "cd", 2))
		ft_cd(args);
	else if (!ft_strncmp(*args[0], "echo", 4))
		ft_echo(args);
	else if (!ft_strncmp(*args[0], "pwd", 3))
		printf("%s\n", getcwd(NULL, 0));
	else if (!ft_strncmp(*args[0], "exit", 4))
		exit(close_shell(*args[0]));
	else if (!ft_strncmp(*args[0], "history", 7))
		print_history();
	else if (!ft_strncmp(*args[0], "env", 3))
		ft_env(args, var);
	else if (!ft_strncmp(*args[0], "export", 6))
		ft_export(args, var);
	else if (!ft_strncmp(*args[0], "unset", 5))
		ft_unset(args, var);
}

/*!
* @brief
*	Checks if the command is a builtin.
* @param exe
*	The command to check.
* @return
*	True if the command is a builtin, false otherwise.
*/
bool	is_builtin(char *exe)
{
	if (exe && (!ft_strncmp(exe, "echo", 5) || !ft_strncmp(exe, "cd", 3) || \
		!ft_strncmp(exe, "pwd", 4) || !ft_strncmp(exe, "export", 7) || \
		!ft_strncmp(exe, "unset", 6) || !ft_strncmp(exe, "env", 4) || \
		!ft_strncmp(exe, "exit", 5) || !ft_strncmp(exe, "history", 7)))
		return (true);
	return (false);
}
