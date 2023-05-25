/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_tools1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:05:28 by aen-naas          #+#    #+#             */
/*   Updated: 2023/05/25 16:40:50 by ilasrarf         ###   ########.fr       */
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
	if (!paths[i])
		printf("minishell: %s: : command not found\n", cmd);
	if (paths)
		ft_free(paths);
	return (holder);
}

void	ft_norm_exc(t_parser *pars, char **env, int fd[2], t_env **env_list)
{
	if (!ft_strcmp(pars->args[0], "exit") && !pars->next && fd[0] == -1)
	{
		if (!ft_check_exit_args(pars->args))
		{
			write(1, "exit", 4);
			exit(ft_atoi(pars->args[1]));
		}
	}
	else
	{
		ft_pipe(pars, env, fd, env_list);
		if (pars->out_red > 2)
			close(pars->out_red);
		if (pars->in_red > 2)
			close(pars->in_red);
	}
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
}
