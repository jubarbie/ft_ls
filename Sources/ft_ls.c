/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 16:46:33 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/26 11:13:55 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include "libft.h"
#include "ft_ls.h"

static void	treat_list(t_list *first, t_param *param)
{
	t_list		*elem;
	t_dirinfos	*infos;

	elem = first;
	while (elem)
	{
		infos = elem->content;
		if (S_ISDIR(D_STAT->st_mode) && ft_strcmp(D_NAME, "..") &&
				ft_strncmp(D_NAME, ".", 1))
			ft_ls(1, &(D_PATH), param);
		elem = elem->next;
	}
}

void		ft_ls(int ac, char **av, t_param *param)
{
	t_list		*first;

	if (!R)
		first = list_dir(*av, param);
	if (ac > 1)
		ft_ls(--ac, av + 1, param);
	if (R)
		first = list_dir(*av, param);
	if (RR)
		treat_list(first, param);
	if (first)
		ft_lstdel(&first, &free_dirinfos);
}
