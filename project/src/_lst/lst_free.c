/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 00:47:39 by kichkiro          #+#    #+#             */
/*   Updated: 2023/05/11 00:38:40 by kichkiro         ###   ########.fr       */
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
			(*lst)->prev = NULL;
		}
		free(*lst);
		*lst = NULL;
	}
	return (NULL);
}

/*!
 * @brief 
	Delete and frees the lst.
 * @param lst 
	Linked list.
 */
void	*t_cmd_free(t_cmd **lst)
{
	t_cmd	*tmp;

	tmp = 0;
	if (*lst)
	{
		t_cmd_set_to_head(lst);
		while ((*lst)->next)
		{
			*lst = (*lst)->next;
			tmp = (*lst)->prev;
			free(tmp);
			(*lst)->prev = NULL;
		}
		free(*lst);
		*lst = NULL;
	}
	return (NULL);
}
