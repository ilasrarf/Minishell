/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:34:49 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/21 14:53:48 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_norm_herdoc_norm(char **env, char *str, int fd)
{
	char	*str1;

	str1 = ft_hendel_var(NULL, str, env);
	ft_putstr_fd(str1, fd);
	write(fd, "\n", 1);
	free(str1);
}

void	ft_join_var_word(t_lexer **lex, char **str, char **env, int i)
{
	int		j;
	char	*str2;

	str2 = NULL;
	j = 0;
	if ((*lex) && (*lex)->type == 'v')
	{
		if ((*lex)->in_quotes == 2)
			j++;
		str2 = ft_hendel_var(*lex, (*lex)->word, env);
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
		str[i] = ft_join_args(lex, str, env, i);
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
