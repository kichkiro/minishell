/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_assignment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:07:27 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/16 22:41:13 by kichkiro         ###   ########.fr       */
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


// da finire
// static char	*get_var_value(char *input, size_t var_name_len)
// {
// 	char	*var_value;
// 	int		i;

// 	i = var_name_len + 1;
// 	if (input[i] == ' ')
// 	{
// 		ft_putstr_fd(RED"minishell: invalid variable value\n"RESET, 2);
// 		return (NULL);
// 	}
// 	while (input[i++])
// 	{
// 		if (input[i] != '\'' && input[i] != '"' && input[i] != '(' && input[i] \
// 			!= ')' && input[i] != '$')
// 			var_value = ft_char_append(input, input[i], true);
// 		else 
// 		{
			
// 		}
// 	}
// 	return (var_value);
// }

static char	*tmp_get_var_value(char *input, size_t var_name_len)
{
	return (ft_substr(input, var_name_len + 1, ft_strlen(input) - \
	var_name_len));
}

bool	variable_assignment(t_var **var, char *input, int *exit_code)
{
	char	*var_name;
	char	*var_value;

	var_name = is_assignment(input);
	if (!var_name)
		return (false);
	var_value = tmp_get_var_value(input, ft_strlen(var_name));
	t_var_add_back(var, t_var_new(var_name, var_value));
	exit_code = 0;
	return (true);
}
