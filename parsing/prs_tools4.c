/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 21:14:50 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/03 20:35:42 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_herdoc_sig(int *i)
{
	*i = 1;
	if (g_var->str)
		ft_free_char(&g_var->str);
	write(1, "\n", 1);
	g_var->suspend = 0;
	g_var->exit_s = 130;
	g_var->i = dup(STDIN_FILENO);
	close(0);
	g_var->in_hdc = 0;
}
