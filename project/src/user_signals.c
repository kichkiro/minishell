/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvannin <anvannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:07:04 by anvannin          #+#    #+#             */
/*   Updated: 2023/04/17 19:07:04 by anvannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signals(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signals);
		line = readline("minishell$ ");
		if (!line)
			return (0);
		add_history(line);
	}
	return (0);
}
