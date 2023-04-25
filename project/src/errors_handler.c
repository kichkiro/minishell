/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:53:07 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/25 11:38:50 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	error_handler(char request, char *msg, unsigned char code,
	bool print_perror)
{
	static unsigned char	exit_status;

	if (request == GET)
		return (exit_status);
	else if (request == SET)
		exit_status = code;
	else if (request == PRINT || request == PRINT_FREE)
	{
		exit_status = code;
		ft_putstr_fd(RED"minishell: ", STDERR_FILENO);
		if (msg)
			ft_putstr_fd(msg, STDERR_FILENO);
		if (print_perror)
		{
			ft_putstr_fd(": ", STDERR_FILENO);
			perror(NULL);
		}
		ft_putstr_fd(RESET, STDERR_FILENO);
	}
	if (request == PRINT_FREE)
		free(msg);
	return (exit_status);
}
