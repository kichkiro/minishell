/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvannin <anvannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:52:25 by anvannin          #+#    #+#             */
/*   Updated: 2023/04/19 18:52:25 by anvannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
void	init_history(void)
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

/*!
* @brief
	Adds the input to the history and the history file.
* @param prompt
	The input string.
*/
void	ft_add_history(char *prompt)
{
	char	*hist;
	int		fd;

	hist = ft_strjoin(getenv("HOME"), "/.minishell_history");
	fd = open(hist, O_RDWR | O_APPEND | O_CREAT, 0644);
	while (ft_get_next_line(fd))
		continue ;
	ft_putendl_fd(prompt, fd);
	add_history(prompt);
	close(fd);
}

/*!
* @brief
	Prints the history to the terminal.
*/
void	print_history(void)
{
	char	*hist;
	int		fd;
	int		i;

	i = 1;
	hist = ft_strjoin(getenv("HOME"), "/.minishell_history");
	fd = open(hist, O_RDWR | O_APPEND | O_CREAT, 0644);
	hist = ft_get_next_line(fd);
	while (hist)
	{
		ft_printf("\t%d\t%s", i++, hist);
		hist = ft_get_next_line(fd);
	}
	close(fd);
}
