/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_var_to_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:02:36 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/16 20:05:46 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
 * @brief 
	Create an array allocated with malloc(3), where each element corresponds to 
	'data' of each node of lst.
 * @param lst 
	Linked list.
 * @return 
	An array of integers.
 */
int	*t_var_to_arr(t_var *lst)
{
	int	*arr;
	int	i;

	arr = (int *)malloc(t_var_size(lst) * sizeof(int));
	i = 0;
	while (lst)
	{
		arr[i++] = lst->data;
		lst = lst->next;
	}
	return (arr);
}
