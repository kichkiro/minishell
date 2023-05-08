/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvannin <anvannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:27:53 by anvannin          #+#    #+#             */
/*   Updated: 2023/04/19 16:27:53 by anvannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	usr_dir_level(void)
{
	int		i;
	int		j;
	char	**path;

	i = 0;
	j = 2;
	path = ft_split(getcwd(NULL, 0), '/');
	while (path[i])
	{
		if (!ft_strncmp(path[i], getenv("USER"), ft_strlen(path[i])))
			j = i;
		i++;
	}
	return (j);
}

static char	*build_path(char **path, int i)
{
	char	*str;
	int		j;

	j = usr_dir_level();
	if (i > j)
	{
		str = "~/";
		i = j;
	}
	else
	{
		str = "/";
		i = -1;
	}
	while (path[++i])
	{
		if (!path[i + 1])
			str = ft_strjoin(str, path[i]);
		else
			str = ft_strjoin(str, ft_strjoin(path[i], "/"));
	}
	return (str);
}

/*!
* @brief
	Returns a string containing the relative path of the current directory.
* @return
	The relative path string.
*/
static char	*curent_dir(void)
{
	char	**path;
	int		i;

	i = 0;
	path = ft_split(getcwd(NULL, 0), '/');
	while (path[i])
		i++;
	return (build_path(path, i));
}

/*!
* @brief
	Returns the command prompt a string.
* @return
	The prompt string.
*/
char	*ft_whoami(void)
{
	char	*prompt;

	prompt = ft_strappend(BLUE"\n┌─"RESET, WHITE_B"[", false, false);
	prompt = ft_strappend(prompt, getenv("USER"), true, false);
	prompt = ft_strappend(prompt, "@minishell] "RESET, true, false);
	prompt = ft_strappend(prompt, RED_B, true, false);
	prompt = ft_strappend(prompt, curent_dir(), true, false);
	prompt = ft_strappend(prompt, RESET"\n", true, false);
	prompt = ft_strappend(prompt, BLUE"└─"RESET, true, false);
	prompt = ft_strappend(prompt, RED_B"[$] "RESET, true, false);
	return (prompt);
}
