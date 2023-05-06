/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:07:59 by kichkiro          #+#    #+#             */
/*   Updated: 2023/05/06 16:59:18 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// -----------------------------------------------------------------------------

// Aggiungere a tutti i built_in questa riga se va a buon fine:
// errors_handler(SET, NULL, EXIT_SUCCESS, false);

// Altrimenti se il comando precedente si e' concluso con un exit status diverso
// da 0, e il comando successivo -finito a buon fine- non reimposta l'exit
// status, nessun altro comando potra essere eseguito.

//------------------------------------------------------------------------------

#include "minishell.h"

int	main(void)
{
	char	*prompt;
	t_var	*var;
	t_cmd	*cmd;

	var = NULL;
	cmd = NULL;
	init_all(&var);
	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGINT, signal_handler);
		prompt = readline(ft_whoami());
		if (!prompt)
			return (close_shell(prompt));
		signals_controller(SET, false);
		if (!invalid_prompt(prompt) && !shell_var_assig(&var, prompt))
		{
			parsing_system(prompt, &cmd, var);
			execution_system(&cmd, &var);

			// DEBUG ---------------------------------------------------------->
			// while (cmd)
			// {
			// 	printf("token: %s\n", cmd->token);
			// 	printf("type:  %d\n\n", cmd->type);
			// 	cmd = cmd->next;
			// }
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

