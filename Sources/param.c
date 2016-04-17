/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 15:59:35 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/17 15:27:28 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include "libft.h"
#include "ft_ls.h"

void	print_param(t_param *param)
{
	ft_putstr("size: ");
	ft_putnbr(L_SZ);
	ft_putchar('\n');
	ft_putstr("link: ");
	ft_putnbr(L_LK);
	ft_putchar('\n');
	ft_putstr("user: ");
	ft_putnbr(L_US);
	ft_putchar('\n');
	ft_putstr("group: ");
	ft_putnbr(L_GR);
	ft_putchar('\n');
}

int		ft_nblen(long long int nb)
{
	int i;

	if (nb == 0)
		return (1);
	i = 0;
	while (nb && ++i)
		nb /= 10;
	return (i);
}

void	update_param(char *dir_name, t_param *param)
{
	t_stat	ps;
	int		l_size;
	int		l_link;
	int		l_usr;
	int		l_gr;

	stat(dir_name, &ps);
	l_size = ft_nblen(ps.st_size);
	l_link = ft_nblen(ps.st_nlink);
	/*printf("size::%lld\n", ps.st_size);
	printf("link::%d\n", ps.st_nlink);
	printf("uid:%d\n", ps.st_uid);
	printf("grid:%d\n", ps.st_gid);
	printf("%s\n", getpwuid(ps.st_uid)->pw_name);
	printf("%s\n", getgrgid(ps.st_gid)->gr_name);*/
	l_usr = ft_strlen(getpwuid(ps.st_uid)->pw_name);
	l_gr = ft_strlen(getgrgid(ps.st_gid)->gr_name);
	L_SZ = (l_size > L_SZ) ? l_size : L_SZ;
	L_LK = (l_link > L_LK) ? l_link : L_LK;
	L_US = (l_usr > L_US) ? l_usr : L_US;
	L_GR = (l_gr > L_GR) ? l_gr : L_GR;
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
	return (param);
}
