/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 23:03:22 by kichkiro          #+#    #+#             */
/*   Updated: 2023/05/07 01:48:14 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_append(char **token, char *type, t_cmd **cmd)
{
	t_cmd_add_back(cmd, t_cmd_new(ft_strdup(*token), *type));
	ft_free((void **)token);
	*type = NONE;
	t_cmd_set_to_head(cmd);
}

static void	quotes_detector(char *prompt, t_parse **p)
{
	if (prompt[(*p)->i] == '\'' && !(*p)->double_quotes)
	{
		(*p)->single_quotes = !(*p)->single_quotes;
		(*p)->flow = false;
	}
	else if ((*p)->flow && prompt[(*p)->i] == '"' && !(*p)->single_quotes)
	{
		(*p)->double_quotes = !(*p)->double_quotes;
		(*p)->flow = false;
	}
}

static void	standard_token(t_cmd **cmd, char *prompt, t_parse **p)
{
	if ((*p)->single_quotes || ((*p)->double_quotes && prompt[(*p)->i] != '$') 
		|| (!(*p)->double_quotes && !(*p)->single_quotes && prompt[(*p)->i] != \
		' ' && prompt[(*p)->i] != '<' && prompt[(*p)->i] != '>' && \
		prompt[(*p)->i] != '$' && prompt[(*p)->i] != '|' && prompt[(*p)->i] != \
		'*' && prompt[(*p)->i] != '?' && prompt[(*p)->i] != '&' && \
		prompt[(*p)->i] != '(' && prompt[(*p)->i] != ')'))
	{
		(*p)->token = ft_char_append((*p)->token, prompt[(*p)->i], true);
		(*p)->type = STANDARD;
		(*p)->flow = false;
	}
	else if ((*p)->flow && (*p)->type == STANDARD && !(*p)->single_quotes && \
		!(*p)->double_quotes && prompt[(*p)->i] == ' ' && (*p)->token)
		token_append(&(*p)->token, &(*p)->type, cmd);
}


// static void	expander(t_cmd **cmd, char *prompt, t_parse **p, t_var *var)
// {
// 	if ((*p)->flow && !(*p)->single_quotes && prompt[(*p)->i] == '$' || (!(*p)->single_quotes && \
// 		prompt[(*p)->i] == '$' && (*cmd) && (*cmd)->prev->type))
// 	{
// 		(*p)->var_value = variable_expand(prompt, &(*p)->i, var);
// 		if ((*p)->var_value)
// 			(*p)->token = ft_strappend((*p)->token, (*p)->var_value, true, true);
// 		(*p)->type = STANDARD;
// 		(*p)->flow = false;
// 	}
// }

void	parsing_system(char *prompt, t_cmd **cmd, t_var *var)
{
	t_parse	*p;

	p = (t_parse *)ft_calloc(1, sizeof(t_parse));
	if (!p)
		return ;
	p->i = -1;
	p->type = NONE;
	p->token = (char *)ft_calloc(1, sizeof(char));
	p->var_value = NULL;
	p->single_quotes = false;
	p->double_quotes = false;
	p->flow = true;
	while (prompt[++p->i])
	{
		// Rilevatore di apici ------------------------------------------------> 

		quotes_detector(prompt, &p);

		// Gestore del tipo STANDARD ---------------->

		if (p->flow)
			standard_token(cmd, prompt, &p);

		// Espansore di variabili ---------------------------------------------> 

		if (p->flow && !p->single_quotes && prompt[p->i] == '$' || (!p->single_quotes && \
			prompt[p->i] == '$' && (*cmd) && (*cmd)->prev->type))
		{
			p->var_value = variable_expand(prompt, &p->i, var);
			if (p->var_value)
				p->token = ft_strappend(p->token, p->var_value, true, true);
			p->type = STANDARD;
		}

		// Gestore di redirect ------------------------------------------------>

		else if (p->flow && !p->single_quotes && !p->double_quotes && (prompt[p->i] == '<' || \
			prompt[p->i] == '>'))
		{
			if (p->type == STANDARD)
				token_append(&p->token, &p->type, cmd);	

			p->token = ft_char_append(p->token, prompt[p->i], true);
			if (prompt[p->i + 1] == '<' || prompt[p->i + 1] == '>')
				p->token = ft_char_append(p->token, prompt[++p->i], true);
			p->type = REDIRECT;
			token_append(&p->token, &p->type, cmd);
		}

		// Gestore di pipeline ------------------------------------------------>

		else if (p->flow && !p->single_quotes && !p->double_quotes && prompt[p->i] == '|' && \
			prompt[p->i + 1] != '|')
		{
			if (p->type == STANDARD)
				token_append(&p->token, &p->type, cmd);
			p->token = ft_char_append(p->token, prompt[p->i], true);
			p->type = PIPE;
			token_append(&p->token, &p->type, cmd);
		}

		// Gestore booleani --------------------------------------------------->
		
		else if (p->flow && !p->single_quotes && !p->double_quotes && ((prompt[p->i] == '&' && \
			prompt[p->i + 1] == '&') || (prompt[p->i] == '|' && prompt[p->i + 1] == '|') 
			|| prompt[p->i] == '(' || prompt[p->i] == ')'))
		{
			if (p->type == STANDARD)
				token_append(&p->token, &p->type, cmd);
			p->token = ft_char_append(p->token, prompt[p->i], true);
			if (prompt[p->i + 1] == '&' || prompt[p->i + 1] == '|')
				p->token = ft_char_append(p->token, prompt[++p->i], true);
			p->type = BOOLEAN;
			token_append(&p->token, &p->type, cmd);
		}

		// Gestore di wildcards ----------------------------------------------->

        else if (p->flow && !p->single_quotes && !p->double_quotes && ((prompt[p->i] == '*' ) || \
            (prompt[p->i] == '?'))) 
		{
            p->token = ft_char_append(p->token, prompt[p->i], true);
			p->flow = false;
			p->i++;

			while (prompt[p->i] && p->flow)
			{	
				standard_token(cmd, prompt, &p);
				p->i++;
			}
			wildcards_handler(p->token, cmd, &p->type);
			ft_free((void **)&p->token);
			p->type = NONE;
        }
		p->flow = true;
	}
	if (p->token && p->type != NONE)
		token_append(&p->token, &p->type, cmd);
}
