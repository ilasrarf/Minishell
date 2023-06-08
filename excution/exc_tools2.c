/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:49:58 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/08 18:28:08 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_excve(t_parser *pars, char **env, t_env **env_list)
{
	char	*str;
	int		i;

	signal(SIGINT, SIG_DFL);
	i = ft_builtins(&pars, env_list);
	if (pars->args[0] && !i)
	{
		str = ft_check_path(pars->args[0], env);
		if (execve(str, pars->args, env) == -1)
			ft_print_error(pars->args[0]);
	}
	exit(g_var->exit_s);
}

int	ft_close_fd(t_parser *pars, int fd[2])
{
	if (pars->in_red < 0 || pars->out_red < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	return (0);
}

char	*ft_env_while(t_env *env, char *str)
{
	if ((env)->value)
		return (ft_strjoin(ft_strjoin_char(ft_strdup((env)->name), '='),
				(env)->value));
	return (ft_strjoin(ft_strjoin_char(ft_strdup((env)->name), '='), str));
}
