/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:30:24 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/20 22:16:35 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <limits.h>

void	ft_status(void)
{
	if (WIFEXITED(g_var->exit_s))
		g_var->exit_s = WEXITSTATUS(g_var->exit_s);
	else if (WIFSIGNALED(g_var->exit_s))
		g_var->exit_s = WTERMSIG(g_var->exit_s) + 128;
}

int	ft_check_exit_args(char **args)
{
	long	i;

	i = 0;
	if (args[1] == NULL)
		return (0);
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		g_var->exit_s = 1;
		return (1);
	}
	else
	{
		i = ft_atoi_exit(args[1]);
		if (g_var->overflow == -1)
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
	}
	return (0);
}

char	*ft_get_path_last(t_parser *pars, char **env)
{
	char	**res;
	char	*str;
	char	*path;
	int		i;

	i = 0;
	path = ft_get_path(env);
	if (!path)
		return (NULL);
	str = ft_strjoin(ft_strdup("/"), pars->args[0]);
	res = ft_split(path, ':');
	while (res && res[i])
	{
		path = ft_strjoin(ft_strdup(res[i]), str);
		if (!access(path, F_OK))
			break ;
		free(path);
		i++;
	}
	free(str);
	if (res && !res[i])
		path = NULL;
	ft_free(res);
	return (path);
}

void	ft_add_lst_cmd(t_env **env_list, t_parser *pars, char **env)
{
	char	*str;
	t_env	*hold;

	hold = *env_list;

	if (!pars->args || !pars->args[0])
		return ;
	while (pars->next)
		pars = pars->next;
	while (env_list && (*env_list)->next)
		*env_list = (*env_list)->next;
	if (*env_list && (*env_list)->name[0] == '_' && !(*env_list)->name[1])
	{
		if (!pars->args || !pars->args[0])
		{
			*env_list = hold;
			return ;
		}
		free((*env_list)->value);
		str = ft_get_path_last(pars, env);
		if (!str)
			(*env_list)->value = ft_strdup(pars->args[0]);
		else
			(*env_list)->value = str;
	}
	*env_list = hold;
}
