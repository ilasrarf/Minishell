/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 10:46:04 by aen-naas          #+#    #+#             */
/*   Updated: 2023/05/28 12:54:44 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_red_out(t_parser *pars)
{
	if (dup2(pars->out_red, STDOUT_FILENO) < 0)
		return ;
	close(pars->out_red);
}

void	ft_red_in(t_parser *pars)
{
	if (dup2(pars->in_red, STDIN_FILENO) < 0)
		return ;
	close(pars->in_red);
}

char	*ft_get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!strncmp(env[i], "PATH", 4))
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	*ft_check_path(char *cmd, char **env)
{
	char	*path;
	int		j;

	j = 0;
	while (env[j])
		j++;
	if (!access(cmd, F_OK))
		return (cmd);
	if (j == 3)
		path = g_var->path;
	else
		path = ft_get_path(env);
	if ((!path && !ft_strchr(cmd, '/')) || (cmd && !ft_strlen(cmd)))
	{
		printf("minishell: %s: No such file or directory\n", cmd);
		exit(1);
	}
	return (ft_norm_check_path(cmd, path));
}
