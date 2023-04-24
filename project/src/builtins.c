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

void	builtins(char ***prompt)
{
	if (!ft_strncmp(*prompt[0], "cd", 2))
	{
		if (*prompt[2])
		{
			printf("cd: too many arguments\n");
			return ;
		}
		if (!*prompt[1] || *prompt[1] == '~'
			|| !ft_strncmp(*prompt[1], "$HOME", 5))
			chdir(getenv("HOME"));
		else
			chdir(*prompt[1]);
	}
	else if (!ft_strncmp(*prompt[1], "pwd", 3))
		printf("%s\n", getcwd(NULL, 0));
	else if (!ft_strncmp(*prompt[1], "exit", 4))
		exit(close_shell(*prompt[1]));
	else if (!ft_strncmp(*prompt[1], "history", 7))
		print_history();
	else
	{
		printf("%s: command not found\n", ft_strtrim(prompt, " "));
		return ;
	}
	ft_add_history(prompt);
}
