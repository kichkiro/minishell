/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:45:46 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/23 14:25:27 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute(char *exe, char ***args, int *exit_code)
{
	int	pid;
	int	execve_return;

	pid = 0;
	execve_return = 1;
	if (access(exe, X_OK) == 0)
	{
		pid = fork();
		execve_return = 0;
		if (pid == -1)
			ft_putstr_fd(RED"minishell: error in process creation\n"RESET, 2);
		else if(!pid)
		{
			execve_return = execve(exe, *args, NULL);
			if (execve_return == -1)
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(pid, exit_code, 0);
			ft_strmatrixfree(args);
		}
	}
	else 
		ft_putstr_fd(RED"minishell: Permission denied"RESET, 2);
	return (execve_return);
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
		ft_putstr_fd(RED"minishell: command not found\n"RESET, 2);
	return (found);
}

void	execution_system(t_cmd *cmd, int *exit_code)
{
	char	**cmd_matrix;
	char	*exe;
	

	cmd_matrix = NULL;
	exe = NULL;
	while (cmd)
	{
		// token STANDARD ----------------------------------------------------->

		// se il token e' di tipo STANDARD:
		//	- controlla che il token non sia un comando built-in
		//	- se non e' un comando built-in:
		//		- si prova ad eseguire execve()
		//		- se execve non esegue, puo essere che non abbiamo il path 
		//			assoluto o relativo e quindi lo cerchiamo con access() e 
		//			convertiamo il comando in una matrice in quanto il secondo 
		//			argomento di execve richiede gli argomenti del comando sotto
		//			forma di matrice.
		//		- se neppure con execve non si trova, allora si stampa:
		//			"command not found"

		// Vedere se e' un built-in:
		//	TODO

		// Provare ad eseguire con execve()
		while (cmd && (cmd->type == STANDARD || cmd->type == WILDCARD))
		{
			cmd_matrix = ft_strmatrixjoin(&cmd_matrix, ft_strdup(cmd->token), \
				true, true);
			cmd = cmd->next;
		}
		exe = cmd_matrix[0];
		if (cmd_matrix && access(exe, F_OK) == 0)
			printf("%d\n", execute(exe, &cmd_matrix, exit_code));
		else if (find_executable(&exe))
		{
			printf("%s\n", exe);
			// execute(exe, &cmd_matrix, exit_code);
		} 

			

		// 

		


		

		
		

		// token REDIRECT ----------------------------------------------------->



		// token HEREDOC ------------------------------------------------------>



		// token PIPE --------------------------------------------------------->



		// BONUS -------------------------------------------------------------->



		if (cmd)
			cmd = cmd->next;
	}
}
