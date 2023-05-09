/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_free_head.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 02:59:28 by kichkiro          #+#    #+#             */
/*   Updated: 2023/05/09 03:03:43 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_fd_free_head(t_fd **fd)
{
	t_fd *tmp;

	while (*fd && (*fd)->prev)
		(*fd) = (*fd)->prev;
	tmp = *fd;
	*fd = (*fd)->next;
	free(tmp);
	(*fd)->prev = NULL;
}

