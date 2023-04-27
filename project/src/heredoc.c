/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:05:42 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/26 19:24:20 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd	heredoc(char *delimiter, t_cmd **cmd, char *exe, char ***args)
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

	// Pipe ------------------------------------------------------------------->
	
	if (pipe(pipe_fd) == -1)
		error_handler(PRINT, NULL, 1, true);
	fd.redirected_fd = pipe_fd[0];
	write(pipe_fd[1], doc, ft_strlen(doc));
	dup2(fd.redirected_fd, STDIN_FILENO);
	close(pipe_fd[1]);

	if ((*cmd) && (*cmd)->next && (*cmd)->next->type == REDIRECT && \
		!ft_strncmp((*cmd)->next->token, ">", 1))
		*cmd = (*cmd)->next;



	return (fd);
}
