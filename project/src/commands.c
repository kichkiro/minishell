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

void	execute_builtin(char *exe, char ***args)
{
	printf("qui viene eseguito il comando builtin\n");
}

bool	is_builtin(char *exe)
{
	if (!ft_strncmp(exe, "echo", 5) || !ft_strncmp(exe, "cd", 3) || \
		!ft_strncmp(exe, "pwd", 4) || !ft_strncmp(exe, "export", 7) || \
		!ft_strncmp(exe, "unset", 6) || !ft_strncmp(exe, "env", 4) || \
		!ft_strncmp(exe, "exit", 5) || !ft_strncmp(exe, "history", 7))
		return (true);
	return (false);
}

// first argument is the shell path, second is the command, third is NULL
//	execve("42Cursus/minishell/project", ft_split(input, ' '), NULL);

void	temp_commands_control(char *prompt)
{
	if (!ft_strncmp(prompt, "cd", 2))
		chdir(ft_split(prompt, ' ')[1]);
	else if (prompt[ft_strlen(prompt) - 2] == '~')
		chdir(getenv("HOME"));
	else if (!ft_strncmp(prompt, "pwd", 3))
		ft_printf("%s\n", getcwd(NULL, 0));
	else if (!ft_strncmp(prompt, "exit", 4))
		exit(close_shell(prompt));
	else if (!ft_strncmp(prompt, "history", 7))
		print_history();
	else
	{
		printf("%s: command not found\n", ft_strtrim(prompt, " "));
		return ;
	}
	ft_add_history(prompt);
}
