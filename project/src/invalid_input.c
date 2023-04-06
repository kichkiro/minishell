/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:56:59 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/06 19:01:12 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
 * @brief 
	Checks if all quotes in the input string are properly closed.
 * @param input 
	Checks if all quotes in the input string are properly closed.
 * @return 
	true if all quotes are closed, false otherwise.
 */
static bool	closed_quotes(char *input)
{
	bool	single_quotes;
	bool	double_quotes;
	int		len;
	int		i;

	single_quotes = false;
	double_quotes = false;
	len = strlen(input);
	i = 0;
	while (i < len)
	{
		if (input[i] == '\'' && (i == 0 || input[i - 1] != '\\') && \
			!double_quotes)
			single_quotes = !single_quotes;
		else if (input[i] == '\"' && (i == 0 || input[i - 1] != '\\') && \
			!single_quotes)
			double_quotes = !double_quotes;
		i++;
	}
	return (!single_quotes && !double_quotes);
}

/*!
 * @brief
	Checks if the given input contains any invalid characters or syntax.
	Invalid characters include '\' and ';', invalid syntax includes	unclosed 
	quotes.
 * @param input 
	The input string to check.
 * @param exit_code 
	A pointer to an integer variable that will be set to the exit code if 
	invalid input is detected.
 * @return 
	true if invalid input is detected, false otherwise.
 */
bool	invalid_input(char *input, int *exit_code)
{
	bool	invalid;

	invalid = false;
	if (ft_stridx(input, '\\') != -1 || ft_stridx(input, ';') != -1)
	{
		write(2, RED"You can't insert '\\' or ';'.\n"RESET, 37);
		invalid = true;
	}
	else if (!closed_quotes(input))
	{
		write(2, RED"You can't insert unclosed quotes.\n"RESET, 43);
		invalid = true;
	}
	if (invalid)
		*exit_code = EXIT_FAILURE;
	else
		*exit_code = EXIT_SUCCESS;
	return (invalid);
}
