/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 23:04:48 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/18 20:20:07 by jubarbie         ###   ########.fr       */
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

static void	to_display(t_dirinfos *infos, t_param *param, int iter)
{
	char	*str;
	char	*pstr;
	int		len;
	char	*link;

	if (!(str = ft_strnew(31 + L_SZ + L_LK + L_US + L_GR)) ||
			!(link = ft_strnew(1024)))
		exit(EXIT_FAILURE);
	pstr = str;
	if (L)
	{
		if (!iter)
			put_total(param);
		get_mode(pstr, D_STAT, infos);
		get_infos(pstr, D_STAT, param);
		ft_putstr(str);
		ft_putchar(' ');
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
