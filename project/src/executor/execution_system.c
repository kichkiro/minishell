/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:45:46 by kichkiro          #+#    #+#             */
/*   Updated: 2023/05/13 15:20:53 by kichkiro         ###   ########.fr       */
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
			error_handler(PRINT, exe, 1, true);
		else if (!pid)
		{
			if (execve(exe, *args, NULL) == -1)
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
		else
			waitpid(pid, &exit_code, 0);
		if (exit_code == EXIT_SUCCESS && pid != -1)
			error_handler(SET, NULL, WEXITSTATUS(exit_code), false);
		else
			error_handler(SET, NULL, WEXITSTATUS(exit_code), true);
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
			ft_free((void **)exe);
			*exe = ft_strdup(tmp);
			ft_free((void **)&tmp);
			break ;
		}
		ft_free((void **)&tmp);
	}
	ft_strmatrixfree(&path);
	if (!found)
		error_handler(PRINT_FREE, ft_strjoin(*exe, ": command not found"), 127, 0);
	return (found);
}

static bool	exec_router(t_cmd **cmd, char *exe, char ***args, t_var **var)
{
	t_fd	*fd;

	if ((*cmd) && (*cmd)->type == REDIRECT)
	{
		if (redirections(cmd, exe, args, var))
			return (false);
		if (*cmd && (*cmd)->next)
			*cmd = (*cmd)->next;
	}
	if ((*cmd) && (*cmd)->type == PIPE)
		pipes(exe, args, var);
	else if (is_builtin(exe))
		execute_builtin(args, var);
	else if (exe)
		execute(exe, args);
	ft_strmatrixfree(args);
	ft_free((void **)&exe);
	// if (args)
	// 	args[0] = NULL;
	fd = fd_handler(GET, 0);
	reset_terminal(&fd, false, true);
	return (true);
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
			exe = ft_strdup(args[0]);
			if (is_builtin(exe) || (args && !access(exe, F_OK)) || find_exe(&exe))
			{
				if (!exec_router(cmd, exe, &args, var))
					return ;
			}
		}
		else if (!exec_router(cmd, NULL, NULL, var))
			return ;
		if (signals_controller(GET, 0) == true)
			return ;
		if (error_handler(GET, 0, 0, 0) != EXIT_SUCCESS)
			break ;
		if (*cmd && (*cmd)->type && (*cmd)->type != BOOLEAN)
			*cmd = (*cmd)->next;
	}
	booleans(cmd, var);
}
