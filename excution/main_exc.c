/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:01:38 by aen-naas          #+#    #+#             */
/*   Updated: 2023/05/26 16:51:19 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_error(char *cmd)
{
	if (errno == EACCES)
	{
		printf("minishell: %s: : Permission denied\n", cmd);
		exit(126);
	}
	else
		exit(127);
}

void	ft_pipe(t_parser *pars, char **env, int fd[2], t_env **env_list)
{
	char	*str;
	int 	i = 0;
	int		old;
	pid_t	id;

	old = fd[0];
	pipe(fd);
	id = fork();
	if (id == 0)
	{
		ft_dup_fd(pars, old, fd);
		i = ft_builtins(&pars, env_list);
		if (i == 0)
		{
			str = ft_check_path(pars->args[0], env);
			if (execve(str, pars->args, env) == -1)
				ft_print_error(pars->args[0]);
		}
		else
			exit(0);
	}
	close(fd[1]);
	close(old);
	if (!pars->next)
		waitpid(id, &g_var->exit_s, 0);
}

int	ft_check_files(t_parser *pars)
{
	while (pars)
	{
		if (pars->in_red == -1)
			return (g_var->exit_s = 1);
		pars = pars->next;
	}
	return (0);
}

void	ft_excution(t_parser *pars, char **env, t_env **env_list)
{
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (!pars->next)
	{
		if (ft_builtins(&pars , env_list) == 0)
			return ;
	}
	while (pars)
	{
		if (pars->in_red >= 0)
		{
			ft_norm_exc(pars, env, fd, env_list);
			ft_status();
		}
		pars = pars->next;
	}
	while (wait(0) != -1 || errno != ECHILD)
		;
	close(fd[0]);
}
