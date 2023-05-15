/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvannin <anvannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:07:08 by kichkiro          #+#    #+#             */
/*   Updated: 2023/05/15 20:18:16 by anvannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	bool_pipe(t_cmd **cmd)
{
	char	*str;

	str = ft_strjoin("syntax error near unexpected token `", (*cmd)->token);
	str = ft_strjoin(str, "'");
	error_handler(PRINT, str, 2, false);
	free(str);
	return (2);
}

static int	bool_pipe_parentheses(t_cmd **cmd)
{
	char	*str;
	char	**ph;

	ph = ft_split((*cmd)->token, '(');
	str = ft_strjoin("syntax error near unexpected token `", ph[1]);
	str = ft_strjoin(str, "'");
	error_handler(PRINT, str, 2, false);
	free(ph);
	free(str);
	return (2);
}

// static bool	syntax_error(char *prompt)
// {
	// Se il primo token e' di tipo PIPE o BOOLEAN ritorna syntax error e setta
	// l'exit_status a 2.
	// Se i primi token sono BOOLEAN e sono parentesi tonde, il token successivo
		// deve essere STANDARD, o REDIRECT)

	// Se finisce con PIPE, REDIRECT, BOOLEAN, non e' syntax error, ma non lo
	// gestiamo e torniamo exit_status 1.
// }


// ! ( | || & && ) () (())
int	syntax_error(t_cmd **cmd)
{
	if (!ft_strncmp((*cmd)->token, "|", 1)
		|| !ft_strncmp((*cmd)->token, "||", 2)
		|| !ft_strncmp((*cmd)->token, "&", 1)
		|| !ft_strncmp((*cmd)->token, "&&", 2))
		return (bool_pipe(cmd));
	else if (!ft_strncmp((*cmd)->token, "(|", 2) // <- this is the problem
		|| !ft_strncmp((*cmd)->token, "(||", 3)
		|| !ft_strncmp((*cmd)->token, "(&", 2)
		|| !ft_strncmp((*cmd)->token, "(&&", 3))
		return (bool_pipe_parentheses(cmd));
	else if ((*cmd)->token[0] == '(' && (*cmd)->next
		&& (*cmd)->next->token[0] == ')')
		return (error_handler(PRINT,
				"syntax error near unexpected token `)'", 2, false));
	else if ((*cmd)->token[0] == '(' && (*cmd)->next && (*cmd)->next->next
		&& (*cmd)->next->token[0] == '(' && (*cmd)->next->next->token[0] == ')')
	{
		printf("\n");
		return (error_handler(SET, NULL, 1, false));
	}
	t_cmd_set_to_head(cmd);
	return (0);
}
