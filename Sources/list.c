/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 18:05:13 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/19 19:12:56 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include "libft.h"
#include "ft_ls.h"

static void	sort_time(t_list **first, t_list *new)
{
	t_list		*elem;
	t_dirinfos	*infos;

	infos = new->content;
	if (((t_dirinfos *)(*first)->content)->s->st_mtimespec.tv_sec <
			D_STAT->st_mtimespec.tv_sec)
	{
		new->next = *first;
		*first = new;
	}
	else
	{
		elem = *first;
		while (elem->next &&
				((t_dirinfos *)elem->next->content)->s->st_mtimespec.tv_sec >
				D_STAT->st_mtimespec.tv_sec)
			elem = elem->next;
		new->next = elem->next;
		elem->next = new;
	}
}

static void	sort_alpha(t_list **first, t_list *new)
{
	t_list		*elem;

	if (ft_strcmp(((t_dirinfos *)(*first)->content)->dir_name,
				((t_dirinfos *)new->content)->dir_name) >= 0)
	{
		new->next = *first;
		*first = new;
	}
	else
	{
		elem = *first;
		while (elem->next &&
				(ft_strcmp(((t_dirinfos *)elem->next->content)->dir_name,
							((t_dirinfos *)new->content)->dir_name) < 0))
			elem = elem->next;
		new->next = elem->next;
		elem->next = new;
	}
}

static void	lst_insert_sort(t_list **first, char *dir_name, t_param *param)
{
	t_list		*new;
	t_dirinfos	*infos;

	if ((infos = new_dirinfos(dir_name, param)))
	{
		new = ft_lstnew(infos, sizeof(*infos));
		free(infos);
		if (!*first)
			*first = new;
		else
		{
			if (!T)
				sort_alpha(first, new);
			else
				sort_time(first, new);
		}
	}
}

t_list		*list_dir(char *dir_name, t_param *param)
{
	DIR				*dir;
	struct dirent	*file;
	t_list			*first;
	t_stat			ps;

	if (lstat(dir_name, &ps) != -1 && S_ISDIR(ps.st_mode))
	{	
	if (!(dir = opendir(dir_name)))
		error_open(dir_name, param);
	else
	{
		print_folder_name(dir_name, param);
		free(C_DIR);
		C_DIR = (ft_strcmp(dir_name, "/")) ? ft_strjoin(dir_name, "/") :
			ft_strjoin(dir_name, "");
		first = NULL;
		reinit_param(param);
		while ((file = readdir(dir)))
			if (A || (!A && file->d_name[0] != '.'))
				lst_insert_sort(&first, file->d_name, param);
		print_lst(first, param, 0);
		closedir(dir);
		ITER++;
		return (first);
	}
	}
	else
	{
		ft_putendl(dir_name);
	}
	return (0);
}
