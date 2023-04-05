/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:47:58 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/04/03 21:28:08 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_handel_cd(t_parser **prs)
{
	int		i;
	char	cur[1024];

	i = chdir((*prs)->args[1]);
	if(i == -1)
		printf("cd: %s: No such file or directory\n", (*prs)->args[1]);
	getcwd(cur, sizeof(cur));
	printf("%s\n",cur);
}
