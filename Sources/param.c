/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 15:59:35 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/18 20:24:11 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include "libft.h"
#include "ft_ls.h"

void	reinit_param(t_param *param)
{
	L_SZ = 0;
	L_LK = 0;
	L_US = 0;
	L_GR = 0;
	BLOCK = 0;
}

void	update_param(char *dir_name, t_param *param)
{
	t_stat			ps;
	int				l_tmp;
	struct passwd	*uid;
	struct group	*gid;

	lstat(dir_name, &ps);
	l_tmp = ft_nbrlen(ps.st_size);
	L_SZ = (l_tmp > L_SZ) ? l_tmp : L_SZ;
	l_tmp = ft_nbrlen(ps.st_nlink);
	L_LK = (l_tmp > L_LK) ? l_tmp : L_LK;
	l_tmp = 0;
	if ((uid = getpwuid(ps.st_uid)))
		l_tmp = (uid->pw_name) ? ft_strlen(uid->pw_name) : 0;
	L_US = (l_tmp > L_US) ? l_tmp : L_US;
	l_tmp = 0;
	if ((gid = getgrgid(ps.st_gid)))
		l_tmp = (gid->gr_name) ? ft_strlen(gid->gr_name) : 0;
	L_GR = (l_tmp > L_GR) ? l_tmp : L_GR;
	BLOCK += ps.st_blocks;
}

void	free_param(t_param *param)
{
	free(param);
}

t_param	*init_param(char opt)
{
	t_param	*param;

	if (!(param = malloc(sizeof(t_param))))
		exit(EXIT_FAILURE);
	OPT = opt;
	L_SZ = 0;
	L_LK = 0;
	L_US = 0;
	L_GR = 0;
	AC = 0;
	BLOCK = 0;
	ITER = 0;
	C_DIR = ft_strnew(0);
	return (param);
}
