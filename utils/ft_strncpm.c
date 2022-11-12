/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:35:37 by busmanov          #+#    #+#             */
/*   Updated: 2022/11/12 22:36:40 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../func/pipex.h"

int	ft_strncmp(const char *st1, const char *st2, size_t x)
{
	size_t	n;

	n = 0;
	if (x == 0)
		return (0);
	while (n < x - 1 && st1[n] != '\0' && st2[n] != '\0' && st1[n] == st2[n])
	{
		n++;
	}
	return ((unsigned char)st1[n] - (unsigned char)st2[n]);
}
