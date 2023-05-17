/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bombaliberatutti.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:34:26 by anvannin          #+#    #+#             */
/*   Updated: 2023/05/17 16:16:09 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bombaliberatutti(t_var **var, t_cmd **cmd, char *prompt)
{
	t_var_free(var);
	t_cmd_free(cmd);
	free(prompt);
	return (0);
}
