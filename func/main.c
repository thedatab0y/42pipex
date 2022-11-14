/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:19:20 by busmanov          #+#    #+#             */
/*   Updated: 2022/11/13 13:10:25 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int f1, char **argv, char **envp, int *end)
{
	dup2(end[1], STDOUT_FILENO);
	dup2(f1, STDIN_FILENO);
	close(end[0]);
	execute(envp, argv[2]);
}

void	parent_process(int f2, char **argv, char **envp, int *end)
{
	dup2(end[0], STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	close(end[1]);
	execute(envp, argv[3]);
}

void	pipex(int file1, int file2, char **argv, char **envp)
{
	int		end[2];
	pid_t	parent;

	if (pipe(end) == -1)
		return (perror("Pipe : "));
	parent = fork();
	if (parent < 0)
		return (perror("Fork: "));
	else if (parent == 0)
		child_process(file1, argv, envp, end);
	else
	{
		waitpid(parent, NULL, 0);
		parent_process(file2, argv, envp, end);
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	int	file1;
	int	file2;

	if (argc == 5)
	{
		file1 = open(argv[1], O_RDONLY, 0777);
		file2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (file2 == -1 || file1 == -1)
		{
			perror("file failed");
			exit (EXIT_FAILURE);
		}
		pipex(file1, file2, argv, envp);
	}
	else
	{
		if (argc < 5)
			write(1, "Missing arguments\n", 18);
		else
			write(1, "Too much arguments\n", 19);
	}
	return (1);
}