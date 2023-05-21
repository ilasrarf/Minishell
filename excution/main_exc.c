/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:01:38 by aen-naas          #+#    #+#             */
/*   Updated: 2023/05/21 12:21:40 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_pipe(t_parser *pars, char **env, int fd[2])
{
	char	*str;
	int		old;
	pid_t		id;

	old = fd[0];
	pipe(fd);
	id = fork();
	if (id == 0)
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
			ft_red_out(pars, env);
		if (pars->in_red > 2 )
			ft_red_in(pars, env);
		if (!ft_strcmp(pars->args[0], "exit"))
			exit(0);
		else
		{
			str = ft_check_path(pars->args[0], env);
			if (execve(str, pars->args, env) == -1)
			{
				if (errno == EACCES)
				{
					printf("minishell: %s: : Permission denied\n", pars->args[0]);
					exit(126);
				}
				else
					exit(127);
			}
		}
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
		if (pars->in_red < 0)
			return (g_var->exit_s = 1);
		pars = pars->next;
	}
	return 0;
}

void	ft_excution(t_parser *pars, char **env)
{
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (ft_check_files(pars))
		return ;
	while (pars)
	{
		if (!pars->args[0])
			break;
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
			ft_pipe(pars, env, fd);
			if (pars->out_red > 2)
				close(pars->out_red);
			// if (pars->in_red > 2)
			// 	close(pars->in_red);
		}
		pars = pars->next;
		ft_status();
	}
	while (wait(0) != -1 || errno != ECHILD)
		;
	close(fd[0]);
}
