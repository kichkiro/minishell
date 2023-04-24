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

void	execute_builtin(char ***args)
{
	// printf("%s\t%s\t%s\n", *args[0], args[0][1], args[0][2]);
	if (!ft_strncmp(*args[0], "cd", 2))
	{
		if (!args[0][1])
			chdir(getenv("HOME"));
		else if (!opendir(args[0][1]))
			printf("cd: no such file or directory: %s\n", args[0][1]);
		else
			chdir(args[0][1]);
	}
	else if (!ft_strncmp(*args[0], "pwd", 3))
		printf("%s\n", getcwd(NULL, 0));
	else if (!ft_strncmp(*args[0], "exit", 4))
		exit(close_shell(*args[0]));
	else if (!ft_strncmp(*args[0], "history", 7))
		print_history();
	else
		printf("%s: command not found\n", ft_strtrim(args[0][1], " "));
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
	if (!ft_strncmp(exe, "echo", 5) || !ft_strncmp(exe, "cd", 3) || \
		!ft_strncmp(exe, "pwd", 4) || !ft_strncmp(exe, "export", 7) || \
		!ft_strncmp(exe, "unset", 6) || !ft_strncmp(exe, "env", 4) || \
		!ft_strncmp(exe, "exit", 5) || !ft_strncmp(exe, "history", 7))
		return (true);
	return (false);
}
