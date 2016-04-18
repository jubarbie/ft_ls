/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirinfos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 09:09:56 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/18 10:41:37 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
		!(infos->s = malloc(sizeof(t_stat))))
		exit(EXIT_FAILURE);
	infos->path = ft_strjoin(C_DIR, dir_name);
	infos->dir_name = ft_strdup(dir_name);
	stat(infos->path, infos->s);
	update_param(infos->path, param);
	return (infos);
}
