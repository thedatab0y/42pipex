/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:19:22 by busmanov          #+#    #+#             */
/*   Updated: 2022/11/13 13:17:09 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <stdlib.h>//process control
#include <stdio.h>//input&output
#include <unistd.h>// standard symbolic constants and types
#include <errno.h>//give more information about the error condition
#include <fcntl.h>// It allows the program to place a read or a write
#include <string.h>//for stderr

// char	*gpathcmd(char *p, char *cmd);
// //char 	obtain_cmdpath(char *path, char *command);
// char	*getpath(char **envp);
// void	exec(char **envp, char *argv);
// char	**ft_split(char const *s, char c);
// //int 	ft_strlen(char *string);
// char	*ft_strjoin(char const *s1, char const *s2);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*getpath(char **envp);
char	*gpathcmd(char *p, char *cmd);
void	exec(char **envp, char *argv);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
