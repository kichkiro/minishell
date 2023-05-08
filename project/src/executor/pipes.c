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

static char	*get_exe_path(char *exe)
{
	char	**ex;
	char	*exe_path;

	ex = ft_split(exe, '/');
	exe_path = ft_strjoin("/", ft_strjoin(ex[0], ft_strjoin(ex[1], "/")));
	free(ex);
	return (exe_path);
}

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
void	ft_pipe(t_cmd **cmd, char *exe, char ***args, t_var **var)
{
	int	fd[2];
	int	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (!is_builtin(args[0][0]))
			execve(exe, args[0], NULL);
		else
		{
			execute_builtin(args, var);
			exit(0);
		}
	}
	else
	{
		waitpid(pid, NULL, 1);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}
