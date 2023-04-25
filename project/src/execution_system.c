/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvannin <anvannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:45:46 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/25 10:20:13 by anvannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(char *exe, char ***args)
{
	int	pid;
	int	ret;

	pid = 0;
	ret = 1;
	if (access(exe, X_OK) == 0)
	{
		ret = 0;
		pid = fork();
		if (pid == -1)
			perror(RED"minishell"RESET);
		else if (!pid)
		{
			ret = execve(exe, *args, NULL);
			if (ret == -1)
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
		else
			waitpid(pid, NULL, 0);
	}
	else
	{
		errno = EACCES;
		perror(RED"minishell"RESET);
	}
	// ft_strmatrixfree(args);
	return (ret);
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
	// ft_strmatrixfree(&path);
	if (!found)
	{
		errno = 127;
		perror(RED"minishell: command not found"RESET);
	}
	return (found);
}

static void	router(t_cmd **cmd, char *exe, char ***args, bool built_in, t_var **var)
{
	if ((*cmd) && ((*cmd)->type == REDIRECT || (*cmd)->type == HEREDOC))
		redirections(cmd, exe, args, built_in, var);
	// else if ((*cmd)->type == PIPE)
	// 	pipes();
	// else if ((*cmd)->type == BOOLEAN)
	// 	boolean();
	else if (built_in)
		execute_builtin(args, var);
	else
		execute(exe, args);
}

void	execution_system(t_cmd **cmd, t_var **var)
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
				router(cmd, exe, &args, true, var);
			else if (args && access(exe, F_OK) == 0 || find_executable(&exe))
				router(cmd, exe, &args, false, var);
		}
		else
			router(cmd, NULL, NULL, false, var);
		if (*cmd)
			*cmd = (*cmd)->next;
	}
}
