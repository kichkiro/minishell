/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_assignment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:07:27 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/13 13:46:41 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
 * @brief 
	Determines whether a given input string contains a valid assignment 
	statement.
 * @details
	- The input must start with a variable name.
	- The first character of the variable name must be a letter or an 
		underscore.
	- If the first character is an underscore, there must be at least one 
		letter, digit, or underscore before the brackets and the assignment 
		operator.
	- All characters between the first character and the assignment operator can 
		be numbers, letters, underscores, or square brackets.
	- If there are square brackets, they must appear in the sequence: an opening 
		bracket, a number, a closing bracket, and the assignment operator.
 * @param input
	A pointer to a character array that contains the input string to be checked.
 * @return 
	Variable name if the input string contains a valid assignment statement, 
	NULL otherwise.
 */
static char	*is_assignment(char *input)
{
	size_t	i;
	ssize_t	var_name_len;

	i = 0;
	var_name_len = ft_stridx(input, '=');
	if (var_name_len == -1 || (input[i] != '_' && !ft_isalpha(input[i])) || \
		(input[i] == '_' && input[i + 1] != '_' && !ft_isalnum(input[i + 1])) \
		|| !input[var_name_len + 1])
		return (NULL);
	while (input[++i] != '=')
	{
		if (input[i] != '_' && !ft_isalnum(input[i]) && input[i] != '[')
			return (NULL);
		if (input[i] == '[')
		{
			var_name_len = ft_stridx(input, '[');
			while (input[++i] != ']')
			{
				if (!ft_isdigit(input[i]) || ft_stridx(input, ']') == -1)
					return (NULL);
			}
		}
	}
	return (ft_substr(input, 0, var_name_len));
}

bool	variable_assignment(char *input, int *exit_code)
{
	char	*var_name;

	(void)exit_code;
	var_name = is_assignment(input);
	if (!var_name)
		return (false);

	printf("var_name: %s\n", var_name);

	// Se var_name e' valido, prendere il valore della variabile.
	
	// Se var_value non e' corretto, stampa errore.

	// Aggiungere var_name e var_value ad una lista.





	return (true);
}
