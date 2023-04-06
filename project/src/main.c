/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:07:59 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/06 14:08:26 by kichkiro         ###   ########.fr       */
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
		if (!invalid_input(input, &g_exit_code))
		{
			

			printf("%s\n", input);
		}

		free(input);
	}

	return (0);
}

