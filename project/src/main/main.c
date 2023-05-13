/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:07:59 by kichkiro          #+#    #+#             */
/*   Updated: 2023/05/13 18:36:37 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*whoami;
	char	*prompt;
	t_var	*var;
	t_cmd	*cmd;
	t_cmd	*head_cmd;

	var = NULL;
	cmd = NULL;
	init_all(&var);
	whoami = ft_whoami();
	head_cmd = NULL;
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
		{
			parsing_system(prompt, &cmd, var);
			head_cmd = cmd;
			execution_system(&cmd, &var);
			fd_handler(RESTORE, NULL);
			t_cmd_free(&head_cmd);
			cmd = NULL;
		}
		ft_add_history(prompt);
		ft_free((void **)&prompt);
	}
	free(whoami);
	return (bombaliberatutti(&var, &head_cmd, NULL, prompt));
}
