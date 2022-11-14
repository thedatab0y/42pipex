/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gp_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:19:24 by busmanov          #+#    #+#             */
/*   Updated: 2022/11/13 13:21:11 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

void	aff_error(char *cmd)
{
	write(2, "command not found: ", ft_strlen("command not found: "));
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

char	*gpathcmd(char *p, char *cmd)
{
	char	*path;

	path = ft_strjoin(p, cmd);
	free(p);
	return (path);
}

char	*getpath(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	exec(char **envp, char *argv)
{
	char	**pathenv;
	char	*rightpath;
	char	**cmd;
	int		i;
	int		count;

	pathenv = ft_split(getpath(envp), ':');
	cmd = ft_split(argv, ' ');
	i = 0;
	count = 0;
	while (pathenv[i])
	{
		rightpath = gpathcmd(ft_strjoin(pathenv[i], "/"), cmd[0]);
		if (access(rightpath, R_OK) == 0)
		{
			if (execve(rightpath, cmd, envp) == -1)
				perror("Execve : ");
		}
		else
			count++;
		free(rightpath);
		i++;
	}
	if (count == i)
		aff_error(cmd[0]);
}
