/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_set_to_last.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:13:57 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/29 11:43:33 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//----------------------------------------------------------------------------->
//	AGGIORNARE DOCUMENTAZIONE
//------------------------------------------------------------------------------


#include "minishell.h"


void	t_fd_set_to_last(t_fd **lst)
{
	if ((*lst) && (*lst)->next)
	{
		while ((*lst) && (*lst)->next)
			*lst = (*lst)->next;
	}
}