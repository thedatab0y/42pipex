/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:07:29 by busmanov          #+#    #+#             */
/*   Updated: 2022/11/14 17:04:37 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H
git 
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char 	*obtain_path(char **envp);
char 	*obtain_cmdpath(char *path, char *command);
void 	execute(char **envp, char *av);
char  	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int  	ft_strncmp(const char *st1, const char *st2, size_t x);

#endif