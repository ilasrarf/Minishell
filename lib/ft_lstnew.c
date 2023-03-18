/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:49:44 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/03/17 18:04:14 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*ft_lstnew(void *word)
{
	t_lexer	*n1;

	n1 = ft_calloc(1, sizeof(t_lexer));
	if (n1)
		n1->word = word;
	return (n1);
}
