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

#include "minishell.h"

/*!
* @brief 
	Returns a string containing the username and the prompt.
* @return 
	The prompt string.
*/
void	signals(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

/*!
* @brief 
	Prints a signout message as the shell closes and returns NULL.
* @return
	NULL.
*/
int	close_shell(char *prompt)
{
	if (!prompt)
		printf("\n");
	printf(YELLOW_B"Goodbye %s. Till next time...\n"RESET, getenv("USER"));
	return (42);
}
