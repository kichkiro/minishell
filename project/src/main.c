/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:07:59 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/06 18:06:10 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

int	main(int argc, char **argv)
{
	char	*input;

	(void)argc;
	(void)argv;
	while (true)
	{
		input = readline("> ");
		// controlla se l'input e' valido, oppure se c'e' un assegnamento, 
		// esegui l'assegnamento e mostra nuovo prompt.
		if (!invalid_input(input, &g_exit_code) || \
			!variable_assignment(input, &g_exit_code))
		{
			

			printf("%s\n", input);
		}

		free(input);
	}

	return (0);
}

