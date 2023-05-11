/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvannin <anvannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:07:04 by anvannin          #+#    #+#             */
/*   Updated: 2023/04/17 19:07:04 by anvannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
<<<<<<< HEAD
 * @brief 
	Handles the SIGINT signal.
 * @param sig 
	Signal to handle.
 */
=======
* @brief
	Returns a string containing the username and the prompt.
* @return
	The prompt string.
*/
>>>>>>> origin/anvannin
void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		signals_controller(SET, true);
	}
}

/*!
 * @brief 
	Controls if a SIGINT signal has been received.
 * @param request 
	Request to perform:
		- GET: returns the value of the sigint_received.
		- SET: sets the value of the sigint_received.
 * @param value 
	Value to set the sigint_received to.
 * @return 
	True if a SIGINT signal has been received, false otherwise.
 */
bool	signals_controller(char request, char value)
{
	static bool	sigint_received;

	if (request == GET)
		return (sigint_received);
	if (request == SET)
		sigint_received = value;
	return (sigint_received);
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
		return (printf("\n"));
	return (printf(YELLOW_B"Goodbye %s. Till next time...\n"RESET,
			getenv("USER")));
}
