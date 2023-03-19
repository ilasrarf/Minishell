/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:23:37 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/03/19 18:37:20 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer    *ft_parser(t_lexer *lex)
{
    t_lexer *holder;
    t_lexer *new_lex;
    char    *str;

    holder = lex;
    while (lex)
    {
        str = lex->word;
        while (lex->next && lex->type == 'w' && lex->next->type == 'w')
        {
            str = ft_strjoin(str, lex->next->word);
            lex = lex->next;
        }
        ft_lstadd_back(&new_lex, ft_lstnew(str, lex->type, lex->in_quotes));
        lex = lex->next;
    }
    return (new_lex);
}