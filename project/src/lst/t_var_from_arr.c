/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_var_from_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvannin <anvannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:35:08 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/25 10:14:38 by anvannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
 * @brief 
	Create new list, where each node corresponds to an arr item.
 * @param arr 
	Array of integers.
 * @param size 
	Lenght of arr.
 * @param need_to_free 
	If set to TRUE, frees arr.
 * @return 
	New linked list.
 */
t_var	*t_var_from_arr(long *arr, int size, bool need_to_free)
{
	t_var	*lst;
	int		i;

	lst = 0;
	i = -1;
	while (++i < size)
		t_var_add_back(&lst, t_var_new(arr[i]));
	if (need_to_free)
		free(arr);
	t_var_set_to_head(&lst);
	return (lst);
}
