/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 10:46:04 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/15 22:43:40 by aen-naas         ###   ########.fr       */
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
	{
		ft_putstr_fd("error\n", 2);
		return ;
	}
	close(pars->in_red);
}

char	*ft_get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!strncmp(env[i], "PATH=", 5))
		{
			if (!ft_strlen(env[i] + 5))
				return NULL;
			return (env[i]);
		}
		i++;
	}
	return (NULL);
}

int	f_check_if_path(char *cmd)
{
	if (cmd[0] == '.' && cmd[1] == '/')
		return (1);
	else if (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/')
		return (1);
	return (0);
}

char	*ft_check_path(char *cmd, char **env)
{
	char	*path;
	int		j;

	j = 0;
	while (env[j] && ft_strncmp("PATH=", env[j], 5))
		j++;
	if (ft_strchr(cmd, '/') || f_check_if_path(cmd) || !access(cmd, F_OK))
		return (cmd);
	else
		path = ft_get_path(env);
	if ((!path && !ft_strchr(cmd, '/')))
	{
		ft_write_error_exc(": No such file or directory\n", cmd);
		exit(1);
	}
	return (ft_norm_check_path(cmd, path));
}
