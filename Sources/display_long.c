/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 17:50:08 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/26 16:46:37 by jubarbie         ###   ########.fr       */
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
	acl_t	acl;
	int		i;

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
	i = listxattr(D_PATH, NULL, 1, XATTR_NOFOLLOW);
	str[10] = (acl && !buf->st_rdev) ? '+' : ' ';
	str[10] = (i && !buf->st_rdev) ? '@' : str[10];
	acl_free((void *)acl);
}

void		get_time(char *str, t_stat *buf, t_param *param)
{
	time_t	now;
	time_t	six_months;
	time_t	btime;

	six_months = 31536000 / 2;
	btime = (L && U) ? buf->st_atime : buf->st_mtime;
	if (time(&now) < btime || btime <= (now - six_months))
	{
		str = ft_strncpy(++str, &ctime(&(btime))[4], 6);
		str = ft_strncpy(str + 8, &ctime(&(btime))[20], 4);
	}
	else
		str = ft_strncpy(++str, &ctime(&(btime))[4], 12);
}

char		*get_mami(char *str, t_stat *buf, t_param *param)
{
	char	*ma;
	char	*mi;
	int		l_ma;
	int		l_mi;

	ma = ft_itoa(major(buf->st_rdev));
	mi = ft_itoa(minor(buf->st_rdev));
	l_ma = ft_strlen(ma);
	l_mi = ft_strlen(mi);
	str += 2 + L_MA - l_ma;
	str = ft_strcpy(str, ma);
	str += l_ma;
	*str = ',';
	str += 1 + L_MI - l_mi;
	str = ft_strcpy(++str, mi);
	str += l_mi;
	*str = ' ';
	return (str);
}

void		get_infos(char *str, t_stat *buf, t_param *param, t_dirinfos *infos)
{
	str += 12;
	str += L_LK - ft_nbrlen(buf->st_nlink);
	str = ft_strcpy(str, ft_itoa(buf->st_nlink));
	str += ft_nbrlen(buf->st_nlink);
	*str = ' ';
	str = ft_strcpy(++str, getpwuid(buf->st_uid)->pw_name);
	str += ft_strlen(getpwuid(buf->st_uid)->pw_name);
	*str = ' ';
	str += L_US - ft_strlen(getpwuid(buf->st_uid)->pw_name) + 1;
	str = ft_strcpy(++str, getgrgid(buf->st_gid)->gr_name);
	str += ft_strlen(getgrgid(buf->st_gid)->gr_name);
	*str = ' ';
	str += L_GR - ft_strlen(getgrgid(buf->st_gid)->gr_name) + 1;
	if (!ft_strstr(D_PATH, "/dev/"))
	{
		str += L_SZ - ft_nbrlen(buf->st_size);
		str = ft_strcpy(++str, ft_itoa(buf->st_size));
		str += ft_nbrlen(buf->st_size);
		*str = ' ';
	}
	else
		str = get_mami(str, buf, param);
	get_time(str, buf, param);
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
