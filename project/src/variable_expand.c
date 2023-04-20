/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 09:22:27 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/20 13:22:31 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_name(char *input, size_t *i, int *exit_code)
{
	char	*var_name;
	char	brackets;

	var_name = (char *)ft_calloc(1, sizeof(char));
	if (input[(*i) + 1] == '{' || input[(*i) + 1] == '[')
	{
		(*i)++;
		brackets = input[*i] + 2;
		if (ft_stridx(input, brackets) < (ssize_t)(*i))
		{
			ft_putstr_fd(RED"minishell: detected unclosed brackets\n"RESET, 2);
			*exit_code = 1;
			return (NULL);
		}
		while (input[++(*i)] != brackets && input[*i])
			var_name = ft_char_append(var_name, input[(*i)], true);
	}
	else
	{
		while (ft_isalnum(input[++(*i)]))
			var_name = ft_char_append(var_name, input[*i], true);
		(*i)--;
	}
	*exit_code = 0;
	return (var_name);
}

char	*variable_expand(char *input, size_t *i, t_var *var, int *exit_code)
{
	char	*var_name;	

	var_name = get_var_name(input, i, exit_code);

	// controlla se e' $?
	if (var_name[1] == '?')
		return (ft_itoa(*exit_code));

	// cerca se e' una variabile di ambiente
	else if (getenv(var_name))
		return (ft_strdup(getenv(var_name)));

	// se non e' una varibile d'ambiente allora cerca nelle locali
	else if (var)
	{
		t_var_set_to_head(&var);
		while (var)
		{
			if (!ft_strncmp(var_name, var->name, ft_strlen(var_name)))
				return (ft_strdup(var->value));
			var = var->next;
		}
	}

	// se non ci sono varibili simili, ritorna NULL
	return (NULL);
}