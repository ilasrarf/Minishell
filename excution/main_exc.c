/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:01:38 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/22 00:02:48 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_handel_dotes(char *cmd)
{
	if (!ft_strcmp(cmd, "."))
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		exit(2);
	}
	else
		ft_putstr_fd("minishell: ..: command not found\n", 2);
	exit(127);
}

void	ft_access_error(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (!ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
		ft_handel_dotes(cmd);
	else if (dir)
	{
		ft_write_error_exc(": is a directory\n", cmd);
		closedir(dir);
	}
	else
		ft_write_error_exc(": Permission denied\n", cmd);
	exit(126);
}

void	ft_print_error(char *cmd)
{
	if (errno == ENOENT)
	{
		perror("minishell: ");
		exit(127);
	}
	else if (errno == EACCES)
		ft_access_error(cmd);
	else if (errno == ENOEXEC)
	{
		perror("minishell: ");
		exit(126);
	}
	else
		perror("minishell: ");
	exit(1);
}

int	ft_pipe(t_parser *pars, char **env, int fd[2], t_env **env_list)
{
	int		old;
	pid_t	id;

	old = fd[0];
	pipe(fd);
	id = fork();
	if (id < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (id == 0)
	{
		ft_sigdef();
		if (ft_close_fd(pars, fd))
			exit(1);
		ft_dup_fd(pars, old, fd);
		ft_excve(pars, env, env_list);
	}
	close(fd[1]);
	close(old);
	if (!pars->next)
		waitpid(id, &g_var->exit_s, 0);
	return (0);
}

void	ft_excution(t_parser *pars, char **env, t_env **env_list)
{
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	g_var->exc = 1;
	if (!pars->next && ft_check_built(pars) && pars->in_red != -1
		&& pars->out_red != -1)
	{
		ft_dup_built(pars, fd);
		ft_builtins(&pars, env_list, env);
		ft_dup_red_for_built(fd);
		close(fd[0]);
		close(fd[1]);
		return ;
	}
	else
		ft_exc_loop(pars, env, fd, env_list);
	while (wait(0) != -1 || errno != ECHILD)
		;
	ft_status();
	g_var->exc = 1;
	ft_add_lst_cmd(env_list, pars, env);
	close(fd[0]);
}
