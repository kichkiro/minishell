/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:07:59 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/20 17:31:41 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

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
		else
		{
			temp_commands_control(prompt);
			continue ;
		}

		// controlla se l'input e' valido, oppure se c'e' un assegnamento,
		// esegui l'assegnamento e mostra nuovo prompt.
		if (!invalid_prompt(prompt, &g_exit_code) && \
			!variable_assignment(&var, prompt, &g_exit_code))
		{
			parse_prompt(prompt, &cmd, var, &g_exit_code);
			// if (prompt[0])
			// 	printf("%s\n", prompt);
		}

		// Se c'e un commento, salva in history e mostra nuovo prompt --------->
		
		// FAKE ECHO - FOR TESTING -------------------------------------------->
		// if (cmd)
		// {
		// 	t_cmd_set_to_head(&cmd);
		// 	cmd = cmd->next;
		// 	while (cmd->next)
		// 	{
		// 		if (cmd->type == STANDARD || cmd->type == WILDCARD)
		// 			printf("%s ", cmd->token);
		// 		cmd = cmd->next;
		// 	}
		// 	printf("%s", cmd->token);
		// 	t_cmd_free(&cmd);
		// }
		// DEBUG PARSING ------------------------------------------------------>
		// if (cmd)
		// {
		// 	t_cmd_set_to_head(&cmd);
		// 	while (cmd->next)
		// 	{
		// 		printf("token -> %s ---> type -> %d\n", cmd->token, cmd->type);
		// 		cmd = cmd->next;
		// 	}
		// 	printf("token -> %s ---> type -> %d\n", cmd->token, cmd->type);
		// 	t_cmd_free(&cmd);
		// }
		// ---------------------------------------------------------------------

		// Salva history ------------------------------------------------------>


		// Free ---------------------------------------------------------------> 

		free(prompt);
	}
	t_var_free(&var);
	return (0);
}

