/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:45:46 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/24 21:32:04 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char *exe, char ***args)
{
	int	pid;
	int	exit_code;

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
		if (exit_code != 0)
			error_handler(PRINT, NULL, exit_code, true);
		else
			error_handler(SET, NULL, exit_code, false);
	}
	else
		error_handler(PRINT, exe, 126, true);
}

static bool	find_executable(char **exe)
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
	ft_strmatrixfree(path, true);
	if (!found)
		error_handler(PRINT_FREE, ft_strjoin(*exe, ": command not found"), 127, 0);
	return (found);
}

static void	router(t_cmd **cmd, char *exe, char ***args, bool built_in)
{
	if ((*cmd) && (*cmd)->type == REDIRECT)
		redirections(cmd, exe, args, built_in);
	// else if ((*cmd)->type == PIPE)
	// 	pipes();
	// else if ((*cmd)->type == BOOLEAN)
	// 	boolean();
	else if (built_in)
		execute_builtin(args);
	else
		execute(exe, args);
}

void	execution_system(t_cmd **cmd)
{
	char	**args;
	char	*exe;

	args = NULL;
	exe = NULL;
	while (*cmd)
	{
		if ((*cmd)->type == STANDARD)
		{
			while (*cmd && (*cmd)->type == STANDARD)
			{
				args = ft_strmatrixjoin(args, ft_strdup((*cmd)->token), 1, 1);
				*cmd = (*cmd)->next;
			}
			exe = args[0];
			if (is_builtin(exe))
				router(cmd, exe, &args, true);
			else if (args && access(exe, F_OK) == 0 || find_executable(&exe))
				router(cmd, exe, &args, false);
			// ft_strmatrixfree(args, true);
		}
		else
			router(cmd, NULL, NULL, false);
		if (error_handler(GET, NULL, 0, false))
			break ;
		if (*cmd)
			*cmd = (*cmd)->next;
	}
}
