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
