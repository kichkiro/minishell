/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:07:59 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/16 22:59:18 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

int	main(int argc, char **argv)
{
	char	*input;
	t_var	*var;

	(void)argc;
	(void)argv;

	var = (t_var *)malloc(sizeof(t_var));
	if (!var)
		return (1);
	while (true)
	{
		input = readline("\n> ");

		// stampa exit_code
		if (!ft_strncmp(input, "$?", 2))
		{
			ft_putnbr_fd(g_exit_code, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(RED"command not found\n"RESET, 2);
			g_exit_code = 127;
		}
			
		// controlla se l'input e' valido, oppure se c'e' un assegnamento, 
		// esegui l'assegnamento e mostra nuovo prompt.
		else if (!invalid_input(input, &g_exit_code) && \
			!variable_assignment(&var, input, &g_exit_code))
		{

			
			printf("%s\n", input);
		}
		t_var_set_to_head(&var);
		while (var->next)
		{
			printf("var_name: %s\nvar_value: %s\n", var->name, var->value);
			var = var->next;
		}
		printf("var_name: %s\nvar_value: %s\n", var->name, var->value);
		free(input);
	}
	t_var_free(&var);
	return (0);
}

