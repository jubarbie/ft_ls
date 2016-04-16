/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 15:59:35 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/16 22:57:49 by jubarbie         ###   ########.fr       */
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
	t_stat	*ps;
	int		len_size;
	int		len_link;
	int		len_usr;
	int		len_gr;

	if (!(ps = malloc(sizeof(t_stat))))
		exit(EXIT_FAILURE);
	stat(dir_name, ps);
	len_size = ft_nblen(ps->st_size);
	len_link = ft_nblen(ps->st_nlink);
	len_usr = ft_strlen(getpwuid(ps->st_uid)->pw_name);
	len_gr = ft_strlen(getgrgid(ps->st_gid)->gr_name);
	L_SZ = (len_size > L_SZ) ? len_size : L_SZ;
	L_LK = (len_link > L_LK) ? len_link : L_LK;
	L_US = (len_usr > L_US) ? len_usr : L_US;
	L_GR = (len_gr > L_GR) ? len_gr : L_GR;
	free(ps);
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
	return (param);
}
