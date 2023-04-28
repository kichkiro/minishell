/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:05:42 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/28 18:49:59 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd	heredoc(char *delimiter, t_cmd **cmd)
{
	t_fd	fd;
	char	*prompt;
	char	*doc;
	pid_t	pid;
	int		pipe_fd[2];

	doc = NULL;
	fd.original_fd = dup(STDIN_FILENO);
	if (!fd.original_fd)
		error_handler(PRINT, NULL, 1, true);
	fd.original_std = STDIN_FILENO;



	// t_fd	fd_stdin = redirect_handler(GET_FD_IN, fd);
	// t_fd	fd_stdout = redirect_handler(GET_FD_OUT, fd);
	// if (fd_stdin.original_fd && dup2(fd_stdin.original_fd, STDIN_FILENO))
	// 	error_handler(PRINT, NULL, 1, true);
	// if (fd_stdout.original_fd && dup2(fd_stdout.original_fd, STDOUT_FILENO))
	// 	error_handler(PRINT, NULL, 1, true);


	
	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler);
		prompt = readline(YELLOW_B"> "RESET);
		if (signals_controller(GET, 0) == true || !prompt)
		{
			signals_controller(SET, false);
			free(prompt);
			ft_free((void **)&doc);
			break ;
		}

		// parsing
		// TODO

		if (!ft_strncmp(prompt, delimiter, ft_strlen(delimiter)) && \
			ft_strlen(prompt) == ft_strlen(delimiter))
		{
			free(prompt);
			break ;
		}
		doc = ft_strappend(doc, prompt, true, false);
		doc = ft_strappend(doc, "\n", true, false);
	}
	if (!doc)	
		doc = ft_strappend(doc, "", true, false);

	// if (fd_stdin.redirected_fd && dup2(fd_stdin.redirected_fd, STDIN_FILENO))
	// 	error_handler(PRINT, NULL, 1, true);
	// if (fd_stdout.redirected_fd && dup2(fd_stdout.redirected_fd, STDOUT_FILENO))
	// 	error_handler(PRINT, NULL, 1, true);


	// Pipe ------------------------------------------------------------------->
	
	if (pipe(pipe_fd) == -1)
		error_handler(PRINT, NULL, 1, true);
	fd.redirected_fd = pipe_fd[0];
	write(pipe_fd[1], doc, ft_strlen(doc));
	dup2(fd.redirected_fd, STDIN_FILENO);
	close(pipe_fd[1]);
	if ((*cmd) && (*cmd)->next && (*cmd)->next->type == REDIRECT)
		*cmd = (*cmd)->next;
	return (fd);
}
