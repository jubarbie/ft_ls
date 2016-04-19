/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 17:50:08 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/19 16:30:58 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <time.h>
#include <stdio.h>
#include <grp.h>
#include <pwd.h>
#include "libft.h"
#include "ft_ls.h"

static void	get_rights(char *str, t_stat *buf, t_dirinfos *infos)
{
	char	*lst;
	acl_t	acl;

	lst = ft_strnew(2);
	str[1] = (S_IRUSR & (buf->st_mode)) ? 'r' : '-';
	str[2] = (S_IWUSR & (buf->st_mode)) ? 'w' : '-';
	str[3] = (S_IXUSR & (buf->st_mode)) ? 'x' : '-';
	str[3] = (str[3] == 'x' && (S_ISUID & (buf->st_mode))) ? 's' : str[3];
	str[3] = (str[3] == '-' && (S_ISUID & (buf->st_mode))) ? 'S' : str[3];
	str[4] = (S_IRGRP & (buf->st_mode)) ? 'r' : '-';
	str[5] = (S_IWGRP & (buf->st_mode)) ? 'w' : '-';
	str[6] = (S_IXGRP & (buf->st_mode)) ? 'x' : '-';
	str[6] = (str[6] == 'x' && (S_ISGID & (buf->st_mode))) ? 's' : str[6];
	str[6] = (str[6] == '-' && (S_ISGID & (buf->st_mode))) ? 'S' : str[6];
	str[7] = (S_IROTH & (buf->st_mode)) ? 'r' : '-';
	str[8] = (S_IWOTH & (buf->st_mode)) ? 'w' : '-';
	str[9] = (S_IXOTH & (buf->st_mode)) ? 'x' : '-';
	str[9] = (str[9] != '-' && (buf->st_mode & S_ISVTX)) ? 't' : str[9];
	str[9] = (str[9] == '-' && (buf->st_mode & S_ISVTX)) ? 'T' : str[9];
	acl = acl_get_file(D_PATH, ACL_TYPE_EXTENDED);
	str[10] = (acl) ? '+' : ' ';
	listxattr(D_PATH, lst, 2, XATTR_NOFOLLOW);
	str[10] = (*lst) ? '@' : str[10];
	acl_free((void *)acl);
	free(lst);
}

void		get_time(char *str, t_stat *buf)
{
	time_t	now;
	time_t	six_months;

	*str = ' ';
	six_months = 31536000 / 2;
	if (time(&now) < buf->st_mtime || buf->st_mtime <= (now - six_months))
	{
		str = ft_strncpy(++str, &ctime(&(buf->st_mtime))[4], 6);
		str += 6;
		str = ft_strcpy(str, "  ");
		str = ft_strncpy(str + 2, &ctime(&(buf->st_mtime))[20], 4);
	}
	else
		str = ft_strncpy(++str, &ctime(&(buf->st_mtime))[4], 12);
}

void		get_infos(char *str, t_stat *buf, t_param *param)
{
	int	i;

	i = -1;
	while (++i <= L_LK - ft_nbrlen(buf->st_nlink))
		str[11 + i] = ' ';
	str = ft_strcpy(&str[11 + i], ft_itoa(buf->st_nlink));
	str += ft_nbrlen(buf->st_nlink);
	*str = ' ';
	i = -1;
	str = ft_strcpy(++str, getpwuid(buf->st_uid)->pw_name);
	str += ft_strlen(getpwuid(buf->st_uid)->pw_name);
	while (++i <= L_US - (int)ft_strlen(getpwuid(buf->st_uid)->pw_name) + 1)
		*(str++) = ' ';
	i = -1;
	str = ft_strcpy(str, getgrgid(buf->st_gid)->gr_name);
	str += ft_strlen(getgrgid(buf->st_gid)->gr_name);
	while (++i <= L_GR - (int)ft_strlen(getgrgid(buf->st_gid)->gr_name))
		*(str++) = ' ';
	i = -1;
	while (++i <= L_SZ - ft_nbrlen(buf->st_size))
		*(str++) = ' ';
	str = ft_strcpy(str, ft_itoa(buf->st_size));
	str += ft_nbrlen(buf->st_size);
	get_time(str, buf);
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

void		put_total(t_param *param)
{
	ft_putstr("total ");
	ft_putnbr(BLOCK);
	ft_putchar('\n');
}
