/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 20:20:22 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/06/12 19:10:52 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		parse(int ac, char **av, t_opt *opt)
{
	int i;
	int j;

	i = 1;
	while (ac-- > 1)
	{
		if (av[i][0] != '-' || ft_strequ(av[i], "-"))
			return (i);
		if (ft_strequ(av[i], "--"))
			return (i + 1);
		j = 0;
		while (av[i][++j])
		{
			if (is_opt(av[i][j]))
				update_opt(opt, av[i][j]);
			else
			{
				ft_printf("ft_ls : illegal option -- %c\n", av[i][j]);
				ft_putstr("usage [-Ralrt] [file ...]\n");
				return (-1);
			}
		}
		i++;
	}
	return (i);
}

int		is_opt(char c)
{
	if (c == 'a' || c == 'l' || c == 'R' || c == 'r' || c == 't')
		return (1);
	return (0);
}

void	update_opt(t_opt *opt, char c)
{
	if (c == 'a')
		opt->opt_a = 1;
	else if (c == 'l')
		opt->opt_l = 1;
	else if (c == 'R')
		opt->opt_bigr = 1;
	else if (c == 'r')
		opt->opt_r = 1;
	else if (c == 't')
		opt->opt_t = 1;
}
