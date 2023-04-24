/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:07:59 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/24 16:03:16 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*prompt;
	t_var	*var;
	t_cmd	*cmd;

	var = NULL;
	cmd = NULL;
	init_history();
	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signals);
		prompt = readline(ft_whoami());
		if (!prompt)
			return (close_shell(prompt));
		if (!invalid_prompt(prompt) && !variable_assignment(&var, prompt))
		{
			parsing_system(prompt, &cmd, var);
			execution_system(&cmd);
		}

		// Se c'e un commento, salva in history e mostra nuovo prompt --------->

			// TODO
		
		// History ------------------------------------------------------------>

		ft_add_history(prompt);

		// Free ---------------------------------------------------------------> 
		
		ft_free((void **)&prompt);
		t_cmd_free(&cmd);
	}
	t_var_free(&var);
	return (0);
}

