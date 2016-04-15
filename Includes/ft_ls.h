/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 15:34:00 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/15 16:10:49 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define OPT_REF "Ralrt"
# define OPT param->opt
# define L_SZ param->len_size
# define L_LK param->len_link
# define L_US param->len_usr
# define L_GR param->len_gr
# define C_DIR pram->c_dir

typedef struct stat	t_stat;
typedef struct	s_param
{
	char	opt;
	int		len_size;
	int		len_link;
	int		len_usr;
	int		len_gr;
	char	*c_dir;
}				t_param;

t_param	*init_param(char opt);
void    print_param(t_param *param);
void    update_param(char *dir_name, t_param *param);
void	ft_ls(int ac, char **av, t_param *param);
void	list_dir(char *dir_name, t_param *param);
void	error_opt(char opt);

#endif