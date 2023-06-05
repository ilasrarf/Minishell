/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_tools1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:05:28 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/05 12:15:27 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_extra_handel(t_env **env_list, t_parser *pars, char *env)
{
	int		cnt1;
	int		shell_lvl;
	t_env	*tmp;
	int		j;

	cnt1 = 0;
	shell_lvl = 0;
	j = 0;
	tmp = *env_list;
	cnt1 = ft_cnt_name(env);
	if (!ft_strncmp("SHLVL=", env, cnt1 + 1))
	{
		shell_lvl = ft_atoi(env + 6) + 1;
		ft_lstadd_back_env(env_list, ft_lstnew_env(ft_substr(env, 0, cnt1),
				ft_itoa(shell_lvl)));
	}
	else
	{
		while (pars->args[j])
			j++;
		ft_lstadd_back_env(env_list, ft_lstnew_env(ft_substr(env, 0, cnt1),
				ft_strdup(pars->args[j - 1])));
	}
}

char	*ft_norm_check_path(char *cmd, char *path)
{
	int		i;
	char	**paths;
	char	*holder;

	i = 1;
	paths = ft_split(path + 5, ':');
	holder = ft_strjoin(ft_strjoin_char(ft_strdup(paths[0]), '/'), cmd);
	while (paths[i] && access(holder, F_OK))
	{
		holder = ft_strjoin(ft_strjoin_char(ft_strdup(paths[i]), '/'), cmd);
		i++;
	}
	if ((!paths[i] && !ft_strchr(cmd, '/')) || (cmd && !ft_strlen(cmd)))
	{
		ft_free(paths);
		ft_write_error_exc(": command not found\n", cmd);
		exit(127);
	}
	ft_free(paths);
	return (holder);
}

int	ft_norm_exc(t_parser *pars, char **env, int fd[2], t_env **env_list)
{
	int	i;

	i = ft_pipe(pars, env, fd, env_list);
	if (pars->out_red > 2)
		close(pars->out_red);
	if (pars->in_red > 2)
		close(pars->in_red);
	return (i);
}

void	ft_dup_fd(t_parser *pars, int old, int fd[2])
{
	close(fd[0]);
	if (pars->next)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (old != -1)
	{
		dup2(old, STDIN_FILENO);
		close(old);
	}
	if (pars->out_red > 2)
		ft_red_out(pars);
	if (pars->in_red > 2)
		ft_red_in(pars);
	close(fd[1]);
}

void	ft_exc_loop(t_parser *pars, char **env, int fd[2], t_env **env_list)
{
	int	i;

	while (pars)
	{
		g_var->exc = 0;
		i = ft_norm_exc(pars, env, fd, env_list);
		if (i == -1)
		{
			ft_putstr_fd("minishell: fork: ", 2);
			ft_putstr_fd("Resource temporarily unavailable \n", 2);
			break ;
		}
		ft_status();
		pars = pars->next;
	}
}
