/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 20:53:09 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/30 13:09:01 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_parsing(char *delimiter, char **prompt)
{

}

size_t	delimiter_len(char *delimiter)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (delimiter[i])
	{
		if (delimiter[i] != '"' && delimiter != '\'')
			len++;
		i++;
	}
	return (len);
}
