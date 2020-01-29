/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 17:55:11 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/05/21 17:55:28 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		init_opt(t_opt *opt)
{
	opt->opt_a = 0;
	opt->opt_l = 0;
	opt->opt_bigr = 0;
	opt->opt_r = 0;
	opt->opt_t = 0;
}

void		init_d_tab(int *tab)
{
	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 0;
	tab[4] = 0;
	tab[5] = 2;
	tab[6] = 1;
	tab[7] = 0;
}