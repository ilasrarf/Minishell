/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:01:38 by aen-naas          #+#    #+#             */
/*   Updated: 2023/05/27 22:52:18 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_error(char *cmd)
{
	(void)cmd;
	if (errno == ENOENT)
		perror("minishell: ");
	else if (errno == EACCES)
	{
		// perror("minishell");
		// if (access(cmd, R_OK | X_OK) == 0) 
		// {
            	// printf("minishell: %s: No such file or directory\n", cmd);
		// }
		// else
		// 	printf("minishell: %s: Permission denied\n", cmd);
		exit(126);
	}
	exit(127);
}

int	ft_pipe(t_parser *pars, char **env, int fd[2], t_env **env_list)
{
	char	*str;
	int 	i = 0;
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
	if (id == 0)
	{
		ft_dup_fd(pars, old, fd);
		signal(SIGINT, SIG_DFL);
		i = ft_builtins(&pars, env_list);
		if (i == 0 && pars->args[0])
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
	return 0;
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
	int i;


	fd[0] = -1;
	fd[1] = -1;
	if (!pars->next && ft_builtins(&pars , env_list) != 0)
			return ;
	else
	{
		while (pars)
		{
			g_var->exc = 0;
			if (pars->in_red >= 0)
			{
				i = ft_norm_exc(pars, env, fd, env_list);
				if (i == -1)
				{
					ft_putstr_fd("minishell: fork: Resource temporarily unavailable \n", 2);
					break ;
				}
				ft_status();
			}
			pars = pars->next;
		}
		}
		g_var->exc = 1;
	while (wait(0) != -1 || errno != ECHILD)
		;
	close(fd[0]);
}
