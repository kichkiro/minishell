/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 23:03:22 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/19 21:08:03 by kichkiro         ###   ########.fr       */
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



void	parse_input(char *input, t_cmd **cmd, t_var *var, int *exit_code)
{
	size_t	i;
	char	type;
	char	*token;
	char	*var_value;
	bool	single_quotes;
	bool	double_quotes;

	i = -1;
	token = (char *)ft_calloc(1, sizeof(char));
	single_quotes = false;
	double_quotes = false;
	while (input[++i])
	{
		// Rilevatore di apici ------------------------------------------------> 

		if (input[i] == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		else if (input[i] == '"' && !single_quotes)
			double_quotes = !double_quotes;

		// Gestore del tipo STANDARD ---------------->

		else if (single_quotes || (double_quotes && input[i] != '$') || \
			(!double_quotes && !single_quotes && input[i] != ' ' && input[i] \
			!= '<' && input[i] != '>' && input[i] != '$' && input[i] != '|'))
			{
				token = ft_char_append(token, input[i], true);
				type = STANDARD;
			}

		// Appende token di tipo STANDARD alla lista di comandi --------------->

		else if (type == STANDARD && !single_quotes && !double_quotes && input[i] == ' ' && token)
		{
			// debug --->
			// printf("token: %s\n", token);

			t_cmd_add_back(cmd, t_cmd_new(ft_strdup(token), STANDARD));
			ft_free((void **)&token);
		}

		// Espansore di variabili ---------------------------------------------> 

		else if (!single_quotes && input[i] == '$' || (!single_quotes && \
			input[i] == '$' && (*cmd) && (*cmd)->prev->type != HEREDOC))
		{
			var_value = variable_expand(input, &i, var, exit_code);
			if (*exit_code != 0)
			{
				ft_free((void **)&token);
				t_cmd_free(cmd);
				return ;
			}
			if (var_value)
				token = ft_strappend(token, var_value, true, true);
		}

		// Gestore di redirect ------------------------------------------------>
		
		else if (!single_quotes && !double_quotes && (input[i] == '<' || \
			input[i] == '>'))
		{
			token = ft_char_append(token, input[i], true);
			if (input[i] == '>' && input[i + 1] == '>')
				token = ft_char_append(token, input[++i], true);
			type = REDIRECT;
		}

		// Gestore di Heredoc ------------------------------------------------->


		// Gestore di pipeline ------------------------------------------------>


		// Gestore di wildcards ----------------------------------------------->


		// Appenditore di nodi ------------------------------------------------>

		

	}
	if (token)
	{
		// debug --->
		// printf("token: %s\n", token);

		t_cmd_add_back(cmd, t_cmd_new(ft_strdup(token), STANDARD));
		t_cmd_set_to_head(cmd);
		free(token);
	}
}
