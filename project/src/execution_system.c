/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:45:46 by kichkiro          #+#    #+#             */
/*   Updated: 2023/05/06 12:47:09 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char *exe, char ***args)
{
	pid_t	pid;
	int		exit_code;

	pid = 0;
	exit_code = 0;
	if (!access(exe, X_OK))
	{
		pid = fork();
		if (pid == -1)
			error_handler(PRINT, NULL, 1, true);
		else if (!pid)
		{
			if (execve(exe, *args, NULL) == -1)
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
		else
			waitpid(pid, &exit_code, 0);
		if (exit_code == EXIT_SUCCESS && pid != -1)
			error_handler(SET, NULL, EXIT_SUCCESS, false);
		else if (exit_code == EXIT_FAILURE && pid != -1)
			error_handler(PRINT, NULL, EXIT_FAILURE, true);
	}
	else
		error_handler(PRINT, exe, 126, true);
}

static bool	find_exe(char **exe)
{
	bool	found;
	char	**path;
	char	*tmp;
	size_t	i;

	found = false;
	path = ft_split(getenv("PATH"), ':');
	i = -1;
	*exe = ft_strappend("/", *exe, false, true);
	while (path[++i])
	{
		tmp = ft_strappend(path[i], *exe, false, false);
		if (access(tmp, F_OK) == 0)
		{
			found = true;
			*exe = ft_strdup(tmp);
			ft_free((void **)&tmp);
			break ;
		}
		ft_free((void **)&tmp);
	}
	ft_strmatrixfree(path);
	if (!found)
		error_handler(PRINT_FREE, ft_strjoin(*exe, ": command not found"), 127, 0);
	return (found);
}

static void	router(t_cmd **cmd, char *exe, char ***args, t_var **var)
{
	if ((*cmd) && (*cmd)->type == REDIRECT)
		redirections(cmd, exe, args, var);
	else if ((*cmd) && (*cmd)->type == PIPE)
		ft_pipe(cmd, exe, args, var);
	// else if ((*cmd)->type == BOOLEAN)
	// 	boolean();
	else if (is_builtin(exe))
		execute_builtin(args, var);
	else
		execute(exe, args);
	// ft_strmatrixfree(args[0]);
	if (args)
		args[0] = NULL;
	if ((*cmd) && (*cmd)->type == REDIRECT)
		router(cmd, exe, args, var);
}

void	execution_system(t_cmd **cmd, t_var **var)
{
	char	**args;
	char	*exe;

	args = NULL;
	exe = NULL;
	while (*cmd && (*cmd)->type != BOOLEAN)
	{
		if ((*cmd)->type == STANDARD)
		{
			while (*cmd && (*cmd)->type == STANDARD)
			{
				args = ft_strmatrixjoin(args, ft_strdup((*cmd)->token), 1, 1);
				*cmd = (*cmd)->next;
			}
			exe = args[0];
			if (is_builtin(exe) || args && !access(exe, F_OK) || find_exe(&exe))
				router(cmd, exe, &args, var);
		}
		else
			router(cmd, NULL, NULL, var);
		if (error_handler(GET, NULL, 0, false) != EXIT_SUCCESS)
			break ;
		if (*cmd && (*cmd)->type && (*cmd)->type != BOOLEAN)
			*cmd = (*cmd)->next;
	}
	booleans_handler(cmd, var);
}
