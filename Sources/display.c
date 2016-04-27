/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 23:04:48 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/27 18:09:49 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/xattr.h>
#include <time.h>
#include <stdio.h>
#include <grp.h>
#include <pwd.h>
#include "libft.h"
#include "ft_ls.h"

void		put_total(t_param *param)
{
	ft_putstr("total ");
	ft_putnbr(BLOCK);
	ft_putchar('\n');
}

void		get_mode(char *str, t_stat *buf, t_dirinfos *infos)
{
	if (S_ISBLK(buf->st_mode))
		str[0] = 'b';
	else if (S_ISCHR(buf->st_mode))
		str[0] = 'c';
	else if (S_ISDIR(buf->st_mode))
		str[0] = 'd';
	else if (S_ISLNK(buf->st_mode))
		str[0] = 'l';
	else if (S_ISSOCK(buf->st_mode))
		str[0] = 's';
	else if (S_ISFIFO(buf->st_mode))
		str[0] = 'p';
	else if (S_ISREG(buf->st_mode))
		str[0] = '-';
	get_rights(str, buf, infos);
}

void		to_display(t_dirinfos *infos, t_param *param, int iter)
{
	char	*str;
	int		len;
	char	*link;

	if (!(str = ft_strnew(31 + L_SZ + L_LK + L_US + L_GR)) ||
			!(link = ft_strnew(1024)))
		exit(EXIT_FAILURE);
	if (L || G || O)
	{
		if (!iter)
			put_total(param);
		str = ft_memset(str, ' ', 31 + L_SZ + L_LK + L_US + L_GR);
		get_mode(str, D_STAT, infos);
		get_infos(str, D_STAT, param, infos);
		ft_putstr(str);
	}
	ft_putstr(D_NAME);
	link = ft_strcpy(link, " -> ");
	if (L && (len = readlink(D_PATH, &link[4], 1024)) != -1)
		write(1, link, len + 4);
	ft_putchar('\n');
	free(str);
	free(link);
}

void		print_lst(t_list *elem, t_param *param, int iter)
{
	if (elem)
	{
		if (!R)
			to_display(elem->content, param, iter);
		print_lst(elem->next, param, ++iter);
		if (R)
			to_display(elem->content, param, iter);
	}
}

void		print_folder_name(char *str, t_param *param)
{
	static char	f = 1;

	if ((!RR && AC > 1) || (RR && f == 0))
	{
		if (AC <= 1 || (AC > 1 && f == 0))
			ft_putchar('\n');
		ft_putstr(str);
		ft_putstr(":\n");
	}
	f = 0;
}
