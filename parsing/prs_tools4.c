/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 21:14:50 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/03 21:30:36 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_herdoc_sig(int *i)
{
	(void)i;
	if (g_var->str)
		ft_free_char(&g_var->str);
	g_var->suspend = 0;
	g_var->exit_s = 130;
	g_var->i = dup(STDIN_FILENO);
	close(0);
	g_var->in_hdc = 0;
}

void	ft_sigdef(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
