/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:19:20 by busmanov          #+#    #+#             */
/*   Updated: 2022/11/12 20:50:05 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
//       |-- child // cmd1
//       :     |--dup2()
//       :     |--close end[0]
//       :     |--execve(cmd1)
//       :
//       |-- parent // cmd2
//             |--dup2()
//             |--close end[1]
//             |--execve(cmd2)


void pipex(int infile, int outfile, char **argv, char **envp)
{//argv[] = the args the command needs, for ex: 'ls -la'. I can use ft_split to obtain a char**. Like this: {"ls", "la", NULL}, it must be NULL terminated
	//split on : to retreieve all possible PATHs
	int fd[2];//end fd // an array that will hold two file discriptors
	pid_t parent;

	if (pipe(fd) == -1)
		return (perror("Pipe:"));
	//fork first child
	// # fork() splits the process in two sub-processes -> parallel, simultaneous, happen at the same time
	// # it returns 0 for the child process, a non-zero for the parent process, -1 in case of error
	parent = fork();//create child process that is a clone of the parent
	if (parent == -1)
		return(perror("Error in the first process"));
	else if (parent == 0)//if parent == 0, its child process
		first_process(infile, argv, envp, fd);
	else
	{
		waitpid(parent, NULL, 0);//waiting until the first child is finished. while they finish their tasks
		second_process(outfile, argv, envp, fd);
	}
	return ;
	
}
//argv = cmd
 //each cmd needs a stdin (input) and returns an output (to stdout)

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


void first_process(int infile, char **argv, char **envp, int *end)
{
	dup2(end[1], STDOUT_FILENO);//and end[1] to be our stdout (we write to end[1] the output of cmd1)
	dup2(infile, STDIN_FILENO);//For the child process, we want infile to be our stdin (as input), 
	close(end[0]);
	exec(envp, argv[2]);
}
//argv = cmd
void second_process(int outfile, char **argv, char **envp, int *end)
{
	dup2(end[0],STDIN_FILENO);//In the parent process, we want end[0] to be our stdin (end[0] reads from end[1] the output of cmd1)
	dup2(outfile, STDOUT_FILENO);//and the outfile to be our stdout(we write to it the output of cmd1)
	close(end[1]);
	exec(envp, argv[3]);
}
//ac = argc
int main(int ac, char **argv, char **envp)
{
	int infile;
	int outfile;
	
	if (ac == 5)
	{
		infile = open (argv[1], O_RDONLY, 0777);
		outfile = open (argv[4], O_CREAT, O_RDWR, O_TRUNC, 0644);
		if (infile < 0 | outfile < 0)
		{
			perror("failed to open the file");
			return (EXIT_FAILURE);
		}
		pipex(infile, outfile, argv, envp);
	}
	else
	{
		if (ac < 5)
		{
			write(1, "Not enough arguments!",21);
		}
		else
			write(1, "More than enough arguments!",27);
	}
	return(1);//exit_failure
}