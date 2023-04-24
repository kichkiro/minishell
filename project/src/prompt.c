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

/*!
* @brief 
	Returns a string containing the relative path of the current directory.
* @return
	The relative path string.
*/
static char	*curent_dir(void)
{
	char	**path;
	char	*str;
	int		i;

	i = 2;

	if (!getcwd(NULL, 0))
		return ("~/");
	path = ft_split(getcwd(NULL, 0), '/');
	str = "~/";
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
	prompt = ft_strappend(prompt, BLUE_B, true, false);
	// prompt = ft_strappend(prompt, curent_dir(), true, false);
	prompt = ft_strappend(prompt, RESET"\n", true, false);
	prompt = ft_strappend(prompt, BLUE"└─"RESET, true, false);
	prompt = ft_strappend(prompt, RED_B"[$] "RESET, true, false);
	return (prompt);
}
