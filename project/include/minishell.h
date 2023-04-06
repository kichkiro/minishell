/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:51:51 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/06 18:02:27 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Libraries ------------------------------------------------------------------>

# include "../lib/libft/include/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

// Functions ------------------------------------------------------------------>

bool	invalid_input(char *input, int *g_exit_code);
bool	variable_assignment(char *input, int *exit_code);

#endif
