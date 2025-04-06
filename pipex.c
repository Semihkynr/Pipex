/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:44:38 by skaynar           #+#    #+#             */
/*   Updated: 2025/04/06 19:19:26 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_execute(char *cmd, char **ep)
{
	char	**commands;
	char	*path;

	commands = ft_split(cmd, ' ');
	if (!commands || !commands[0])
	{
		ft_free(commands);
		ft_error(1);
	}
	path = ft_get_cmd(commands[0], ep);
	if (execve(path, commands, ep) == -1)
	{
		ft_putstr_fd(commands[0], 2);
		ft_putendl_fd(": command not found", 2);
		ft_free(commands);
		exit(0);
	}
}

static void	ft_child(char **av, int *fd, char **ep)
{
	int	file_d;

	file_d = ft_open(av[1], 0);
	dup2(file_d, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	ft_execute(av[2], ep);
}

static void	ft_parent(char **av, int *fd, char **ep)
{
	int	file_d;

	file_d = ft_open(av[4], 1);
	dup2(file_d, 1);
	dup2(fd[0], 0);
	close(fd[1]);
	ft_execute(av[3], ep);
}

void	ft_error(int nbr)
{
	if (nbr == 1)
		ft_putstr_fd("USAGE: ./pipex infile '/cmd1' '/cmd2' outfile\n", 2);
	exit(0);
}

int	main(int ac, char **av, char **ep)
{
	int		fd[2];
	pid_t	pid;

	if (ac != 5)
		ft_error(1);
	if (pipe(fd) < 0)
		exit(-1);
	pid = fork();
	if (pid < 0)
		exit(-1);
	if (pid == 0)
		ft_child(av, fd, ep);
	ft_parent(av, fd, ep);
	return (0);
}
