/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:35:15 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/29 22:29:00 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
 * @brief 
	Contains fd, a linked list that keeps track of all redirects performed so 
	far.
	Based on the request, GET, SET, RESTORE executes the corresponding action.
 * @param request 
	Request to perform:
		- GET: return fd list.
		- SET: append new node at the end of the list.
		- RESTORE: close actual fd, restore prev fd and delete last node.
 * @param new_node 
	Possible new node to be added to the end of the list.
 * @return 
	List if request is GET, NULL otherwise.
 */
t_fd	*redirect_handler(char request, t_fd *new_node)
{
	static t_fd	*fd;

	if (request == GET)
		return (fd);
	else if (request == SET)
		t_fd_add_back(&fd, new_node);
	else if (request == RESTORE)
	{
		t_fd_set_to_last(&fd);
		close(fd->new_fd);
		if (dup2(fd->prev_fd, fd->redirect) == -1)
			error_handler(PRINT, NULL, 1, true);
		t_fd_free_last(&fd);
	}
	return (NULL);
}

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
	redirect_handler(SET, t_fd_new(STDIN_FILENO, prev_fd, new_fd));
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
	redirect_handler(SET, t_fd_new(STDOUT_FILENO, prev_fd, new_fd));
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
	redirect_handler(SET, t_fd_new(STDOUT_FILENO, prev_fd, new_fd));
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
	if (!ft_strncmp((*cmd)->prev->token, "<", 2))
		redirecting_input((*cmd)->token, cmd);
	else if (!ft_strncmp((*cmd)->prev->token, ">", 2))
		redirecting_output((*cmd)->token, cmd);
	else if (!ft_strncmp((*cmd)->prev->token, ">>", 2))
		appending_redirected_output((*cmd)->token, cmd);
	if ((*cmd) && (*cmd)->type == REDIRECT)
		redirections(cmd, exe, args, var);
	else
	{
		if (is_builtin(exe) && !error_handler(GET, NULL, 0, false))
			execute_builtin(args, var);
		else if (exe && args && !error_handler(GET, NULL, 0, false))
			execute(exe, args);
		if (*cmd)
		*cmd = (*cmd)->next;
	}
	redirect_handler(RESTORE, NULL);
}
