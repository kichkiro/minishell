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

static void	save_prev_fd(int *pipe_fd)
{
	int	prev_fd;
	int	new_fd;

	prev_fd = dup(STDIN_FILENO);
	if (!prev_fd)
		error_handler(PRINT, NULL, 1, true);
	new_fd = pipe_fd[0];
	fd_handler(SET, t_fd_new(STDIN_FILENO, prev_fd, new_fd, true));
}

static void	write_in_pipe(int *pipe_fd, char *exe, char ***args, t_var **var)
{
	if (close(pipe_fd[0]) == -1)
		error_handler(PRINT, NULL, 1, true);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		error_handler(PRINT, NULL, 1, true);
	if (close(pipe_fd[1]) == -1)
		error_handler(PRINT, NULL, 1, true);
	if (!is_builtin(args[0][0]))
		execute(exe, args);
	else
		execute_builtin(args, var);
}

static void	read_from_pipe(pid_t pid, int *pipe_fd)
{
	if (waitpid(pid, NULL, 1) == -1)
		error_handler(PRINT, NULL, 1, true);
	if (close(pipe_fd[1]) == -1)
		error_handler(PRINT, NULL, 1, true);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		error_handler(PRINT, NULL, 1, true);
}

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
* @param exe
*	The path to the executable of the first command.
* @param args
*	The command to pipe from, with possible arguments.
*/
void	ft_pipe(char *exe, char ***args, t_var **var, bool output_redirect)
{
	int		pipe_fd[2];
	pid_t	pid;
	t_fd	*fd;

	if (pipe(pipe_fd) == -1)
		error_handler(PRINT, NULL, 1, true);
	fd = fd_handler(GET, 0);
	reset_terminal(&fd, false, true);
	save_prev_fd(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		write_in_pipe(pipe_fd, exe, args, var);
		exit(0);
	}
	else
		read_from_pipe(pid, pipe_fd);
}