/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:20:43 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/20 16:14:03 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_norm_fill_args(t_lexer **lex, char **env, char **str, t_norm *var)
{
	if ((*lex) && (*lex)->type == 'r')
		ft_fill_heredoc_fm(&(*lex), &var->in, &var->out, env);
	if ((*lex) && (*lex)->type == 'h')
	{
		*lex = (*lex)->next;
		if ((*lex) && (*lex)->type == 's')
			*lex = (*lex)->next;
		if (var->in > 2 && var->in != var->fd[g_var->index])
			close(var->in);
		var->in = var->fd[g_var->index];
		while ((*lex) && ((*lex)->type == 'v' || (*lex)->type == 'w'))
			*lex = (*lex)->next;
	}
	if ((*lex) && ((*lex)->type == 'v' || (*lex)->type == 'w'))
	{
		ft_join_var_word(lex, str, env, var->i);
		return (1);
	}
	return (0);
}

void	ft_open_red(t_lexer **lex, int *fd, char **av, int status)
{
	char	*str;

	if ((*lex)->type != 'v' && status == 0)
		*fd = open((*lex)->word, O_RDONLY, 0777);
	else if ((*lex)->type != 'v' && status == 1)
		*fd = open((*lex)->word, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if ((*lex)->type != 'v' && status == 2)
		*fd = open((*lex)->word, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
	{
		str = ft_hendel_var((*lex)->word, av);
		if (!status)
			*fd = open(str, O_RDONLY, 0777);
		else if (status == 1)
			*fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else if (status == 2)
			*fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (*fd < 0 && !ft_strlen(str))
			*fd = -2;
		else
			*fd = -3;
		free(str);
	}
}

void	ft_close_open_herdoc(char *hold, int *fd)
{
	ft_putstr_fd(g_var->str, *fd);
	write(*fd, "\n", 1);
	close(*fd);
	*fd = open(hold, O_RDWR | O_CREAT | O_APPEND, 0777);
}

int	ft_fill_herdoc(t_lexer **lex, char **env, char *hold, int *fd)
{
	static char *del;
	g_var->in_hdc = 1;
	g_var->str = readline("heredoc>");
	if (!del)
		del = ft_get_delemiter(lex);
	if (!ft_strcmp(g_var->str, del))
	{
		free(del);
		del = NULL;
		g_var->in_hdc = 0;
		if (g_var->str)
			ft_free_char(&g_var->str);
		close(*fd);
		*fd = open(hold, O_RDWR | O_CREAT | O_APPEND, 0777);
		return (1);
	}
	if (!g_var->str)
		return (free(del), del = NULL, 1);
	if ((*lex) && (*lex)->in_quotes == 0 && ft_strchr(g_var->str, '$'))
		ft_norm_herdoc_norm(env, g_var->str, *fd);
	else if ((*lex) && ft_strcmp(g_var->str, (*lex)->word))
		ft_close_open_herdoc(hold, fd);
	if (g_var->str)
		ft_free_char(&g_var->str);
	return (0);
}

void	ft_handel_open_error(int in, int out, t_lexer **lex)
{
	if (in == -1 && *lex)
	{
		while ((*lex)->next)
		{
			if ((*lex)->next->type == 'p')
				break ;
			*lex = (*lex)->next;
		}
	}
	else if (out == -1 && (*lex)->word[0] == '/')
		ft_write_error_exc(": Permission denied\n", (*lex)->word);
}
