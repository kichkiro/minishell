/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_free_last.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:37:16 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/29 19:00:51 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_fd_free_last(t_fd **lst)
{
	t_fd	*curr;

	curr = NULL;
	if (!*lst)
		return ;
	else if (!(*lst)->next && !(*lst)->prev)
	{
		free(*lst);
		*lst = NULL;
		return ;
	}
	t_fd_set_to_last(lst);
	curr = *lst;
	*lst = (*lst)->prev;
	free(curr);
	(*lst)->next = NULL;
}
