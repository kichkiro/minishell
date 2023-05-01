/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvannin <anvannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:16:54 by anvannin          #+#    #+#             */
/*   Updated: 2023/05/01 14:16:54 by anvannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
* @brief
*	Execute a pipe.
* @param cmd
*	The list of commands after the pipe (pipe included).
* @param exe
*	The path to the executable of the first command.
* @param args
*	The command to pipe from, with possible arguments.
*/
void	ft_pipe(t_cmd **cmd, char *exe, char ***args)
{
	int		fd[2];
	int		pid1;
	int		pid2;

	// printf("exe: %s\t%s\n", ft_split(exe, '/')[2], args[0][1]);
	// while ((*cmd))
	// {
	// 	printf("cmd: %s\n", (*cmd)->token);
	// 	(*cmd) = (*cmd)->next;
	// }

	if (pipe(fd) == -1)
	{
		printf("pipe error\n");
		return ;
	}

	pid1 = fork();
	if (pid1 == -1)
	{
		printf("fork error\n");
		return ;
	}

	if (!pid1)
	{
		if (!is_builtin(ft_split(exe, '/')[2]))
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execve(exe, &args[0][1], NULL);
		}
	}

	pid2 = fork();
	if (pid2 == -1)
	{
		printf("fork error\n");
		return ;
	}

	if (!pid2)
	{
		(*cmd) = (*cmd)->next;

		if (!is_builtin((*cmd)->token))
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			execve(ft_strjoin("/usr/bin/", (*cmd)->token),
				&(*cmd)->next->token, NULL);
		}
	}

	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
