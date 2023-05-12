/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bombaliberatutti.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:34:26 by anvannin          #+#    #+#             */
/*   Updated: 2023/05/12 01:05:22 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bombaliberatutti(t_var **var, t_cmd **cmd, t_fd **fd, char *prompt)
{
	(void)fd;
	t_var_free(var);
	t_cmd_free(cmd);
	// t_fd_free(fd);
	free(prompt);
	return (0);
}
