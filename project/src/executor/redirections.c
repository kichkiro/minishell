/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:35:15 by kichkiro          #+#    #+#             */
/*   Updated: 2023/05/09 19:42:33 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
 * @brief 
	Saves the current fd, and redirects the input to the file passed as the 
	argument.
	Print error if the file does not exist.
 * @param file 
	File to redirect the input to.
 * @param cmd 
	Linked list containing command line.
 */
static void	redirecting_input(char	*file, t_cmd **cmd)
{
	int	prev_fd;
	int	new_fd;

	prev_fd = dup(STDIN_FILENO);
	if (!prev_fd)
		error_handler(PRINT, NULL, 1, true);
	new_fd = open(file, O_RDONLY);
	if (new_fd == -1)
		error_handler(PRINT, file, 1, true);
	fd_handler(SET, t_fd_new(STDIN_FILENO, prev_fd, new_fd, false));
	if (new_fd != -1 && dup2(new_fd, STDIN_FILENO) == -1)
		error_handler(PRINT, file, 1, true);
	if ((*cmd) && (*cmd)->next && (*cmd)->next->type == REDIRECT)
		*cmd = (*cmd)->next;
}

/*!
 * @brief 
	Saves the current fd, and redirects the output to the file passed as the 
	argument.
	If the file does not exist it creates a new one, if it exists it will 
	overwrite.
 * @param file 
	File to redirect the output to.
 * @param cmd 
	Linked list containing command line.
 */
static void	redirecting_output(char	*file, t_cmd **cmd)
{
	int	prev_fd;
	int	new_fd;

	prev_fd = dup(STDOUT_FILENO);
	if (!prev_fd)
		error_handler(PRINT, NULL, 1, true);
	new_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (new_fd == -1)
		error_handler(PRINT, file, 1, true);
	fd_handler(SET, t_fd_new(STDOUT_FILENO, prev_fd, new_fd, false));
	if (dup2(new_fd, STDOUT_FILENO) == -1)
		error_handler(PRINT, file, 1, true);
	if ((*cmd) && (*cmd)->next && (*cmd)->next->type == REDIRECT)
		*cmd = (*cmd)->next;
}

/*!
 * @brief 
	Saves the current fd, and redirects the output to the file passed as the 
	argument.
	If the file does not exist, it creates a new one; if it exists, the new 
	content is appended to EOF.
 * @param file 
	File to redirect the output to.
 * @param cmd 
	Linked list containing command line.
 */
static void	appending_redirected_output(char *file, t_cmd **cmd)
{
	int	prev_fd;
	int	new_fd;

	prev_fd = dup(STDOUT_FILENO);
	if (!prev_fd)
		error_handler(PRINT, NULL, 1, true);
	new_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (new_fd == -1)
		error_handler(PRINT, file, 1, true);
	fd_handler(SET, t_fd_new(STDOUT_FILENO, prev_fd, new_fd, false));
	if (dup2(new_fd, STDOUT_FILENO) == -1)
		error_handler(PRINT, file, 1, true);
	if ((*cmd) && (*cmd)->next && (*cmd)->next->type == REDIRECT)
		*cmd = (*cmd)->next;
}

/*!
 * @brief 
	Main function of redirects.
	Based on the input, it routes the flow to the appropriate redirect.
	If it's the last redirect, it runs the executable.
 * @param cmd 
	Linked list containing command line.
 * @param exe 
	Built-in executable or absolute path of executable program.
 * @param args 
	Command line in matrix form.
 * @param var 
	Linked list containing variables.
 */
void	redirections(t_cmd **cmd, char *exe, char ***args, t_var **var)
{
	*cmd = (*cmd)->next;
	if (!ft_strncmp((*cmd)->prev->token, "<<", 2))
		heredoc((*cmd)->token, cmd);
	else if (!ft_strncmp((*cmd)->prev->token, "<", 2))
		redirecting_input((*cmd)->token, cmd);
	else if (!ft_strncmp((*cmd)->prev->token, ">", 2))
		redirecting_output((*cmd)->token, cmd);
	else if (!ft_strncmp((*cmd)->prev->token, ">>", 2))
		appending_redirected_output((*cmd)->token, cmd);
	if ((*cmd) && (*cmd)->type == REDIRECT)
		redirections(cmd, exe, args, var);
	// else
	// {
	// 	// if ((*cmd) && (*cmd)->next && (*cmd)->next->type == PIPE && \
	// 	// 	!error_handler(GET, 0, 0, 0))
	// 	// {
	// 	// 	if (no_output_redirect(fd_handler(GET, NULL)))
	// 	// 		ft_pipe(exe, args, var, false);
	// 	// 	else
	// 	// 		ft_pipe(exe, args, var, true);
	// 	// }
	// 	// if (is_builtin(exe) && !error_handler(GET, 0, 0, 0))
	// 	// 	execute_builtin(args, var);
	// 	// else if (exe && args && !error_handler(GET, 0, 0, 0))
	// 	// 	execute(exe, args);
	// 	if (*cmd)
	// 		*cmd = (*cmd)->next;
	// }
	// if (!no_output_redirect(fd_handler(GET, NULL)))
	// fd_handler(RESTORE, NULL);
}
