/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:35:15 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/23 22:47:08 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_fd	redirecting_input(char	*input_file, int *exit_code)
{
	t_fd	fd;

	fd.original_fd = dup(STDIN_FILENO);
	if (!fd.original_fd)
		error_handler("Error duplicating file descriptor", exit_code, 1);
	fd.original_std = STDIN_FILENO;
	fd.redirected_fd = open(input_file, O_RDONLY);
	if (fd.redirected_fd == -1)
		error_handler("Error opening input file", exit_code, 1);
	if (dup2(fd.redirected_fd, STDIN_FILENO) == -1)
		error_handler("Error redirecting input", exit_code, 1);
	return (fd);
}

static t_fd	redirecting_output(char	*output_file, int *exit_code)
{
	t_fd	fd;

	fd.original_fd = dup(STDOUT_FILENO);
	if (!fd.original_fd)
		error_handler("Error duplicating file descriptor", exit_code, 1);
	fd.original_std = STDOUT_FILENO;
	fd.redirected_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd.redirected_fd == -1)
		error_handler("Error opening output file", exit_code, 1);
	if (dup2(fd.redirected_fd, STDOUT_FILENO) == -1)
		error_handler("Error redirecting output", exit_code, 1);
	return (fd);
}

static t_fd	appending_redirected_output(char *output_file, int *exit_code)
{
	t_fd	fd;

	fd.original_fd = dup(STDOUT_FILENO);
	if (!fd.original_fd)
		error_handler("Error duplicating file descriptor", exit_code, 1);
	fd.original_std = STDOUT_FILENO;
	fd.redirected_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd.redirected_fd == -1)
		error_handler("Error opening output file", exit_code, 1);
	if (dup2(fd.redirected_fd, STDOUT_FILENO) == -1)
		error_handler("Error redirecting output", exit_code, 1);
	return (fd);
}

// static t_fd	heredoc(char *input_file, int *exit_code)
// {
// 	t_fd	fd;

// 	fd.original_fd = dup(STDIN_FILENO);
// 	if (!fd.original_fd)
// 		error_handler("Error duplicating file descriptor", exit_code, 1);
// 	fd.original_std = STDIN_FILENO;
// 	TODO
// }

void	redirections(t_cmd **cmd, char *exe, char ***args, int *exit_code)
{
	t_fd	fd;

	*cmd = (*cmd)->next;
	if (!ft_strncmp((*cmd)->prev->token, "<", 2))
		fd = redirecting_input((*cmd)->token, exit_code);
	else if (!ft_strncmp((*cmd)->prev->token, ">", 2))
		fd = redirecting_output((*cmd)->token, exit_code);
	else if (!ft_strncmp((*cmd)->prev->token, ">>", 2))
		fd = appending_redirected_output((*cmd)->token, exit_code);
	// else if (!ft_strncmp((*cmd)->prev->token, "<<", 2))
	// 	fd = heredoc((*cmd)->token, exit_code);
	if (exe && args)
		execute(exe, args, exit_code);
	if (*cmd)
		*cmd = (*cmd)->next;
	close(fd.redirected_fd);
	if (dup2(fd.original_fd, fd.original_std) == -1)
		error_handler("Error restoring fd", exit_code, 1);
}
