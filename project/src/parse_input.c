/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 23:03:22 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/17 22:02:29 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
parsing input cmd di bash:

- Ogni spazio che non si trovi tra apici e' un delimitatore tra un elemento e
	l'altro.
- Scorrere l'input:
	- Se presenti apici:
		- Se singoli, copiare ogni singolo char fino a chiusura.
		- Se doppi, espandere le variabili.
		infine controllare se l'elemento successivo e' uno spazio, se si:
			- passare al prossimo elemento.
		se no:
			- continuare con questo elemento.
	- Se presenti redirect, fuori da apici:
		- ogni redirect e' un elemento a se stante anche se non delimitato da
			spazi.
	- Se presente "<<", prende letteralmente il valore successivo come 
		delimitatore senza espandere variabili.
*/



static char	*variable_expand(char *input, size_t *i, t_var *var, int *exit_code)
{
	char	*var_name;	
	char	*var_value;

	t_var_set_to_head(&var);
	var_name = (char *)ft_calloc(1, sizeof(char));
	if (input[(*i) + 1] == '{')
	{
		(*i)++;
		while (input[++(*i)] != '}')
			var_name = ft_char_append(var_name, input[(*i)], true);
	}
	else
	{
		while (ft_isalnum(input[++(*i)]))
			var_name = ft_char_append(var_name, input[*i], true);
	}

	// ft_printf("var_expand: %s\n", var_name);
		
	// controlla se e' $?
	if (var_name[1] == '?')
		return (ft_itoa(*exit_code));

	// cerca se e' una variabile di ambiente
	var_value = getenv(var_name);
	if (var_value)
		return (var_value);

	// se non e' una varibile d'ambiente allora cerca nelle locali
	while (var->next)
	{
		if (!ft_strncmp(var_name, var->name, ft_strlen(var_name)))
			return (var->value);
		var = var->next;
		if (!ft_strncmp(var_name, var->name, ft_strlen(var_name)))
			return (var->value);
	}

	// se non ci sono varibili simili, ritorna NULL
	return (NULL);
}

void	parse_input(char *input, t_cmd **cmd, t_var *var, int *exit_code)
{
	size_t	i;
	char	*token;
	char	*var_value;
	bool	single_quotes;
	bool	double_quotes;

	i = -1;
	single_quotes = false;
	double_quotes = false;
	while (input[++i])
	{
		token = NULL;
		if (input[i] == '\'' && !double_quotes && ++i)
			single_quotes = !single_quotes;
		else if (input[i] == '"' && !single_quotes && ++i)
			double_quotes = !double_quotes;
			
		if (single_quotes || (double_quotes && input[i] != '$') || \
			(!double_quotes && !single_quotes && input[i] != ' ' && input[i] \
			!= '<' && input[i] != '>' && input[i] != '$' && input[i] != '|'))
			token = ft_char_append(token, input[i], true);
		else if(!single_quotes && !double_quotes && input[i] == ' ')
		{
			t_cmd_add_back(cmd, t_cmd_new(token));
			// ft_free((void **)&token);
		}

		// espansione variabile
		else if(!single_quotes && input[i] == '$')
		{
			var_value = variable_expand(input, &i, var, exit_code);
			token = ft_strappend(token, var_value, true, false);
			printf("var_expand_value: %s\n", token);
		}

		// redirect <

		// redirect <<

		// redirect >

		// redirect >>

		// pipe

		
	}
}









