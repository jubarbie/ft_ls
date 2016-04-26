/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 15:34:00 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/26 16:48:35 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define OPT_REF "Ralrtu1"
# define OPT param->opt
# define RR (OPT & (1 << 0))
# define A (OPT & (1 << 1))
# define L (OPT & (1 << 2))
# define R (OPT & (1 << 3))
# define T (OPT & (1 << 4))
# define U (OPT & (1 << 5))
# define L_SZ param->len_size
# define L_LK param->len_link
# define L_US param->len_usr
# define L_GR param->len_gr
# define L_MA param->len_ma
# define L_MI param->len_mi
# define C_DIR param->c_dir
# define BLOCK param->block
# define ITER param->iter
# define D_NAME infos->dir_name
# define D_PATH infos->path
# define D_STAT infos->s
# define AC param->ac

typedef struct stat	t_stat;
typedef struct		s_param
{
	char			opt;
	int				len_size;
	int				len_ma;
	int				len_mi;
	int				len_link;
	int				len_usr;
	int				len_gr;
	char			*c_dir;
	char			ac;
	long long int	block;
	int				iter;
}					t_param;
typedef struct		s_dirinfos
{
	char	*path;
	char	*dir_name;
	t_stat	*s;
}					t_dirinfos;

void				ft_ls(int ac, char **av, t_param *param);

t_param				*init_param(char opt, int ac);
void				print_param(t_param *param);
void				update_param(char *dir_name, t_param *param);
void				update_param_mima(char *dir_name, t_param *param);
void				reinit_param(char *dir_name, t_param *param);
void				free_param(t_param *param);

t_dirinfos			*new_dirinfos(char *dir_name, t_param *param);
void				free_dirinfos(void *infos, unsigned long t_size);

int					sort_arg(int ac, char **av, t_param *param);
t_list				*list_dir(char *dir_name, t_param *param);
int					ft_namecmp(t_dirinfos *infos1, t_dirinfos *infos2);
int					ft_mtimecmp(t_dirinfos *infos1, t_dirinfos *infos2);
int					ft_atimecmp(t_dirinfos *infos1, t_dirinfos *infos2);
void				to_display(t_dirinfos *infos, t_param *param, int iter);
void				print_lst(t_list *first, t_param *param, int iter);
void				print_folder_name(char *str, t_param *param);

void				put_total(t_param *param);
void				get_mode(char *str, t_stat *buf, t_dirinfos *infos);
void				get_infos(char *str, t_stat *buf, t_param *param,
							t_dirinfos *infos);

void				error_open(char *dir_name, t_param *param);
void				error_opt(char opt);

#endif
