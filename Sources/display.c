/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 23:04:48 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/16 23:10:00 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include "libft.h"
#include "ft_ls.h"

static void	to_display(char *dir_name, t_param *param)
{
	t_stat	*buf;

	buf = malloc(sizeof(t_stat));
	stat(dir_name, buf);
	if (L)
	{
		if (buf->st_mode & S_IFDIR)
			ft_putchar('d');
		ft_putstr("---------  ");
		ft_putnbr(buf->st_nlink);
		ft_putstr(" ");
		ft_putnbr(buf->st_uid);
		ft_putstr("  ");
		ft_putnbr(buf->st_gid);
		ft_putstr("  ");
		ft_putnbr(buf->st_size);
		ft_putstr("  ");
		ft_putstr(ctime(&buf->st_mtime));
	}
	else
	{
		ft_putstr(dir_name);
		ft_putchar('\n');
	}
	free(buf);
}

void		print_lst(t_list *elem, t_param *param)
{
	if (elem)
	{
		if (!R)
			to_display(elem->content, param);
		print_lst(elem->next, param);
		if (R)
			to_display(elem->content, param);
	}
}
