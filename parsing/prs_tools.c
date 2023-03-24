/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:16:02 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/03/24 00:30:13 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    ft_check_in_out_snt(t_lexer *lex)
{
    while (lex)
    {
        if (ft_check_herdoc_fm(lex->word))
        {
            if (lex->next && !ft_strcmp(lex->next->word, " "))
                lex = lex->next;
            if (!lex->next || (lex->next->type != 'w'))
            {
                printf("syntax error near unexpected token `%s'\n", lex->word);
                return (0);
            }
        }
        lex = lex->next;
    }
    return (1);
}

int ft_count_heredoc(t_lexer *lex)
{
    int i;

    i = 0;
    while (lex)
    {
       if (!ft_strcmp(lex->word, ">") || !ft_strcmp(lex->word, "<"))
            i++;
        lex = lex->next;
    }
    return (i);
}
