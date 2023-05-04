/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 09:22:27 by kichkiro          #+#    #+#             */
/*   Updated: 2023/05/05 01:35:41 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
 * @brief 
	Get the name of a variable from a prompt string.
 * @param prompt 
	The prompt string to parse.
 * @param i 
	A pointer to the current index in the prompt string.
 * @return 
	A pointer to a newly allocated string containing the variable name.
 */
static char	*get_var_name(char *prompt, size_t *i)
{
	char	*var_name;
	char	brackets;

	var_name = (char *)ft_calloc(1, sizeof(char));
	if (prompt[(*i) + 1] == '{' || prompt[(*i) + 1] == '[')
	{
		(*i)++;
		brackets = prompt[*i] + 2;
		while (prompt[++(*i)] != brackets && prompt[*i])
			var_name = ft_char_append(var_name, prompt[(*i)], true);
	}
	else if (prompt[(*i) + 1] == '?' && ++(*i))
		var_name = ft_strappend(var_name, "$?", false, false);
	else
	{
		while (ft_isalnum(prompt[++(*i)]))
			var_name = ft_char_append(var_name, prompt[*i], true);
		(*i)--;
	}
	return (var_name);
}

/*!
 * @brief 
	Expand a variable in a prompt string.
 * @param prompt 
 	The prompt string to parse.
 * @param i 
 	A pointer to the current index in the prompt string.
 * @param var 
	A pointer to the head of a linked list of variables.
 * @return 
	A pointer to a newly allocated string containing the value of the expanded 
	variable, or NULL if no matching variable is found.
 */
char	*variable_expand(char *prompt, size_t *i, t_var *var)
{
	char	*var_name;	

	var_name = get_var_name(prompt, i);
	if (var_name[1] == '?')
		return (ft_itoa(error_handler(GET, NULL, 0, false)));
	else if (getenv(var_name))
		return (ft_strdup(getenv(var_name)));
	else if (var)
	{
		t_var_set_to_head(&var);
		while (var)
		{
			if (!ft_strncmp(var_name, var->name, ft_strlen(var_name)) && \
				var->type == SHELL)
				return (ft_strdup(var->value));
			var = var->next;
		}
	}
	return (NULL);
}
