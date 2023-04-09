/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 10:46:04 by aen-naas          #+#    #+#             */
/*   Updated: 2023/04/09 10:51:50 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_red_out(t_parser *pars, char **env)
{
	int		fd;
	char	*str;

	(void)env;
	str = NULL;
	fd = dup2(pars->out_red,1);
	read(fd, str,1000);
	write(pars->out_red, str, 1000);
	return fd;
}