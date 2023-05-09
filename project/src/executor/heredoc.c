/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:05:42 by kichkiro          #+#    #+#             */
/*   Updated: 2023/05/09 19:56:33 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
 * @brief 
	Gets the document with readline().
 * @param delimiter 
	Heredoc delimiter.
 * @param doc 
	Heredoc document.
 */
static void	get_doc(char *delimiter, char **doc)
{
	char	*prompt;

	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler);
		prompt = readline(YELLOW_B"> "RESET);
		if (signals_controller(GET, 0) == true || !prompt)
		{
			signals_controller(SET, false);
			ft_free((void **)doc);
			break ;
		}
		if (!ft_strncmp(prompt, delimiter, ft_strlen(delimiter)) && \
			ft_strlen(prompt) == ft_strlen(delimiter))
			break ;
		*doc = ft_strappend(*doc, prompt, true, false);
		*doc = ft_strappend(*doc, "\n", true, false);
		free(prompt);
	}
	free(prompt);
	if (!*doc)
		*doc = ft_strappend(*doc, "", true, false);
}

/*!
 * @brief 
	Creates a file to which the document is written and redirects the input to 
	the same file.
 * @param doc 
	Heredoc document.
 * @param cmd 
	Linked list containing command line.
 */
static void	redirection_pipe(char *doc, t_cmd **cmd)
{
	int	prev_fd;
	int	new_fd;
	int	pipe_fd[2];

	prev_fd = dup(STDIN_FILENO);
	if (!prev_fd)
		error_handler(PRINT, NULL, 1, true);
	if (pipe(pipe_fd) == -1)
		error_handler(PRINT, NULL, 1, true);
	new_fd = pipe_fd[0];
	write(pipe_fd[1], doc, ft_strlen(doc));
	if (dup2(new_fd, STDIN_FILENO) == -1)
		error_handler(PRINT, NULL, 1, true);
	close(pipe_fd[1]);
	fd_handler(SET, t_fd_new(STDIN_FILENO, prev_fd, new_fd, false));
	if ((*cmd) && (*cmd)->next && (*cmd)->next->type == REDIRECT)
		*cmd = (*cmd)->next;
}

/*!
 * @brief 
	Main function of the heredoc.
 * @param delimiter 
	Heredoc delimiter.
 * @param cmd 
	Linked list containing command line.
 */
void	heredoc(char *delimiter, t_cmd **cmd)
{
	t_fd	*fd;
	char	*doc;

	fd = fd_handler(GET, NULL);
	doc = NULL;
	reset_terminal(&fd, true, true);
	get_doc(delimiter, &doc);
	reset_prev(&fd);
	redirection_pipe(doc, cmd);
}
