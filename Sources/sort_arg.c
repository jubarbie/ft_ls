/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 17:17:17 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/21 19:55:17 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include "libft.h"
#include "ft_ls.h"

static int		nb_files(int ac, char **av)
{
	int		i;
	int		ret;
	t_stat	ps;

	i = -1;
	ret = ac;
	while (++i < ac)
	{
		lstat(av[i], &ps);
		if (S_ISDIR(ps.st_mode))
			ret--;
	}
	return (ret);
}

static void		sort_attr(int ac, char **av,
		int (*cmp)(t_dirinfos *, t_dirinfos *), t_param *param)
{
	int			i;
	int			j;
	char		*tmp;
	t_dirinfos	infos1;
	t_dirinfos	infos2;

	i = -1;
	while (++i < ac - 1)
	{
		j = i;
		infos1 = *new_dirinfos(av[i], param);
		while (++j < ac)
		{
			infos2 = *new_dirinfos(av[j], param);
			if ((*cmp)(&infos1, &infos2) > 0)
			{
				tmp = av[i];
				av[i] = av[j];
				av[j] = tmp;
			}
		}
	}
}

static int		sort_tab(int ac, char **av, t_param *param)
{
	int		j;

	j = nb_files(ac, av);
	if (T && U)
	{
		sort_attr(j, av, &ft_atimecmp, param);
		sort_attr(ac - j, &av[j], &ft_atimecmp, param);
	}
	else if (T)
	{
		sort_attr(j, av, &ft_mtimecmp, param);
		sort_attr(ac - j, &av[j], &ft_mtimecmp, param);
	}
	else
	{
		sort_attr(j, av, &ft_namecmp, param);
		sort_attr(ac - j, &av[j], &ft_namecmp, param);
	}
	return (j);
}

int				sort_arg(int ac, char **av, t_param *param)
{
	int		i;
	int		j;
	char	*tmp;
	t_stat	ps;

	i = -1;
	while (++i < ac - 1)
	{
		lstat(av[i], &ps);
		if (S_ISDIR(ps.st_mode))
		{
			j = i;
			while (++j < ac)
			{
				lstat(av[j], &ps);
				if (!S_ISDIR(ps.st_mode))
				{
					tmp = av[i];
					av[i] = av[j];
					av[j] = tmp;
				}
			}
		}
	}
	return (sort_tab(ac, av, param));
}
