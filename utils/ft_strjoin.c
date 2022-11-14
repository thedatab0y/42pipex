/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:05:00 by busmanov          #+#    #+#             */
/*   Updated: 2022/11/14 16:09:23 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../files/pipex.h"

char  *ft_strjoin(char const *s1, char const *s2)
{
  int    x;
  int    y;
  char  *str;

  x = 0;
  y = 0;
  while (s1[x])
    x++;
  while (s2[y])
    y++;
  str = malloc(sizeof(*s1) * (x + y + 1));
  if (str == 0)
    return (NULL);
  x = 0;
  y = 0;
  while (s1[x])
  {
    str[x] = s1[x];
    x++;
  }
  while (s2[y])
    str[x++] = s2[y++];
  str[x] = '\0';
  return (str);
}
