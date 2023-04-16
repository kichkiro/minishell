/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_var_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:13:57 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/16 20:00:26 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
 * @brief 
	Returns the last node of the list.
 * @param lst 
	The beginning of the list.
 * @return 
	Last node of the list.	
 */
t_var	*t_var_last(t_var *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}
