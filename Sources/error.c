/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 15:36:05 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/17 14:34:19 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"

void	error_opt(char opt)
{
	ft_putstr("./ft_ls: illegal option -- ");
	ft_putchar(opt);
	ft_putstr("\nusage: ls [-");
	ft_putstr(OPT_REF);
	ft_putstr("] [file ...]\n");
	exit(EXIT_FAILURE);
}
