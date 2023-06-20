/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:49:58 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/20 20:48:39 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_excve(t_parser *pars, char **env, t_env **env_list)
{
	char	*str;
	int		i;

	signal(SIGINT, SIG_DFL);
	i = ft_builtins(&pars, env_list, env);
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

void	ft_dup_built(t_parser *pars, int fd[2])
{
	if (pars->out_red > 2)
	{
		fd[1] = dup(STDOUT_FILENO);
		dup2(pars->out_red, STDOUT_FILENO);
		close(pars->out_red);
	}
	if (pars->in_red > 2)
	{
		fd[0] = dup(STDIN_FILENO);
		dup2(pars->in_red, STDIN_FILENO);
		close(pars->in_red);
	}
}

int	ft_check_built(t_parser *pars)
{
	if (!ft_strcmp(pars->args[0], "echo") || !ft_strcmp(pars->args[0], "ECHO"))
		return (1);
	else if (!ft_strcmp(pars->args[0], "exit"))
		return (1);
	else if (!ft_strcmp(pars->args[0], "cd") || !ft_strcmp(pars->args[0], "CD"))
		return (1);
	else if (!ft_strcmp(pars->args[0], "pwd") || !ft_strcmp(pars->args[0],
			"PWD"))
		return (1);
	else if (!ft_strcmp(pars->args[0], "env") || !ft_strcmp(pars->args[0],
			"ENV"))
		return (1);
	else if (!ft_strcmp(pars->args[0], "export"))
		return (1);
	else if (!ft_strcmp(pars->args[0], "unset"))
		return (1);
	return (0);
}
