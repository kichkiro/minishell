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
	Prints a signout message as the shell closes and returns 0.
* @return
	0
*/
int	close_shell(char *input)
{
	if (!input)
		printf("\n");
	printf("Goodbye %s. Till next time...\n", getenv("USER"));
	return (42);
}
