/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 23:03:22 by kichkiro          #+#    #+#             */
/*   Updated: 2023/05/08 00:41:42 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_append(char **token, char *type, t_cmd **cmd, bool free_token)
{
	t_cmd_add_back(cmd, t_cmd_new(ft_strdup(*token), *type));
	*type = NONE;
	t_cmd_set_to_head(cmd);
	if (free_token)
		ft_free((void **)token);
}

static void	quotes_detector(char *prompt, t_parse **p)
{
	if (prompt[(*p)->i] == '\'' && !(*p)->double_quotes)
	{
		(*p)->single_quotes = !(*p)->single_quotes;
		(*p)->flow = false;
	}
	else if (prompt[(*p)->i] == '"' && !(*p)->single_quotes)
	{
		(*p)->double_quotes = !(*p)->double_quotes;
		(*p)->flow = false;
	}
}

void	parsing_standard_token(t_cmd **cmd, char *prompt, t_parse **p, char wc)
{
	if ((*p)->single_quotes || ((*p)->double_quotes && prompt[(*p)->i] != \
		'$') || (!(*p)->double_quotes && !(*p)->single_quotes && \
		prompt[(*p)->i] != ' ' && prompt[(*p)->i] != '<' && prompt[(*p)->i] != \
		'>' && prompt[(*p)->i] != '$' && prompt[(*p)->i] != '|' && \
		prompt[(*p)->i] != wc && prompt[(*p)->i] != '&' && \
		prompt[(*p)->i] != '(' && prompt[(*p)->i] != ')'))
	{
		(*p)->token = ft_char_append((*p)->token, prompt[(*p)->i], true);
		(*p)->type = STANDARD;
		(*p)->flow = false;
	}
	else if (wc && (*p)->flow && (*p)->type == STANDARD && \
		!(*p)->single_quotes && !(*p)->double_quotes && prompt[(*p)->i] == ' ' \
		&& (*p)->token)
		token_append(&(*p)->token, &(*p)->type, cmd, true);
}

static void	init_parsing(t_parse **p)
{
	(*p)->i = -1;
	(*p)->type = NONE;
	(*p)->token = (char *)ft_calloc(1, sizeof(char));
	(*p)->var_value = NULL;
	(*p)->single_quotes = false;
	(*p)->double_quotes = false;
	(*p)->flow = true;
}

void	parsing_system(char *prompt, t_cmd **cmd, t_var *var)
{
	t_parse	*p;

	p = (t_parse *)ft_calloc(1, sizeof(t_parse));
	init_parsing(&p);
	while (prompt[++p->i])
	{
		quotes_detector(prompt, &p);
		if (p->flow)
			parsing_standard_token(cmd, prompt, &p, 42);
		if (p->flow)
			parsing_vars(cmd, prompt, &p, var);
		if (p->flow)
			parsing_redirects(cmd, prompt, &p);
		if (p->flow)
			parsing_pipes(cmd, prompt, &p);
		if (p->flow)
			parsing_booleans(cmd, prompt, &p);
		if (p->flow)
			parsing_wildcards(cmd, prompt, &p);
		p->flow = true;
	}
	if (p->token && p->type != NONE)
		token_append(&p->token, &p->type, cmd, true);
	free(p);
}