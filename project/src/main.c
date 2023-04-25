/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvannin <anvannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:07:59 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/25 10:19:20 by anvannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	// int		exit_code;
	t_var	*var;
	t_cmd	*cmd;

	// exit_code = 0;
	var = NULL;
	cmd = NULL;
	init_history();
	while (true)
	{
		// printf("%d\n", errno);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signals);
		prompt = readline(ft_whoami());
		if (!prompt)
			return (close_shell(prompt));

		// controlla se l'input e' valido, oppure se c'e' un assegnamento,
		// esegui l'assegnamento e mostra nuovo prompt.
		if (!invalid_prompt(prompt) && !variable_assignment(&var, prompt))
		{
			parsing_system(prompt, &cmd, var);
			// if (prompt[0])
			// 	printf("%s\n", prompt);

			execution_system(&cmd, &var);
		}

		// Se c'e un commento, salva in history e mostra nuovo prompt --------->

		// TODO

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
		ft_add_history(prompt);

		// Free ---------------------------------------------------------------> 
		ft_free((void **)&prompt);
		t_cmd_free(&cmd);
	}
	t_var_free(&var);
	return (0);
}

