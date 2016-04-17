/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 23:04:48 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/17 16:55:13 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <grp.h>
#include <pwd.h>
#include "libft.h"
#include "ft_ls.h"

static void	get_infos(char *str, t_stat *buf, t_param *param)
{
	int	i;
	
	i = -1;
	while (++i <= L_LK - ft_nblen(buf->st_nlink))
		str[11 + i] = ' ';
	str = ft_strcpy(&str[11 + i], ft_itoa(buf->st_nlink));
	str += ft_nblen(buf->st_nlink);
	*str = ' ';
	i = -1;
	while (++i < L_US - (int)ft_strlen(getpwuid(buf->st_uid)->pw_name))
		*(++str) = ' ';
	str = ft_strcpy(++str, getpwuid(buf->st_uid)->pw_name);
	str += ft_strlen(getpwuid(buf->st_uid)->pw_name);
	*str = ' ';
	i = -1;
	while (++i <= L_GR - (int)ft_strlen(getgrgid(buf->st_gid)->gr_name))
		*(++str) = ' ';
	str = ft_strcpy(++str, getgrgid(buf->st_gid)->gr_name);
	str += ft_strlen(getgrgid(buf->st_gid)->gr_name);
	*str = ' ';
	i = -1;
	while (++i <= L_SZ - ft_nblen(buf->st_size))
		*(++str) = ' ';
	str = ft_strcpy(++str, ft_itoa(buf->st_size));
	str += ft_nblen(buf->st_size);
	*str = ' ';
	str = ft_strncpy(++str, &ctime(&(buf->st_mtime))[4], 12);
	*(str + 12) = ' ';
}

static void	get_mode(char *str, t_stat *buf)
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
	str[1] = (S_IRUSR & (buf->st_mode)) ? 'r' : '-';
	str[2] = (S_IWUSR & (buf->st_mode)) ? 'w' : '-';
	str[3] = (S_IXUSR & (buf->st_mode)) ? 'x' : '-';
	str[4] = (S_IRGRP & (buf->st_mode)) ? 'r' : '-';
	str[5] = (S_IWGRP & (buf->st_mode)) ? 'w' : '-';
	str[6] = (S_IXGRP & (buf->st_mode)) ? 'x' : '-';
	str[7] = (S_IROTH & (buf->st_mode)) ? 'r' : '-';
	str[8] = (S_IWOTH & (buf->st_mode)) ? 'w' : '-';
	str[9] = (S_IXOTH & (buf->st_mode)) ? 'x' : '-';
	str[10] = ' ';
}

static void	to_display(char *dir_name, t_param *param)
{
	t_stat	buf;
	char	*str;
	char	*pstr;
	char	*dir;

	str = ft_strnew(31 + L_SZ + L_LK + L_US + L_GR);
	pstr = str;
	dir = ft_strjoin(C_DIR, dir_name);
	stat(dir, &buf);
	if (L)
	{
		get_mode(pstr, &buf);
		get_infos(pstr, &buf, param);
		ft_putstr(str);
		ft_putstr(dir_name);
		ft_putchar('\n');
		/*ft_putnbr(buf.st_nlink);
		ft_putstr(" ");
		ft_putnbr(buf.st_uid);
		ft_putstr("  ");
		ft_putnbr(buf.st_gid);
		ft_putstr("  ");
		ft_putnbr(buf.st_size);
		ft_putstr("  ");
		ft_putstr(ctime(&(buf.st_mtime)));*/
	}
	else
	{
		ft_putstr(dir_name);
		ft_putchar('\n');
	}
	free(str);
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

void		print_folder_name(char *str, t_param *param)
{
	static char	first = 1;

	if (AC <= 1 ||  (AC > 1 && first == 0))
	ft_putchar('\n');
	ft_putstr(str);
	ft_putstr(":\n");
	first = 0;
}
