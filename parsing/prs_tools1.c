/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:12:02 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/04/03 19:50:06 by aen-naas         ###   ########.fr       */
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
	char	*str;
	char	*str1;

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
			str1 = ft_hendel_var(str, env);
			ft_putstr_fd(str1, fd);
			write(fd, "\n", 1);
			free(str1);
		}
		else if (ft_strcmp(str, lex->word))
			ft_putstr_fd(str, fd);
		free(str);
	}
}

char	*ft_hendel_var_herdoc(char *val, char **av)
{
	int		i;
	int		j;
	int		len;
	char	*holder;

	j = 0;
	i = 0;
	while (val[j] && val[j] != '$')
		j++;
	len = j;
	while (val[len] && val[len] != ' ')
		len++;
	len -= j;
	while (av[i] && ft_strncmp(av[i], val + j + 1, len - 1))
		i++;
	if (!av[i])
		return (ft_strdup(""));
	if (j > 0)
		holder = ft_strjoin(ft_substr(val, 0, j), av[i] + len);
	else
		holder = av[i] + len;
	return (ft_strjoin(holder, val + len + j));
}

int	ft_check_other_var(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '$')
		i++;
	if (var[i] == '$')
		return (1);
	return (0);
}

char	*ft_hendel_var(char *val, char **av)
{
	int		i;
	int		j;
	int		len;
	int		k;
	char	*holder;

	j = 0;
	i = 0;
	while (val[j] && val[j] != '$')
		j++;
	len = j + 1;
	while (val[len] && (val[len] == '_' || ft_isalnum(val[len])))
		len++;
	len -= j;
	while (av[i])
	{
		k = 0;
		while (av[i] && av[i][k] != '=')
			k++;
		if (!ft_strncmp(av[i], val + j + 1, k) && !ft_strncmp(av[i], val + j
				+ 1, len - 1))
			break ;
		i++;
	}
	if (!ft_check_other_var(val + j + 1))
	{
		if (!av[i] && !j)
			holder = (ft_strdup(""));
		else if (!av[i] && j)
			holder = (ft_substr(val, 0, j));
		else if (j > 0)
			holder = ft_strjoin(ft_substr(val, 0, j), av[i] + k + 1);
		else
			holder = ft_strdup(av[i] + k + 1);
		holder = ft_strjoin(holder, val + j + len);
	}
	else
	{
		if (!av[i] && !j)
			holder = ft_strjoin(ft_strdup(""), val + len + j);
		else if (!av[i] && j)
			holder = ft_strjoin(ft_substr(val, 0, j), val + len + j);
		else if (j > 0)
			holder = ft_strjoin(ft_substr(val, 0, j), av[i] + k + 1);
		else
			holder = ft_strdup(av[i] + k + 1);
		if (av[i])
			holder = ft_strjoin(holder, val + j + k + 1);
		holder = ft_hendel_var(holder, av);
	}
	return (holder);
}
