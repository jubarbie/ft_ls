/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 18:05:13 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/27 16:34:55 by jubarbie         ###   ########.fr       */
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

static void		lst_insert_sort(t_list **first, t_list *new,
					int (*cmp)(t_dirinfos*, t_dirinfos*))
{
	t_list		*elem;

	if ((*cmp)((*first)->content, new->content) >= 0)
	{
		new->next = *first;
		*first = new;
	}
	else
	{
		elem = *first;
		while (elem->next &&
				((*cmp)(elem->next->content, new->content) < 0))
			elem = elem->next;
		new->next = elem->next;
		elem->next = new;
	}
}

static void		lst_insert(t_list **first, char *dir_name, t_param *param)
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
			if (T && U)
				lst_insert_sort(first, new, &ft_atimecmp);
			else if (T)
				lst_insert_sort(first, new, &ft_mtimecmp);
			else
				lst_insert_sort(first, new, &ft_namecmp);
		}
	}
}

static t_list	*create_list(DIR *dir, char *dir_name,
							t_list *first, t_param *param)
{
	struct dirent	*file;

	print_folder_name(dir_name, param);
	reinit_param(dir_name, param);
	while ((file = readdir(dir)))
		if (A || (!A && AA) || (!A && file->d_name[0] != '.'))
			if (!AA || (AA && !A && (ft_strcmp(file->d_name, "..") &&
								ft_strcmp(file->d_name, "."))) || (AA && A))
				lst_insert(&first, file->d_name, param);
	print_lst(first, param, 0);
	closedir(dir);
	return (first);
}

t_list			*list_dir(char *dir_name, t_param *param)
{
	DIR				*dir;
	t_list			*first;
	t_stat			ps;
	t_dirinfos		*infos;

	first = NULL;
	if (lstat(dir_name, &ps) != -1 && S_ISDIR(ps.st_mode))
	{
		if (!(dir = opendir(dir_name)))
			error_open(dir_name, param);
		else
			return (create_list(dir, dir_name, first, param));
	}
	else
	{
		infos = new_dirinfos(dir_name, param);
		if (infos)
		{
			to_display(infos, param, 1);
			free_dirinfos(infos, sizeof(*infos));
		}
	}
	return (0);
}
