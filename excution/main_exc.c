/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:01:38 by aen-naas          #+#    #+#             */
/*   Updated: 2023/05/14 18:33:58 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pipe(t_parser *pars, char **env, int fd[2], int *status)
{
	char	*str;
	int		old;
	pid_t		id;
	(void)status;

	// str = NULL;
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
		else if (pars->in_red > 2)
			ft_red_in(pars, env);
		str = ft_check_path(pars->args[0], env);
		if (execve(str, pars->args, env) == -1)
		{
			// if (errno == EACCES)
			// 	puts("alo\n");
			// else
			// 	puts("no");
			// exit(127);
			perror("execve");
        	exit(EXIT_FAILURE);
		}
	}
	close(fd[1]);
	close(old);
	waitpid(id, &exit_s, 0);
}

int	ft_check_files(t_parser *pars)
{
	while (pars)
	{
		if (pars->in_red < 0)
			return 2;
		pars = pars->next;
	}
	return 0;
}

void	ft_excution(t_parser *pars, char **env)
{
	int	fd[2];
	int status;

	fd[0] = -1;
	fd[1] = -1;
	// if (ft_check_files(pars))
	// 	return ;
	while (pars)
	{
		ft_pipe(pars, env, fd, &status);
		pars = pars->next;
		ft_status();
	}
	while (wait(0) != -1 || errno != ECHILD)
		;
	// g_var = status;
	close(fd[0]);
}
