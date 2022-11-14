/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:24:23 by busmanov          #+#    #+#             */
/*   Updated: 2022/11/13 00:21:47 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../func/pipex.h"

static int	cmp_nb_word(const char *s, char c)
{
	int	i;
	int	word;

	if (!s)
		return (0);
	word = 0;
	i = 0;
	while (s[i] == c && s[i] != '\0')
	{
		i++;
	}
	while (s[i])
	{
		while (s[i] && (s[i] != c))
			i++;
		word++;
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	return (word);
}

static int	cmp_nb_caract(const char *s, char c, char **str)
{
	int	n;
	int	i;
	int	m;

	n = 0;
	i = 0;
	m = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i])
	{
		while (s[i] && (s[i] != c))
		{
			i++;
			n++;
		}
		str[m] = malloc(sizeof(char) * (n + 1));
		if (!str)
			return (0);
		m++;
		n = 0;
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	return (0);
}

static void	ft_assembleall(char const *s, char c, char **str)
{
	int	i;
	int	m;
	int	mm;

	i = 0;
	m = 0;
	mm = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i])
	{
		while (s[i] && (s[i] != c))
		{
			str[m][mm] = s[i];
			i++;
			mm++;
		}
		str[m][mm] = '\0';
		mm = 0;
		m++;
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	str[m] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		m;
	int		mm;

	i = 0;
	m = 0;
	mm = 0;
	str = malloc((sizeof(char *) * (cmp_nb_word(s, c) + 1)));
	if (!str)
		return (NULL);
	cmp_nb_caract(s, c, str);
	ft_assembleall(s, c, str);
	return (str);
}