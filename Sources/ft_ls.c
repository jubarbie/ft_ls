/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 16:46:33 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/18 10:44:13 by jubarbie         ###   ########.fr       */
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

static void		lst_insert_sort_time(t_list **first, char *dir_name)
{
	t_list	*elem;
	t_list	*new;
	t_stat	*b_elem;
	t_stat	*b_new;

	new = ft_lstnew(dir_name, 10);
	b_elem = malloc(sizeof(struct stat));
	b_new = malloc(sizeof(struct stat));
	stat(new->content, b_new);
	if (!*first)
		*first = new;
	else
	{
		stat((*first)->content, b_elem);
		if (b_new->st_mtimespec.tv_sec > b_elem->st_mtimespec.tv_sec)
		{
			new->next = *first;
			*first = new;
		}
		else
		{
			elem = (*first);
			while (elem->next &&
					b_new->st_mtimespec.tv_sec <= b_elem->st_mtimespec.tv_sec)
			{
				elem = elem->next;
				stat(elem->content, b_elem);
			}
			new->next = elem->next;
			elem->next = new;
		}
	}
	free(b_elem);
}

static void		lst_insert_sort_alpha(t_list **first, char *dir_name,
				t_param *param)
{
	t_list		*elem;
	t_list		*new;
	t_dirinfos	*infos;

	infos = new_dirinfos(dir_name, param);
	new = ft_lstnew(infos, sizeof(*infos));
	if (!*first)
		*first = new;
	else
	{
		if (ft_strcmp(((t_dirinfos *)(*first)->content)->dir_name, dir_name) >= 0)
		{
			new->next = *first;
			*first = new;
		}
		else
		{
			elem = *first;
			while (elem->next && (ft_strcmp(((t_dirinfos *)elem->next->content)->dir_name, dir_name) < 0))
				elem = elem->next;
			new->next = elem->next;
			elem->next = new;
		}
	}
}

static t_list	*list_dir(char *dir_name, t_param *param)
{
	DIR				*dir;
	struct dirent	*file;
	t_list			*first;

	if (!(dir = opendir(dir_name)))
	{
		ft_putstr("./ft_ls: ");
		perror(dir_name);
	}
	else
	{
		C_DIR = ft_strjoin(dir_name, "/");
		first = NULL;
		while ((file = readdir(dir)))
		{
			if (T && (A || (!A && ft_strncmp(file->d_name, ".", 1))))
				lst_insert_sort_time(&first, file->d_name);
			else if (A || (!A && file->d_name[0] != '.'))
				lst_insert_sort_alpha(&first, file->d_name, param);
		}
		print_lst(first, param);
		closedir(dir);
		return (first);
	}
	return (0);
}

void			ft_ls(int ac, char **av, t_param *param)
{
	t_list		*first;
	t_list		*elem;
	t_dirinfos	*infos;

	if (!R)
	{
		if (AC > 1)
			print_folder_name(*av, param);
		first = list_dir(*av, param);
	}
	if (ac > 1)
		ft_ls(--ac, av + 1, param);
	if (R)
	{
		if (AC > 1)
			print_folder_name(*av, param);
		first = list_dir(*av, param);
	}
	if (RR)
	{
		elem = first;
		while (elem)
		{
			infos = elem->content;
			if (S_ISDIR(D_STAT->st_mode) && ft_strcmp(D_NAME, ".") &&
				ft_strcmp(D_NAME, "..") && ft_strncmp(D_NAME, ".", 1))
			{
				if (AC <= 1)
					print_folder_name(D_PATH, param);
				ft_ls(1, &(D_PATH), param);
			}
			elem = elem->next;
		}
		ft_lstdel(&first, &free_dirinfos);
	}
}
