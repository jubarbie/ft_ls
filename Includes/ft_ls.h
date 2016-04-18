/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 15:34:00 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/18 10:40:39 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define OPT_REF "Ralrt"
# define OPT param->opt
# define RR (OPT & (1 << 0))
# define A (OPT & (1 << 1))
# define L (OPT & (1 << 2))
# define R (OPT & (1 << 3))
# define T (OPT & (1 << 4))
# define L_SZ param->len_size
# define L_LK param->len_link
# define L_US param->len_usr
# define L_GR param->len_gr
# define C_DIR param->c_dir
# define D_NAME infos->dir_name
# define D_PATH infos->path
# define D_STAT infos->s
# define AC param->ac

typedef struct stat	t_stat;
typedef struct	s_param
{
	char	opt;
	int		len_size;
	int		len_link;
	int		len_usr;
	int		len_gr;
	char	*c_dir;
	char	ac;
}				t_param;
typedef struct	s_dirinfos
{
	char	*path;
	char	*dir_name;
	t_stat	*s;
}				t_dirinfos;

int			ft_nblen(long long int nb);

t_param		*init_param(char opt);
void    	print_param(t_param *param);
void    	update_param(char *dir_name, t_param *param);

t_dirinfos	*new_dirinfos(char *dir_name, t_param *param);
void		free_dirinfos(void *infos, unsigned long t_size);

void		print_lst(t_list *first, t_param *param);
void		print_folder_name(char *str, t_param *param);
void		ft_ls(int ac, char **av, t_param *param);
void		error_opt(char opt);

#endif
