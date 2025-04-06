/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:45:42 by skaynar           #+#    #+#             */
/*   Updated: 2025/04/06 19:59:39 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_access(char *exec, char **opt, char **path)
{
	if (!access(exec, F_OK | X_OK))
	{
		ft_free(opt);
		ft_free(path);
		return (1);
	}
	return (0);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	ft_open(char *file, int val)
{
	int	rtn;

	if (val)
		rtn = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		rtn = open(file, O_RDONLY);
	if (rtn < 0)
	{
		ft_putstr_fd("bash: ", 2);
		perror(file);
		exit(1);
	}
	return (rtn);
}

char	*ft_get_path(char **ep)
{
	int		i;
	char	*path;

	path = NULL;
	i = 0;
	while (ep[i])
	{
		if (!ft_strncmp(ep[i], "PATH=", 5))
		{
			path = ep[i] + 5;
			break ;
		}
		i++;
	}
	if (!path)
		exit(1);
	return (path);
}

char	*ft_get_cmd(char *cmd, char **ep)
{
	char	**path;
	char	*part;
	char	**opt;
	char	*exec;
	int		i;

	i = -1;
	path = ft_split(ft_get_path(ep), ':');
	opt = ft_split(cmd, ' ');
	if (!opt || !path)
		ft_error(1);
	while (path[++i])
	{
		part = ft_strjoin(path[i], "/");
		exec = ft_strjoin(part, opt[0]);
		free(part);
		if (ft_access(exec, opt, path))
			return (exec);
		free(exec);
	}
	ft_free(path);
	ft_free(opt);
	return (cmd);
}
