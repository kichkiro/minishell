/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_var_del_last.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 20:32:17 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/16 20:01:29 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
 * @brief 
	Delete last node.
 * @param lst 
	Linked list.
 */
void	t_var_del_last(t_var **lst)
{
	*lst = t_var_last(*lst);
	*lst = (*lst)->prev;
	free((*lst)->next);
	(*lst)->next = 0;
}
