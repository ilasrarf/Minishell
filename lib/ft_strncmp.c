/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 01:25:37 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/04/03 19:51:26 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int				i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	if (!s1)
		return (1);
	while ((ss1[i] != '\0' || ss2[i] != '\0') && i < n)
	{
		if (ss1[i] < ss2[i])
			return (-1);
		else if (ss1[i] > ss2[i])
			return (1);
		i++;
	}
	return (0);
}
