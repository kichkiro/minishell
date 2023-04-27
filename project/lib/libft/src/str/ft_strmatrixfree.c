/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmatrixfree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:51:19 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/26 20:12:01 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*!
 * @brief 
    Free a string matrix.
 * @param matrix 
    The string matrix.
 */
void	ft_strmatrixfree(char **matrix)
{
	int	i;

	i = 0;
	if (matrix)
	{
		while (matrix[i])
			free(matrix[i++]);
		free(matrix);
		matrix = NULL;
	}
}
