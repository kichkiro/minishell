/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:53:07 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/23 21:56:33 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_handler(char *error, int *exit_code, int status)
{
	ft_putstr_fd(RED"minishell: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(RESET, 2);
	*exit_code = status;
}
