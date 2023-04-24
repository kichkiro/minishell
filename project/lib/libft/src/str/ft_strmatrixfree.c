/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmatrixfree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:51:19 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/24 15:31:31 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*!
 * @brief 
    Free a string matrix.
 * @param matrix 
    The string matrix.
 * @param free_matrix
	If true, free matrix, otherwise free only matrix elements.
 */
void	ft_strmatrixfree(char **matrix, bool free_matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	if (free_matrix)
		free(matrix);
	// *matrix = NULL;
}
