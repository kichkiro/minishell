/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_var_head.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:38:44 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/16 20:03:09 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
 * @brief
	Search and return first node of lst.
 * @param lst 
	Linked list.
 * @return 
	Head of the lst.
 */
t_var	*t_var_head(t_var *lst)
{
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}
