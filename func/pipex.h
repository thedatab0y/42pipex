/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:19:22 by busmanov          #+#    #+#             */
/*   Updated: 2022/11/12 22:28:15 by busmanov         ###   ########.fr       */
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

char obtain_cmdpath(char *path, char *command);
char *obtain_path (char **envp);
void execute (char **envp, char *av);
char	**ft_split(char const *s, char c);
int ft_strlen(char *string);



#endif