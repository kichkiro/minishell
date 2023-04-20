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
	path = ft_split(getcwd(NULL, 0), '/');
	str = NULL;
	while (path[++i])
	{
		if (!str)
			str = ft_strjoin(path[i], "/");
		else if (!path[i + 1])
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

	prompt = ft_strjoin(getenv("USER"), "@minishell:~");
	prompt = ft_strjoin(prompt, curent_dir());
	prompt = ft_strjoin(prompt, "$ ");
	return (prompt);
}
