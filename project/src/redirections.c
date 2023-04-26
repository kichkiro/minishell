/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:35:15 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/26 16:02:12 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	last(char request, bool value)
{
	static bool	flag;

	if (request == GET)
		return (flag);
	else if (request == SET)
		flag = value;
	return (flag);
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
		fd = heredoc((*cmd)->token, exe, args, var);
	else if (!ft_strncmp((*cmd)->prev->token, "<", 2))
		fd = redirecting_input((*cmd)->token, cmd);
	else if (!ft_strncmp((*cmd)->prev->token, ">", 2))
		fd = redirecting_output((*cmd)->token, cmd);
	else if (!ft_strncmp((*cmd)->prev->token, ">>", 2))
		fd = appending_redirected_output((*cmd)->token, cmd);
	if ((*cmd) && (*cmd)->next && (*cmd)->next->type == REDIRECT)
		redirections(cmd, exe, args, var);
	else
		last(SET, true);
	if (is_builtin(exe) && !error_handler(GET, NULL, 0, false) && last(GET, 0))
		execute_builtin(args, var);
	else if (exe && args && !error_handler(GET, NULL, 0, false) && last(GET, 0))
		execute(exe, args);
	last(SET, false);
	if (*cmd)
		*cmd = (*cmd)->next;
	// close(fd.redirected_fd);
	if (dup2(fd.original_fd, fd.original_std) == -1)
		error_handler(PRINT, NULL, 1, true);
}
