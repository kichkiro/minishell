/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_var_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 00:47:39 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/16 20:02:30 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
 * @brief 
	Delete and frees the lst.
 * @param lst 
	Linked list.
 */
void	*t_var_free(t_var **lst)
{
	t_var	*tmp;

	tmp = 0;
	if (*lst)
	{
		t_var_set_to_head(lst);
		while ((*lst)->next)
		{
			*lst = (*lst)->next;
			tmp = (*lst)->prev;
			free(tmp);
			(*lst)->prev = 0;
		}
		free(*lst);
		*lst = 0;
	}
	return (0);
}
