/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:37:43 by kichkiro          #+#    #+#             */
/*   Updated: 2023/05/07 01:44:31 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	matcher(char *s, char *pattern)
{
	while (*s && *pattern)
	{
		if (*pattern == '*')
		{
			while (*s)
			{
				if (matcher(s, pattern + 1))
					return (true);
				s++;
			}
			return (*pattern == '\0');
		}
		else if (*pattern == '?' || *s == *pattern)
		{
			s++;
			pattern++;
		}
		else
			return (false);
	}
	return (*s == '\0' && *pattern == '\0');
}

static void	get_all(char *token, t_cmd **cmd, char *type, DIR *dir)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry)
	{
		token = ft_strdup(entry->d_name);
		if (ft_strncmp(token, ".", 1))
			token_append(&token, type, cmd);
		*type = STANDARD;
		entry = readdir(dir);
	}
}

static void	find_match(char *token, t_cmd **cmd, char *type, DIR *dir)
{
	struct dirent	*entry;
	bool			find_match;

	find_match = false;
	entry = readdir(dir);
	while (entry)
	{
		find_match = matcher(entry->d_name, token);
		if (find_match)
		{
			token = ft_strdup(entry->d_name);
			token_append(&token, type, cmd);
		}
		entry = readdir(dir);
	}
	if (!find_match)
	{
		token = ft_strdup(token);
		token_append(&token, type, cmd);
	}
}

static void	find_files(char *path, char *token, t_cmd **cmd, char *type)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
	{
		// gestire errore
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
	// else
		// gestire errore
}
