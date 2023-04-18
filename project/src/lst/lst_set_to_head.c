/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_set_to_head.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:57:45 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/18 15:59:47 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
 * @brief 
	Set lst to first node.
 * @param lst 
	Linked List.
 */
void	t_var_set_to_head(t_var **lst)
{
	while ((*lst)->prev)
		*lst = (*lst)->prev;
}

/*!
 * @brief 
	Set lst to first node.
 * @param lst 
	Linked List.
 */
void	t_cmd_set_to_head(t_cmd **lst)
{
	while ((*lst)->prev)
		*lst = (*lst)->prev;
}
