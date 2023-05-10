/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:07:59 by kichkiro          #+#    #+#             */
/*   Updated: 2023/05/10 16:41:43 by kichkiro         ###   ########.fr       */
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
	t_fd	*fd;

	var = NULL;
	cmd = NULL;
	init_all(&var);
	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGINT, signal_handler);

		fd = fd_handler(GET, NULL);
		reset_terminal(&fd, true, true);

		prompt = readline(ft_whoami());
		if (!prompt)
			return (close_shell(prompt));
		signals_controller(SET, false);
		if (!invalid_prompt(prompt) && !shell_variables(&var, prompt))
		{
			parsing_system(prompt, &cmd, var);
			execution_system(&cmd, &var);
		}
		ft_add_history(prompt);
		ft_free((void **)&prompt);
		// t_cmd_set_to_head(&cmd);
		t_cmd_free(&cmd);
	}
	t_var_free(&var);
	return (0);
}
