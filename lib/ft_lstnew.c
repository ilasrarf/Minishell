/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:49:44 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/06 15:57:30 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*ft_lstnew(void *word, char type, int in_quotes)
{
	t_lexer	*n1;

	n1 = ft_calloc(1, sizeof(t_lexer));
	if (n1)
	{
		n1->word = word;
		n1->type = type;
		n1->in_quotes = in_quotes;
	}
	return (n1);
}

t_env	*ft_lstnew_env(void *name, void *val)
{
	t_env	*n1;

	n1 = ft_calloc(1, sizeof(t_env));
	if (n1)
	{
		n1->name = name;
		n1->value = val;
	}
	n1->next = NULL;
	return (n1);
}
