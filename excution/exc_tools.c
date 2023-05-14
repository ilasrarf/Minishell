/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 10:46:04 by aen-naas          #+#    #+#             */
/*   Updated: 2023/05/14 17:28:59 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_red_out(t_parser *pars, char **env)
{
	(void)env;
	if (dup2(pars->out_red, STDOUT_FILENO) < 0)
		return ;
	close(pars->out_red);
}

void	ft_red_in(t_parser *pars, char **env)
{
	(void)env;
	if (dup2(pars->in_red, STDIN_FILENO) < 0)
		return ;
	close(pars->in_red);
}

char	*ft_get_path(char **env)
{
	int i;
	
	i = 0;
	while (env[i])
	{
		if (!strncmp(env[i], "PATH", 4))
			return env[i];
		i++;
	}
	return NULL;
}

char	*ft_check_path(char *cmd, char **env)
{
	char	*holder;
	char	*path;
	char	**paths;
	int i = 1;

	path = ft_get_path(env);
	if (!path)
	{
		printf("minishell: %s: No such file or directory\n", cmd);
		exit(1);
	}
	paths = ft_split(path + 5, ':');
	holder = ft_strjoin(ft_strjoin_char(paths[0], '/'), cmd);
	while  (paths[i] && access(holder, F_OK))
	{
		holder = ft_strjoin(ft_strjoin_char(paths[i], '/'), cmd);
		i++;
	}
	return (holder);
}