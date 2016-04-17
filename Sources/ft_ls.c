/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 16:46:33 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/17 16:40:15 by jubarbie         ###   ########.fr       */
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

static void		lst_insert_sort_time(t_list **first, char *dir_name, int len)
{
	t_list	*elem;
	t_list	*new;
	t_stat	*b_elem;
	t_stat	*b_new;

	new = ft_lstnew(dir_name, len);
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

static void		lst_insert_sort_alpha(t_list **first, char *dir_name, int len,
				t_param *param)
{
	t_list	*elem;
	t_list	*new;
	char	*dir;

	new = ft_lstnew(dir_name, len);
	dir = ft_strjoin(C_DIR, dir_name);
	if (ft_strcmp(dir_name, ".") && ft_strcmp(dir_name, ".."))
		update_param(dir, param);
	if (!*first)
		*first = new;
	else
	{
		if (ft_strcmp((*first)->content, dir_name) >= 0)
		{
			new->next = *first;
			*first = new;
		}
		else
		{
			elem = *first;
			while (elem->next && (ft_strcmp(elem->next->content, dir_name) < 0))
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
				lst_insert_sort_time(&first, file->d_name, file->d_namlen + 1);
			else if (A || (!A && file->d_name[0] != '.'))
				lst_insert_sort_alpha(&first, file->d_name, file->d_namlen + 1,
										param);
		}
		print_lst(first, param);
		closedir(dir);
		return (first);
	}
	return (0);
}

void			ft_ls(int ac, char **av, t_param *param)
{
	t_list	*first;
	char	*curent;
	t_stat	*ps;

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
		while (first)
		{
			ps = malloc(sizeof(t_stat));
			curent = ft_strjoin(*av, "/");
			curent = ft_strjoin(curent, first->content);
			stat(curent, ps);
			if (S_ISDIR(ps->st_mode) && ft_strcmp(first->content, ".") &&
		ft_strcmp(first->content, "..") && ft_strncmp(first->content, ".", 1))
			{
				if (AC <= 1)
					print_folder_name(curent, param);
				ft_ls(1, &curent, param);
			}
			free(curent);
			free(ps);
			first = first->next;
		}
}
