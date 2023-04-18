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

/*
gcc user_signals.c -lreadline && ./a.out
*/

#include "../include/minishell.h"

static char	*ft_whoami(void)
{
	return (strcat(getenv("USER"), "@minishell$ "));
}

static void	signals(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

static int	ctrl_d(char *line, char *whoami)
{
	printf("\nBye Bye\n");
	free(whoami);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*whoami;
	char	*line;

	whoami = ft_whoami();
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signals);
		line = readline(whoami);
		if (!line)
			return (ctrl_d(line, whoami));
		add_history(line);
	}
	return (0);
}
