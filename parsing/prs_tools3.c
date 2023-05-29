/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:20:43 by aen-naas          #+#    #+#             */
/*   Updated: 2023/05/29 17:50:03 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_norm_fill_args(t_lexer **lex, char **env, char **str, t_norm *var)
{
	if ((*lex) && (*lex)->type == 'p')
		return (1);
	if ((*lex) && (!ft_strcmp((*lex)->word, ">") || !ft_strcmp((*lex)->word,
				"<") || !ft_strcmp((*lex)->word, ">>")) && (*lex)->type == 'r')
		ft_fill_heredoc_fm(&(*lex), &var->in, &var->out, env);
	if ((*lex) && !ft_strcmp((*lex)->word, "<<") && (*lex)->type == 'r')
		ft_use_heredoc(&(*lex), env, &var->in);
	if ((*lex) && ((*lex)->type == 'v' || (*lex)->type == 'w'))
	{
		ft_join_var_word(lex, str, env, var->i);
		return (1);
	}
	return (0);
}

void	ft_handel_in(t_lexer **lex, int *in, char **av)
{
	(void)av;
	if ((*lex)->type != 'v')
		*in = open((*lex)->word, O_RDONLY, 0777);
	else
	{
		*in = open(ft_hendel_var((*lex)->word, av), O_RDONLY, 0777);
		if (*in < 0)
			*in = -2;
	}
}

int	ft_fill_herdoc(t_lexer *lex, char **env, char *hold, int fd)
{
	char	*str;

	str = readline("\e[91mheredoc>  \e[0m");
	if (!ft_strcmp(str, lex->word))
		return (1);
	if (!str)
	{
		close(fd);
		return (1);
	}
	if (lex->in_quotes == 0 && ft_strchr(str, '$'))
		ft_norm_herdoc_norm(env, str, fd);
	else if (ft_strcmp(str, lex->word))
	{
		ft_putstr_fd(str, fd);
		write(fd, "\n", 1);
		close(fd);
		fd = open(hold, O_RDWR | O_CREAT | O_APPEND, 0777);
	}
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (0);
}

void	ft_handel_open_error(int out, t_lexer *lex)
{
	if (out == -1 && (lex)->word[0] == '/')
		fprintf(stderr, "Minishell: /f: Permission denied\n");
}
