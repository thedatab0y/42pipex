/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:07:25 by busmanov          #+#    #+#             */
/*   Updated: 2022/11/14 16:23:42 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void first_process(int infile, char **av, char **envp, int *fd)//env[] = envirenmental variable -> retreived from main
{//av[] = the args the command needs, for ex: 'ls -la'. I can use ft_split to obtain a char**. Like this: {"ls", "la", NULL}, it must be NULL terminated
	dup2(fd[1], STDOUT_FILENO);//and fd[1] to be our stdout (we write to fd[1] the output of cmd1)
	dup2(infile, STDIN_FILENO);//For the child process, we want infile to be our stdin (as input), 
	close(fd[0]);//This is the PARENT
	execute(envp, av[2]);
}

//    infile                                             outfile
// as stdin for cmd1                                 as stdout for cmd2            
//        |                        PIPE                        ↑
//        |           |---------------------------|            |
//        ↓             |                       |              |
//       cmd1   -->    end[1]       ↔       end[0]   -->     cmd2           
//                      |                       |
//             cmd1   |---------------------------|  end[0]
//            output                             reads end[1]
//          is written                          and sends cmd1
//           to end[1]                          output to cmd2
//        (end[1] becomes                      (end[0] becomes 
//         cmd1 stdout)                           cmd2 stdin)


void second_process(int outfile, char **av, char **envp, int *fd)
{
	dup2(fd[0], STDIN_FILENO);//In the parent process, we want end[0] to be our stdin (fd[0] reads from end[1] the output of cmd1)
	dup2(outfile, STDOUT_FILENO);//and the outfile to be our stdout(we write to it the output of cmd1)
	close(fd[1]);
	execute(envp, av[3]);
}

//pipe(fd) = Recives a fd[2] and opens
//fd[0] for reading and fd[1] for writing
//pipefd[0] is for reading data from pipe
//pipefd[1] is for writing data to pipe
//on success, the pipe func returns 0, otherwise -1

// # ./pipex infile cmd1 cmd2 outfile
// pipe()
//  |
//  |-- fork()
//       |
//       |-- child 1 // cmd1
//       :     |--dup2()
//       :     |--close end[0]
//       :     |--execve(cmd1)
//       :
//       |-- child 2 // cmd2
//             |--dup2()
//             |--close end[1]
//             |--execve(cmd2)

void pipex(int infile, int outfile, char **av, char **envp)
{
	int fd[2];//end fd // an array that will hold two file discriptors
	pid_t parent;
	int status;

	if (pipe(fd) == -1)
		return(perror("Pipe: "));
	parent = fork();//create child process that is a clone of the parent
	if (parent == -1)
		return(perror("Fork Error: "));
	else if (parent == 0)//if parent == 0, then wE ARE in a CHILD process
		first_process(infile, av, envp, fd);//child process
	else
	{//could also do "NULL" instead of &status
		waitpid(parent, &status, 0);//wait for the child to finish
		second_process(outfile, av, envp, fd);//parent process
	}
	return ;
}

int main(int ac, char **av, char **envp)
{
	int infile;//number of bytes
	int outfile;//num of bytes

	if (ac == 5)//we are required to have 5 arguments
	{
		infile = open(av[1], O_RDONLY, 0777);
		outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (infile == -1 || outfile == -1)
		{
			perror("File could not be opened!");
			exit(EXIT_FAILURE);
		}
		pipex(infile, outfile, av, envp);
	}
	else
	{
		if (ac < 5)
			write(1, "not enough arguments!", 21);
		else
			write(1, "Ample number of arguments!", 26);
	}
	return(1);
}
