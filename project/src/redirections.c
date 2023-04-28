/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:35:15 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/28 16:24:57 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	last(char request, bool flag)
{
	static bool	last_redirect;
	
	if (request == RESTORE)
		last_redirect = false;
	else if (request == GET_LAST)
		return (last_redirect);
	else if (request == SET_LAST)
		last_redirect = flag;
	return (last_redirect);
}

t_fd	redirect_handler(char request, t_fd fd)
{
	// static int	last_redirect;
	static t_fd	original_stdin_fd;
	static t_fd	original_stdout_fd;

	if (request == RESTORE)
	{
		// last_redirect = false;
		original_stdin_fd.original_fd = 0;
		original_stdin_fd.original_std = 0;
		original_stdin_fd.redirected_fd = 0;
		original_stdout_fd.original_fd = 0;
		original_stdout_fd.original_std = 0;
		original_stdout_fd.redirected_fd = 0;
	}
	// else if (request == GET_LAST)
	// 	return (last_redirect);
	// else if (request == SET_LAST)
	// 	last_redirect = last;
	else if (request == GET_FD_IN)
		return (original_stdin_fd);
	else if (request == GET_FD_OUT)
		return (original_stdout_fd);
	else if (request == SET_FD_IN && isatty(fd.original_fd))
		original_stdin_fd = fd;
	else if (request == SET_FD_OUT && isatty(fd.original_fd))
		original_stdout_fd = fd;
	return (original_stdin_fd);
}

static t_fd	redirecting_input(char	*file, t_cmd **cmd)
{
	t_fd	fd;

	fd.original_fd = dup(STDIN_FILENO);
	if (!fd.original_fd)
		error_handler(PRINT, NULL, 1, true);
	fd.original_std = STDIN_FILENO;
	fd.redirected_fd = open(file, O_RDONLY);
	if (fd.redirected_fd == -1)
		error_handler(PRINT, file, 1, true);
	redirect_handler(SET_FD_IN, fd);
	if (fd.redirected_fd != -1 && dup2(fd.redirected_fd, STDIN_FILENO) == -1)
		error_handler(PRINT, file, 1, true);
	if ((*cmd) && (*cmd)->next && (*cmd)->next->type == REDIRECT)
		*cmd = (*cmd)->next;
	return (fd);
}

static t_fd	redirecting_output(char	*file, t_cmd **cmd)
{
	t_fd	fd;

	fd.original_fd = dup(STDOUT_FILENO);
	if (!fd.original_fd)
		error_handler(PRINT, NULL, 1, true);
	fd.original_std = STDOUT_FILENO;
	fd.redirected_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd.redirected_fd == -1)
		error_handler(PRINT, file, 1, true);
	redirect_handler(SET_FD_OUT, fd);
	if (dup2(fd.redirected_fd, STDOUT_FILENO) == -1)
		error_handler(PRINT, file, 1, true);
	if ((*cmd) && (*cmd)->next && (*cmd)->next->type == REDIRECT)
		*cmd = (*cmd)->next;
	return (fd);
}

static t_fd	appending_redirected_output(char *file, t_cmd **cmd)
{
	t_fd	fd;

	fd.original_fd = dup(STDOUT_FILENO);
	if (!fd.original_fd)
		error_handler(PRINT, NULL, 1, true);
	fd.original_std = STDOUT_FILENO;
	fd.redirected_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd.redirected_fd == -1)
		error_handler(PRINT, file, 1, true);
	redirect_handler(SET_FD_OUT, fd);
	if (dup2(fd.redirected_fd, STDOUT_FILENO) == -1)
		error_handler(PRINT, file, 1, true);
	if ((*cmd) && (*cmd)->next && (*cmd)->next->type == REDIRECT)
		*cmd = (*cmd)->next;
	return (fd);
}

void	redirections(t_cmd **cmd, char *exe, char ***args, t_var **var)
{
	t_fd	fd;

	*cmd = (*cmd)->next;
	if (!ft_strncmp((*cmd)->prev->token, "<<", 2))
		fd = heredoc((*cmd)->token, cmd);
	else if (!ft_strncmp((*cmd)->prev->token, "<", 2))
		fd = redirecting_input((*cmd)->token, cmd);
	else if (!ft_strncmp((*cmd)->prev->token, ">", 2))
		fd = redirecting_output((*cmd)->token, cmd);
	else if (!ft_strncmp((*cmd)->prev->token, ">>", 2))
		fd = appending_redirected_output((*cmd)->token, cmd);
	if ((*cmd) && (*cmd)->type == REDIRECT)
		redirections(cmd, exe, args, var);
	else
		// redirect_handler(SET_LAST, true, 0);
		last(SET_LAST, true);
	if (is_builtin(exe) && !error_handler(GET, NULL, 0, false) && last(GET_LAST, 0))
		execute_builtin(args, var);
	else if (exe && args && !error_handler(GET, NULL, 0, false) && last(GET_LAST, 0))
		execute(exe, args);
	redirect_handler(RESTORE, fd);
	last(RESTORE, 0);
	if (*cmd)
		*cmd = (*cmd)->next;
	close(fd.redirected_fd);
	if (dup2(fd.original_fd, fd.original_std) == -1)
		error_handler(PRINT, NULL, 1, true);
}
