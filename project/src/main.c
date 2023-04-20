/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:07:59 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/20 13:13:25 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

// possiamo rinominare input con prompt? mi sembra piu' chiaro
int	main(void)
{
	char	*input;
	t_var	*var;
	t_cmd	*cmd;

	init_history();

	var = NULL;
	cmd = NULL;
	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signals);
		input = readline(ft_whoami());
		if (!input)
			return (close_shell(input));
		else
		{
			temp_commands_control(input);
			continue ;
		}
		// stampa exit_code


		if (!ft_strncmp(input, "$?", 2))
		{
			ft_putnbr_fd(g_exit_code, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(RED"command not found\n"RESET, 2);
			g_exit_code = 127;
		}

		//else if c'e un commento, salva in history e mostra nuovo prompt

		// controlla se l'input e' valido, oppure se c'e' un assegnamento,
		// esegui l'assegnamento e mostra nuovo prompt.
		if (!invalid_input(input, &g_exit_code) && \
			!variable_assignment(&var, input, &g_exit_code))
		{
			// parse_input(input, &cmd, var, &g_exit_code);
			if (input[0])
				printf("%s\n", input);
		}

		// Se c'e un commento, salva in history e mostra nuovo prompt --------->
		
		// FAKE ECHO - FOR TESTING -------------------------------------------->
		if (cmd)
		{
			t_cmd_set_to_head(&cmd);
			cmd = cmd->next;
			while (cmd->next)
			{
				if (cmd->type == STANDARD || cmd->type == WILDCARD)
					printf("%s ", cmd->token);
				cmd = cmd->next;
			}
			printf("%s", cmd->token);
			t_cmd_free(&cmd);
		}
		// ---------------------------------------------------------------------
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

		free(input);
	}
	t_var_free(&var);
	return (0);
}

