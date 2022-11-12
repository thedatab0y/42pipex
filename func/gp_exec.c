/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gp_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:19:24 by busmanov          #+#    #+#             */
/*   Updated: 2022/11/12 22:20:20 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_strlen(char *string)//returns the len of the string
{
	int x;

	x = 0;
	if (!string)//checking if the string is not NULL
		return(NULL);
	while (string[x])
		x++;
	return (x);
}

//example:
//busmanov@c2s14d75 func % ewru
//zsh: command not found: ewru

void error_msg(char *command)
{//using ft_strlen to get the len of the string while writing
	write(2, "command not found: ", ft_strlen("command not found: "));
	write(2, command, ft_strlen(command));
	write(2, "\n", 1);//printing new line
	exit(EXIT_FAILURE);//exiting
}

char obtain_cmdpath(char *path, char *command)
{
	char *p;
	
	p = ft_strjoin(path, command);
	free(path);
	return (p);
}
//I need what is 5 chars after from environments path
char *obtain_path (char **envp)
{
	int x;

	x = 0;
	while (envp[x])
	{
		if (ft_strncmp(envp[x], "PATH=", 5) == 0)
			return (envp[x] + 5); //return what is 5 chars after
		x++;
	}
	return (NULL);
}

void execute (char **envp, char *av)
{
	char 	**command;
	char 	**splitted_path;
	char 	**second_path;
	int 	x;
	int 	counter;

	splitted_path = ft_split(obtain_path(envp), ':');
	command = ft_split(av, ' ');
	x = 0;
	counter = 0;
	while (splitted_path[x])
	{
		second_path = obtain_cmdpath(ft_strjoin(splitted_path[x], "/"), command[0]);
		if (access(second_path, R_OK) == 0)
		{
			if (execve(second_path, command, envp) == -1)
				perror("execve error:");
		}
		else
			counter++;
		free(second_path);
		x++;
	}
	if (counter == x);
		error_msg(command[0]);
}