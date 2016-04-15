/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 11:54:04 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/15 16:00:20 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include "libft.h"
#include "ft_ls.h"

/*static void		print_bits(char c)
{
	int		i;

	i = 8;
	while (--i >= 0)
		if (c & (1 << i))
			ft_putchar('1');
		else
			ft_putchar('0');
	ft_putchar('\n');
}*/

static int		in_opt(char c)
{
	int		i;

	i = -1;
	while (OPT_REF[++i])
		if (c == OPT_REF[i])
			return (i);
	return (-1);
}

static int		get_options(int ac, char **av, char *opt)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	*opt = 0;
	while (++i < ac && av[i][0] == '-' && av[i][1])
	{
		j = 0;
		while (av[i][++j])
			if ((k = in_opt(av[i][j])) != -1)
				*opt |= (1 << k);
			else 
				error_opt(av[i][j]);
	}
	return (i);
}

int				main(int ac, char **av)
{
	int		i;
	char	opt;
	t_param	*param;

	i = get_options(ac, av, &opt);
	param = init_param(opt);
	if (ac - i == 0)
		list_dir(".", param);
	else
		ft_ls(ac - i, &av[i - 1], param);
	print_param(param);
	free(param);
	return (0);
}
