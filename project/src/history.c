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

/*!
* @brief
	Initializes the history file.
*/
void	init_history(void)
{
	char	*hist;
	int		fd;

	fd = open("minishell_history", O_RDWR | O_APPEND | O_CREAT, 0644);
	hist = ft_get_next_line(fd);
	while (hist)
	{
		add_history(ft_split(hist, '\t')[1]);
		hist = ft_get_next_line(fd);
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
	int		i;

	i = 1;
	fd = open("minishell_history", O_RDWR | O_APPEND | O_CREAT, 0644);
	while (ft_get_next_line(fd))
		i++;
	hist = ft_strjoin("\t", ft_itoa(i));
	hist = ft_strjoin(hist, "\t");
	hist = ft_strjoin(hist, prompt);
	ft_putendl_fd(hist, fd);
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

	fd = open("minishell_history", O_RDWR | O_APPEND | O_CREAT, 0644);
	hist = ft_get_next_line(fd);
	while (hist)
	{
		ft_printf("%s", hist);
		hist = ft_get_next_line(fd);
	}
	close(fd);
}
