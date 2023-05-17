/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:07:59 by kichkiro          #+#    #+#             */
/*   Updated: 2023/05/17 17:24:05 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run(t_cmd **cmd, t_var **var, char *prompt, t_cmd **head_cmd)
{
	parsing_system(prompt, cmd, *var);
	*head_cmd = *cmd;
	if (*cmd && !syntax_error(cmd))
		execution_system(cmd, var);
	fd_handler(RESTORE, NULL);
	t_cmd_free(head_cmd);
	*cmd = NULL;
}

int	main(void)
{
	t_var	*var;
	t_cmd	*cmd;
	t_cmd	*head_cmd;
	char	*whoami;
	char	*prompt;

	init_all(&var, &cmd, &head_cmd, &whoami);
	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGINT, signal_handler);
		prompt = readline(whoami);
		if (!prompt && close_shell(prompt))
			break ;
		signals_controller(SET, false);
		if (!invalid_prompt(prompt) && !shell_variables(&var, prompt))
			run(&cmd, &var, prompt, &head_cmd);
		ft_add_history(prompt);
		ft_free((void **)&prompt);
	}
	ft_free((void **)&whoami);
	return (bombaliberatutti(&var, &head_cmd, prompt));
}
