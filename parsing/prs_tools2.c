/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:34:49 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/17 15:52:05 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_norm_herdoc_norm(char **env, char *str, int fd)
{
	char	*str1;

	str1 = ft_hendel_var(str, env);
	ft_putstr_fd(str1, fd);
	write(fd, "\n", 1);
	free(str1);
}

void	ft_join_var_word(t_lexer **lex, char **str, char **env, int i)
{
	// char	*str1;
	int		j;
	char	*str2;

	str2 = NULL;
	j = 0;
	if ((*lex) && (*lex)->type == 'v')
	{
		if ((*lex)->in_quotes == 2)
			j++;
		str2 = ft_hendel_var((*lex)->word, env);
		if (!ft_strlen(str2))
		{
			free(str2);
			str2 = NULL;
		}
		ft_norm_join_var_il(str, str2, i, j);
	}
	else if (*lex)
		str[i] = ft_strdup((*lex)->word);
	(*lex) = (*lex)->next;
	while ((*lex) && ((*lex)->type == 'w' || (*lex)->type == 'v'))
	{
		str[i] = ft_join_args(lex, str, env, i);
	}
}

t_calcul	ft_inial_cal(void)
{
	t_calcul	cl;

	cl.i = 0;
	cl.j = 0;
	cl.k = 0;
	cl.len = 0;
	return (cl);
}

char	*ft_one_plus_var(char **av, t_calcul cl, char *holder, char *val)
{
	if (!av[cl.i] && !cl.j)
		holder = ft_strjoin(ft_strdup(""), val + cl.len + cl.j);
	else if (!av[cl.i] && cl.j)
		holder = ft_strjoin(ft_substr(val, 0, cl.j), val + cl.len + cl.j);
	else if (cl.j > 0)
		holder = ft_strjoin(ft_substr(val, 0, cl.j), av[cl.i] + cl.k + 1);
	else
		holder = ft_strdup(av[cl.i] + cl.k + 1);
	if (av[cl.i])
		holder = ft_strjoin(holder, val + cl.j + cl.k + 1);
	return (ft_hendel_var(holder, av));
}

char	*ft_norm_hendle_var(char **av, char *val, t_calcul cl)
{
	char	*holder;

	holder = NULL;
	if (!ft_check_other_var(val + cl.j + 1))
	{
		if (!av[cl.i] && !cl.j)
			holder = (ft_strdup(""));
		else if (!av[cl.i] && cl.j)
			holder = (ft_substr(val, 0, cl.j));
		else if (cl.j > 0)
			holder = ft_strjoin(ft_substr(val, 0, cl.j), av[cl.i] + cl.k + 1);
		else
			holder = ft_strdup(av[cl.i] + cl.k + 1);
		holder = ft_strjoin(holder, val + cl.j + cl.len);
	}
	else
		holder = ft_one_plus_var(av, cl, holder, val);
	return (holder);
}
