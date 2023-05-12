/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:07:59 by kichkiro          #+#    #+#             */
/*   Updated: 2023/05/12 16:42:43 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*whoami;
	char	*prompt;
	t_var	*var;
	t_cmd	*cmd;

	var = NULL;
	cmd = NULL;
	init_all(&var);
	whoami = ft_whoami();
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
			execution_system(&cmd, &var);
			fd_handler(RESTORE, NULL);
		}
		ft_add_history(prompt);
		ft_free((void **)&prompt);
		// t_cmd_set_to_head(&cmd);
		t_cmd_free(&cmd);
	}
	free(whoami);
	return (bombaliberatutti(&var, &cmd, NULL, prompt));
}
