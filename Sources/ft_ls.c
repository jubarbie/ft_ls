/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 16:46:33 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/15 16:23:38 by jubarbie         ###   ########.fr       */
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

static void	to_display(char *dir_name, char opt)
{
	t_stat	*buf;

	buf = malloc(sizeof(t_stat));
	stat(dir_name, buf);
	if (opt & (1 << 2))
	{
		if (buf->st_mode & S_IFDIR)
			ft_putchar('d');
		ft_putstr("---------  ");
		ft_putnbr(buf->st_nlink);
		ft_putstr(" ");
		ft_putnbr(buf->st_uid);
		ft_putstr("  ");
		ft_putnbr(buf->st_gid);
		ft_putstr("  ");
		ft_putnbr(buf->st_size);
		ft_putstr("  ");
		ft_putstr(ctime(&buf->st_mtime));
	}
	else
	{
		ft_putstr(dir_name);
		ft_putchar('\n');
	}
	free(buf);
}

static void	print_lst(t_list *elem, char opt)
{
	if (elem)
	{
		if ( !(opt & (1 << 3)) && ((opt & (1 << 1)) ||
		(!(opt & (1 << 1)) && ft_strncmp(elem->content, ".", 1))))
			to_display(elem->content, opt);
		print_lst(elem->next, opt);
		if ((opt & (1 << 3)) && ((opt & (1 << 1)) ||
		(!(opt & (1 << 1)) && ft_strncmp(elem->content, ".", 1))))
			to_display(elem->content, opt);
	}
}

static void	lst_insert_sort_time(t_list **first, char *dir_name, int len)
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

static void	lst_insert_sort_alpha(t_list **first, char *dir_name, int len, t_param *param)
{
	t_list	*elem;
	t_list	*new;

	new = ft_lstnew(dir_name, len);
	update_param(dir_name, param);
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

void			list_dir(char *dir_name, t_param *param)
{
	DIR				*dir;
	struct dirent	*file;
	t_list			*first;

	if (!(dir = opendir(dir_name)))
		perror(dir_name);
	else
	{
		first = NULL;
		while ((file = readdir(dir)))
		{
			if (OPT & (1 << 4))
				lst_insert_sort_time(&first, file->d_name, file->d_namlen + 1);
			else
				lst_insert_sort_alpha(&first, file->d_name, file->d_namlen + 1, param);
		}
		print_lst(first, OPT);
		closedir(dir);
	}
}

void		ft_ls(int ac, char **av, t_param *param)
{
	if (ac > 0)
	{
		if (!(OPT & (1 << 3)))
		{
			ft_putstr(*(av + 1));
			ft_putstr(":\n");
			list_dir(*(av + 1), param);
			if (ac != 1)
				ft_putchar('\n');
		}
		ft_ls(--ac, ++av, param);
		if (OPT & (1 << 3))
		{
			ft_putstr(*av);
			ft_putstr(":\n");
			list_dir(*av, param);
			if (ac == 0)
				ft_putchar('\n');
		}
	}
}
