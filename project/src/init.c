/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvannin <anvannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:06:33 by anvannin          #+#    #+#             */
/*   Updated: 2023/04/25 13:06:33 by anvannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_env(char **envp, t_var **var)
{
	int		i;
	char	**str;

	i = -1;
	while (envp[++i])
	{
		str = ft_split(envp[i], '=');
		if (str[0][0] == '_')
			t_var_add_back(var, t_var_new(str[0], str[1], ENV));
		else
			t_var_add_back(var, t_var_new(str[0], str[1], EXPORT));
	}
	t_var_set_to_head(var);
}

static char	*ft_str_replace(char *str, char c, char r)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			str[i] = r;
	return (str);
}

/*!
* @brief
	Initializes the history file.
*/
static void	init_history(void)
{
	char	*hist;
	int		fd;
	int		i;

	i = -1;
	hist = ft_strjoin(getenv("HOME"), "/.minishell_history");
	fd = open(hist, O_RDWR | O_APPEND | O_CREAT, 0644);
	hist = ft_get_next_line(fd);
	while (hist)
	{
		hist = ft_str_replace(hist, '\n', '\0');
		if (hist[0] || hist[0] != '\n')
		{
			add_history(hist);
			hist = ft_get_next_line(fd);
		}
	}
	close(fd);
}

void	init_all(char **envp, t_var **var)
{
	init_env(envp, var);
	init_history();
}
