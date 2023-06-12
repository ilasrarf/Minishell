/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_white_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:45:41 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/12 11:45:51 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_my_strtrim_w(const char *s1)
{
	int		len_s1;
	char	*str;

	str = (char *)s1;
	if (!str)
		return (0);
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	len_s1 = ft_strlen(str);
	while (len_s1 > 0 && (str[len_s1 - 1] == ' '
		|| (str[len_s1 - 1] >= 9 && str[len_s1 - 1] <= 13)))
		len_s1--;
	return (ft_substr(str, 0, len_s1));
}

int ft_cnt_words_w(char *str)
{
	int i;
	int cnt;

	cnt = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) &&
			!(str[i + 1] == ' ' || (str[i + 1] >= 9 && str[i + 1] <= 13)))
			cnt++;
		i++;
	}
	if (i == 0)
		return (0);
	return (cnt + 1);
}

static int ft_char_cnt(char *str)
{
	int i;

	i = 0;
	while (str[i] && !(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	return (i);
}

char **ft_append_w(char **res, char *str, int cnt_w)
{
	int i;

	i = 0;
	while (i < cnt_w)
	{
		while (*str == ' ' || (*str >= 9 && *str <= 13))
			str++;
		res[i] = ft_substr(str, 0, ft_char_cnt(str));
		if (!res)
		{
			i = 0;
			while (res[i] != NULL)
			{
				free(res[i]);
				i++;
			}
			free(res);
			return (NULL);
		}
		str += ft_char_cnt(str);
		i++;
	}
	return (res);
}

char **ft_split_white(char const *s)
{
	char **res;
	int i;
	int cnt_w;
	char *str;

	i = 0;
	str = ft_my_strtrim_w(s);
	if (!s || !str)
		return (NULL);
	cnt_w = ft_cnt_words_w(str);
	res = (char **)ft_calloc((cnt_w + 1), sizeof(char *));
	if (!res)
		return (0);
	res = ft_append_w(res, str, cnt_w);
	free(str);
	return (res);
}
