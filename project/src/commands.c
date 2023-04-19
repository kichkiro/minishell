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

void	temp_commands_control(char *input)
{
	if (!ft_strncmp(input, "cd", 2))
		chdir(ft_split(input, ' ')[1]);
	else if (input[ft_strlen(input) - 2] == '~')
		chdir(getenv("HOME"));
	else if (!ft_strncmp(input, "pwd", 3))
		ft_printf("%s\n", getcwd(NULL, 0));
	else if (!ft_strncmp(input, "exit", 4))
		exit(close_shell(input));
	else if (!ft_strncmp(input, "history", 7))
		print_history();
	else
	{
		printf("%s: command not found\n", ft_strtrim(input, " "));
		return ;
	}
	ft_add_history(input);
}
