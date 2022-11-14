/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:35:37 by busmanov          #+#    #+#             */
/*   Updated: 2022/11/13 00:25:50 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../func/pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	size_t			j;
	unsigned char	*s3;
	unsigned char	*s4;

	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	i = 0;
	j = 1;
	if (n == 0)
		return (-1);
	while (s3[i] && s4[i] && s3[i] == s4[i] && j < n)
	{	
		i++;
		j++;
	}
	return (s3[i] - s4[i]);
}
