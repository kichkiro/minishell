/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 23:03:22 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/26 15:48:52 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Parsing --->

- Ogni spazio che non si trovi tra apici e' un delimitatore tra un elemento e
	l'altro.
- Scorrere il prompt:
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


static void	token_append(char **token, char *type, t_cmd **cmd)
{
	t_cmd_add_back(cmd, t_cmd_new(ft_strdup(*token), *type));
	ft_free((void **)token);
	*type = NONE;
	t_cmd_set_to_head(cmd);
}

void	parsing_system(char *prompt, t_cmd **cmd, t_var *var)
{
	size_t	i;
	char	type;
	char	*token;
	char	*var_value;
	bool	single_quotes;
	bool	double_quotes;

	i = -1;
	type = NONE;
	token = (char *)ft_calloc(1, sizeof(char));
	single_quotes = false;
	double_quotes = false;
	while (prompt[++i])
	{
		// // Delimitatore di Heredoc -------------------------------------------->
		// if ((*cmd) && (*cmd)->prev && !ft_strncmp((*cmd)->prev->token, "<<", 2)
		// 	&& (*cmd)->prev->type == REDIRECT)
		// 	{
				
		// 	}

		// Rilevatore di apici ------------------------------------------------> 

		if (prompt[i] == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		else if (prompt[i] == '"' && !single_quotes)
			double_quotes = !double_quotes;

		// Gestore del tipo STANDARD ---------------->

		else if (single_quotes || (double_quotes && prompt[i] != '$') || \
			(!double_quotes && !single_quotes && prompt[i] != ' ' && prompt[i] \
			!= '<' && prompt[i] != '>' && prompt[i] != '$' && prompt[i] != '|' \
			&& prompt[i] != '*' && prompt[i] != '?' && prompt[i] != '['))
		{
			token = ft_char_append(token, prompt[i], true);
			type = STANDARD;
		}

		// Appende token di tipo STANDARD alla lista di comandi --------------->

		else if (type == STANDARD && !single_quotes && !double_quotes \
			&& prompt[i] == ' ' && token)
		{
			// debug --->
			// printf("token: %s\n", token);

			token_append(&token, &type, cmd);
		}

		// Espansore di variabili ---------------------------------------------> 

		else if (!single_quotes && prompt[i] == '$' || (!single_quotes && \
			prompt[i] == '$' && (*cmd) && (*cmd)->prev->type))
		{
			var_value = variable_expand(prompt, &i, var);
			if (var_value)
				token = ft_strappend(token, var_value, true, true);
			type = STANDARD;
		}

		// Gestore di redirect ------------------------------------------------>

		else if (!single_quotes && !double_quotes && (prompt[i] == '<' || \
			prompt[i] == '>'))
		{
			if (type == STANDARD)
				token_append(&token, &type, cmd);	

			token = ft_char_append(token, prompt[i], true);
			if (prompt[i + 1] == '<' || prompt[i + 1] == '>')
				token = ft_char_append(token, prompt[++i], true);
			type = REDIRECT;
			token_append(&token, &type, cmd);
		}

		// Gestore di pipeline ------------------------------------------------>

		else if (!single_quotes && !double_quotes && prompt[i] == '|')
		{
			if (type == STANDARD)
				token_append(&token, &type, cmd);
			token = ft_char_append(token, prompt[i], true);
			type = PIPE;
			token_append(&token, &type, cmd);
		}

		// Gestore booleani --------------------------------------------------->
		
		// TODO

		// Gestore di wildcards ----------------------------------------------->

		else if (!single_quotes && !double_quotes && (prompt[i] == '*' \
			|| prompt[i] == '?' || prompt[i] == '['))
		{
			if (type == STANDARD)
				token_append(&token, &type, cmd);
			if (prompt[i] == '[')
			{
				if (ft_stridx(prompt, ']') < (ssize_t)i)
				{
					error_handler(PRINT, "detected unclosed brackets", 1, 0);
					free(token);			
					return ;
				}
				while (prompt[i] != ']' && prompt[i])
					token = ft_char_append(token, prompt[i++], true);
				token = ft_char_append(token, prompt[i], true);
			}
			else
				token = ft_char_append(token, prompt[i], true);
			type = WILDCARD;
			token_append(&token, &type, cmd);
		}
	}
	if (token && type)
		token_append(&token, &type, cmd);
}
