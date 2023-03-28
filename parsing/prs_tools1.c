/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:12:02 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/03/28 06:44:26 by aen-naas         ###   ########.fr       */
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

void	ft_norm_herdoc(t_lexer *lex, char **env, char *hold, int fd)
{
	char *str;

	str = NULL;
	while (ft_strcmp(str, lex->word))
	{
		str = readline("\e[91mheredoc>  \e[0m");
		if (!str)
		{
			free(hold);
			close(fd);
			return ;
		}
		if (lex->in_quotes == 0 && ft_strchr(str, '$'))
		{
			ft_putstr_fd(ft_hendel_var(str, env), fd);
		}
		else if (ft_strcmp(str, lex->word))
			ft_putstr_fd(str, fd); 
		free(str);
	}
}
char	*ft_hendel_var(char *val, char **av)
{
    int i;

    i = 0;
    while (av[i] && strncmp(av[i], val + 1, ft_strlen(val) - 1))
        i++;
	printf("%s\n",val);
    return av[i] + ft_strlen(val);
}