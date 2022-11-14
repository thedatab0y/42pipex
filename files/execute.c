/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:07:24 by busmanov          #+#    #+#             */
/*   Updated: 2022/11/14 16:28:13 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_strlen(char *string)//finds the len of the string
{
	int x;

	x = 0;
	if(!string)//error_handeling
		return(0);
	while(string[x])
	{
		x++;
	}
	return(x);
}

void error_msg(char *command)
{//printing the message in case the command is not found
	write(2, "command not found: ", ft_strlen("command not found: "));//using ft_strlen to get the len of the string for write
	write(2, command, ft_strlen(command));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);// 1  = Exit_failure
}

char *obtain_cmdpath(char *path, char *command)//gets the cmd_path by joining the path with the command
{
	char *p;
	
	p = ft_strjoin(path, command);//libft func
	free(path);//free to prevent leaks
	return(p);
}

char *obtain_path(char **envp)//get whats after "PATH=" = 5 chars
{
	int x;

	x = 0;
	while (envp[x])
	{
		if (ft_strncmp(envp[x], "PATH=", 5) == 0)//compares two strings up to nth char
			return(envp[x] + 5);//get whats after "PATH=" = 5 chars
		x++;
	}
	return(0);
}

void execute(char **envp, char *av)//function to execute the function
{
	char **splitted_path;
	char *second_path;//right
	char **command;
	int x;
	int counter;

	splitted_path = ft_split(obtain_path(envp), ':');//we need the path splitted from :
	command = ft_split(av, ' ');//we dont need the space between commands
	x = 0;
	counter = 0;
	while (splitted_path[x])//as long as i have the splittled path, i can execute
	{
		second_path =obtain_cmdpath(ft_strjoin(splitted_path[x], "/"), command[0]);
		if (access(second_path, R_OK) == 0)// checking the access
		{
			if (execve(second_path, command, envp) == -1)// checking the execution of the program that is referred to by pathname
				perror("Execve error: ");//error message in case the execution does not work
		}
		else
			counter++;
		free(second_path);//free to prevent leaks
		x++;
	}
	if (counter == x)
		error_msg(command[0]);
}
