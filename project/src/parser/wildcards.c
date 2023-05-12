/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:37:43 by kichkiro          #+#    #+#             */
/*   Updated: 2023/05/12 12:17:21 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	matcher(char *s, char *pattern)
{
	while (*s || *pattern)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (!*pattern)
				return (true);
			while (*s)
			{
				if (matcher(s++, pattern))
					return (true);
			}
			return (false);
		}
		else if (*pattern == *s)
		{
			pattern++;
			s++;
		}
		else
			return (false);
	}
	return (true);
}

static void	get_all(char *token, t_cmd **cmd, char *type, DIR *dir)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry)
	{
		*type = STANDARD;
		token = ft_strdup(entry->d_name);
		if (ft_strncmp(token, ".", 1))
			token_append(&token, type, cmd, true);
		entry = readdir(dir);
	}
}

static void	find_match(char *token, t_cmd **cmd, char *type, DIR *dir)
{
	bool			find_match;
	bool			found;
	char			*tmp_token;
	struct dirent	*entry;

	find_match = false;
	found = false;
	tmp_token = NULL;
	entry = readdir(dir);
	while (entry)
	{
		find_match = matcher(entry->d_name, token);
		if (find_match)
		{
			found = true;
			tmp_token = ft_strdup(entry->d_name);
			if (ft_strncmp(tmp_token, ".", 1))
			{
				*type = STANDARD;
				token_append(&tmp_token, type, cmd, true);
			}
		}
		entry = readdir(dir);
	}
	if (!found)
		token_append(&token, type, cmd, false);
}

static void	find_files(char *path, char *token, t_cmd **cmd, char *type)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
	{
		error_handler(PRINT, NULL, 1, true);
		return ;
	}
	if (!ft_strncmp(token, "*", 2))
		get_all(token, cmd, type, dir);
	else
		find_match(token, cmd, type, dir);
	closedir(dir);
}

void	wildcards_handler(char *token, t_cmd **cmd, char *type)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		find_files(cwd, token, cmd, type);
	else
		error_handler(PRINT, NULL, 1, true);
}
