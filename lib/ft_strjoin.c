/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:08:15 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/04/01 08:54:31 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*alloc;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	i = 0;
	j = 0;
	alloc = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!alloc)
		return (0);
	while (s1[i])
	{
		alloc[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		alloc[i] = s2[j];
		j++;
		i++;
	}
	alloc[i] = '\0';
	free(s1);
	return (alloc);
}

char	*ft_strjoin_char(char *s1, char s2)
{
	char	*alloc;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	i = 0;
	j = 0;
	alloc = (char *)malloc(ft_strlen(s1) + 2);
	if (!alloc)
		return (0);
	while (s1[i])
	{
		alloc[i] = s1[i];
		i++;
	}
	alloc[i++] = s2;
	free(s1);
	alloc[i] = '\0';
	return (alloc);
}
