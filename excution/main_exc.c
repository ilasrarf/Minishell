/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:01:38 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/17 17:17:58 by aen-naas         ###   ########.fr       */
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

void	ft_print_error(char *cmd)
{
	DIR	*dir;

	if (errno == ENOENT)
		ft_write_error_exc(" : No such file or directory\n", cmd);
	else if (errno == EACCES)
	{
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
	else if (errno == ENOEXEC)
		perror("minishell: ");
	else
		perror("minishell: ");
	exit(127);
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
	(void)env;
	g_var->exc = 1;
	if (!pars->next && ft_check_built(pars))
	{
		ft_dup_built(pars, fd);
		ft_builtins(&pars, env_list, env);
		if (fd[1] > 2)
			dup2(fd[1], STDOUT_FILENO);
		if (fd[0] > 2)
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		return ;
	}
	else
		ft_exc_loop(pars, env, fd, env_list);
	while (wait(0) != -1 || errno != ECHILD)
		;
	g_var->exc = 1;
	ft_add_lst_cmd(env_list, pars, env);
	close(fd[0]);
}
