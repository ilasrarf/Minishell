/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:01:38 by aen-naas          #+#    #+#             */
/*   Updated: 2023/05/26 18:50:42 by aen-naas         ###   ########.fr       */
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

int	ft_pipe(t_parser *pars, char **env, int fd[2])
{
	int		old;
	pid_t	id;

	old = fd[0];
	pipe(fd);
	id = fork();
	if (id < 0)
	{
		close (fd[0]);
		close (fd[1]);
		return -1;
	}
		
	else if (id == 0)
	{
		ft_dup_fd(pars, old, fd);
		if (!ft_strcmp(pars->args[0], "exit"))
			exit(0);
		else
		{
			if (execve(ft_check_path(pars->args[0], env), pars->args, env) == -1)
				ft_print_error(pars->args[0]);
		}
	}
	close(fd[1]);
	close(old);
	if (pars && !pars->next)
		waitpid(id, &g_var->exit_s, 0);
	return 1;
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

void	ft_excution(t_parser *pars, char **env)
{
	int	fd[2];
	int i;

	fd[0] = -1;
	fd[1] = -1;
	if (!pars->next)
    {
        if (ft_builtins(&pars , env_list) == 0)
            return ;
    }
	else
	{
		while (pars)
		{
			if (pars->in_red >= 0)
			{
				i = ft_norm_exc(pars, env, fd);
				if (i == -1)
				{
					ft_putstr_fd("minishell: fork: Resource temporarily unavailable \n",2);
					break ;
				}
				ft_status();
			}
			pars = pars->next;
		}
	}
	while (wait(0) != -1 || errno != ECHILD)
		;
	close(fd[0]);
}
