/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:12:02 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/03/28 02:20:56 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_next_fd(t_lexer *lex, int in, int out)
{
	while (lex && lex->type != 'p')
	{
		if ((ft_strcmp(lex->word, ">") || ft_strcmp(lex->word, ">>"))
			&& out >= 3)
			close(out);
		else if (ft_strcmp(lex->word, "<") && in >= 3)
			close(in);
		lex = lex->next;
	}
}

void	ft_norm_herdoc(char *str, char *del, char *hold, int fd)
{
	while (ft_strcmp(str, del))
	{
		str = readline("\e[91mheredoc>  \e[0m");
		if (!str)
		{
			free(hold);
			close(fd);
			return ;
		}
		if (ft_strcmp(str, del))
			ft_putstr_fd(str, fd);
		free(str);
	}
}
char	*ft_hendel_var(t_lexer **lex, char **av)
{
    int i;

    i = 0;
    while (av[i] && strncmp(av[i], (*lex)->word, 4))
        i++;
    return av[i];
}