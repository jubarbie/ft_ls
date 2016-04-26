/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirinfos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 09:09:56 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/26 12:40:56 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "libft.h"
#include "ft_ls.h"

void		free_dirinfos(void *infos, unsigned long size)
{
	if (infos)
	{
		free(((t_dirinfos *)infos)->path);
		free(((t_dirinfos *)infos)->dir_name);
		free(((t_dirinfos *)infos)->s);
		free(infos);
	}
	size--;
}

t_dirinfos	*new_dirinfos(char *dir_name, t_param *param)
{
	t_dirinfos	*infos;

	if (!(infos = malloc(sizeof(t_dirinfos))) ||
		!(D_STAT = malloc(sizeof(t_stat))))
		exit(EXIT_FAILURE);
	D_PATH = ft_strjoin(C_DIR, dir_name);
	D_NAME = ft_strdup(dir_name);
	if (lstat(D_PATH, D_STAT) == -1)
	{
		error_open(D_PATH, param);
		free_dirinfos(infos, sizeof(*infos));
		return (NULL);
	}
	else if (ft_strcmp(D_NAME, ".") && ft_strcmp(D_NAME, ".."))
	{
		update_param(infos->path, param);
		if (ft_strstr(D_PATH, "/dev/"))
			update_param_mima(infos->path, param);
	}
	return (infos);
}
