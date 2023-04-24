/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:45:46 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/24 00:59:48 by kichkiro         ###   ########.fr       */
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

static void	router(t_cmd **cmd, char *exe, char ***args)
{
	if ((*cmd) && ((*cmd)->type == REDIRECT || (*cmd)->type == HEREDOC))
		redirections(cmd, exe, args);
	// else if ((*cmd)->type == PIPE)
	// 	pipes();
	// else if ((*cmd)->type == BOOLEAN)
	// 	boolean();
	else
		execute(exe, args);
}

// static void	standard_token(t_cmd **cmd)
// {
// 	// token STANDARD ----------------------------------------------------->

// 		// se il token e' di tipo STANDARD:
// 		//	- controlla che il token non sia un comando built-in
// 		//	- se non e' un comando built-in:
// 		//		- si prova ad eseguire execve()
// 		//		- se execve non esegue, puo essere che non abbiamo il path 
// 		//			assoluto o relativo e quindi lo cerchiamo con access() e 
// 		//			convertiamo il comando in una matrice in quanto il secondo 
// 		//			argomento di execve richiede gli argomenti del comando sotto
// 		//			forma di matrice.
// 		//		- se neppure con execve non si trova, allora si stampa:
// 		//			"command not found"

// 		// Vedere se e' un built-in:
// 		//	TODO

// 		// Provare ad eseguire con execve()

// 	char	**cmd_matrix;
// 	char	*exe;

// 	while (*cmd && ((*cmd)->type == STANDARD || (*cmd)->type == WILDCARD))
// 	{
// 		cmd_matrix = ft_strmatrixjoin(&cmd_matrix, ft_strdup((*cmd)->token), \
// 			true, true);
// 		*cmd = (*cmd)->next;
// 	}
// 	exe = cmd_matrix[0];
// 	if (cmd_matrix && access(exe, F_OK) == 0)
// 		router(cmd, exe, &cmd_matrix);
// 	else if (find_executable(&exe))
// 	{
// 		printf("%s\n", exe);
// 		router(cmd, exe, &cmd_matrix);
// 	}
// }

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
				args = ft_strmatrixjoin(
					&args, ft_strdup((*cmd)->token), false, false);
				*cmd = (*cmd)->next;
			}
			exe = args[0];
			if (args && access(exe, F_OK) == 0 || find_executable(&exe))
				router(cmd, exe, &args);
		}
		else
			router(cmd, NULL, NULL);
		if (*cmd)
			*cmd = (*cmd)->next;
	}
}
