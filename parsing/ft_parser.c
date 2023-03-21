/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:23:37 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/03/21 02:31:18 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer *ft_new_lexer(t_lexer *lex)
{
    t_lexer *new_lex;
    char    *str;
    char    *str1;

    new_lex = NULL;
    while (lex)
    {
        str = lex->word;
        while (lex->next && lex->type == 'w' && lex->next->type == 'w')
        {
            str1 = str;
            str = ft_strjoin(str, lex->next->word);
            free(str1);
            lex = lex->next;
        }
        ft_lstadd_back(&new_lex, ft_lstnew(str, lex->type, lex->in_quotes));
        lex = lex->next;
    }
    // ft_lstclear_lex(&lex);
    return (new_lex);
}

int ft_count_arg(t_lexer *lex)
{
    int i;

    i = 0;
    while (lex)
    {
        if ((lex->word[0] == '|' && lex->in_quotes == 0) || ft_check_herdoc_fm(lex->word))
            return i;
        if (lex->word[0] != ' ')
            i++;
        lex = lex->next;
    }
    return i;
}

void    ft_fill_args(t_lexer *lex, t_parser **prs)
{
    int i;
    int j;
    char **str;
    i = ft_count_arg(lex);
    str = malloc(sizeof(char *) * i + 1);
    str[i] = NULL;
    j = 0;
    while (lex && !ft_check_herdoc_fm(lex->word))
    {
        if (!strcmp(lex->word, "|") && lex->in_quotes == 0)
            break ;
        if (strcmp(lex->word, " "))
        {
            str[j] = ft_strdup(lex->word);
            j++; 
        }
        lex = lex->next;
    }
    ft_lstadd_back_prs(prs, ft_lst_new_prs(str));
    if (lex && !strcmp(lex->word, "|"))
    {
        lex = lex->next;
        ft_fill_args(lex, prs);
    }
}

void    ft_parser(t_lexer *lex, t_parser **prs)
{
    t_parser *holder;
    *prs = NULL;
    ft_fill_args(lex, prs);
    holder = (*prs);
    // int i;
    // while(holder)
    // {
    //     i = 0;
    //     while (holder->args[i])
    //     {
    //         printf("%s\n",holder->args[i]);
    //         i++;
    //     }
    //     holder = holder->next;
    // }
    ft_lstclear_lex(&lex);
    ft_lstclear(prs);
}