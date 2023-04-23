/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:56:59 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/23 14:25:33 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// static bool	closed_brackets(char *prompt)
// {
// 	// controllare se le parentesi - () [] {} - che si trovino fuori da apici 
// 	// e non siano il delimitatore di heredoc, siano chiuse correttamente.
// }

// static bool semicolon(char *prompt)
// {
// 	// controllare che non ci siano semicolon - ; - fuori da apici.
// }

// static bool	backslash(char *prompt)
// {
// 	// controllare che non ci siano backslash fuori da singoli apici.
// }


/*!
 * @brief 
	Checks if all quotes in the prompt string are properly closed.
 * @param prompt 
	The prompt string to check.
 * @return 
	true if all quotes are closed, false otherwise.
 */
static bool	closed_quotes(char *prompt)
{
	bool	single_quotes;
	bool	double_quotes;
	int		len;
	int		i;

	single_quotes = false;
	double_quotes = false;
	len = ft_strlen(prompt);
	i = 0;
	while (i < len)
	{
		if (prompt[i] == '\'' && (i == 0 || prompt[i - 1] != '\\') && \
			!double_quotes)
			single_quotes = !single_quotes;
		else if (prompt[i] == '\"' && (i == 0 || prompt[i - 1] != '\\') && \
			!single_quotes)
			double_quotes = !double_quotes;
		i++;
	}
	return (!single_quotes && !double_quotes);
}

/*!
 * @brief
	Checks if the given prompt contains any invalid characters or syntax.
	Invalid characters include '\' and ';', invalid syntax includes	unclosed 
	quotes.
 * @param prompt 
	The prompt string to check.
 * @param exit_code 
	A pointer to an integer variable that will be set to the exit code if 
	invalid prompt is detected.
 * @return 
	true if invalid prompt is detected, false otherwise.
 */
bool	invalid_prompt(char *prompt, int *exit_code)
{
	bool	invalid;

	invalid = false;
	if (ft_stridx(prompt, '\\') != -1 || ft_stridx(prompt, ';') != -1)
	{
		ft_putstr_fd(RED"minishell: detected '\\' or ';'\n"RESET, 2);
		invalid = true;
	}
	else if (!closed_quotes(prompt))
	{
		ft_putstr_fd(RED"minishell: detected unclosed quotes\n"RESET, 2);
		invalid = true;
	}
	if (invalid)
		*exit_code = EXIT_FAILURE;
	return (invalid);
}
