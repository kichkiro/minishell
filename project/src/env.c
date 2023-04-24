/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvannin <anvannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:02:34 by anvannin          #+#    #+#             */
/*   Updated: 2023/04/24 18:02:34 by anvannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char ***args)
{
	int		i;

	i = -1;
	while (__environ[++i])
		printf("%s\n", __environ[i]);
}

void	ft_export(char ***args)
{
	printf("export\n");
}

void	ft_unset(char ***args)
{
	printf("unset\n");
}
