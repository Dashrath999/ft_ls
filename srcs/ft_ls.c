/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:49:39 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/06/03 17:16:29 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	int		i;
	t_opt	opt;
	t_node	*arg_tree;
	int		nb_arg;
	int		*f_width;

	init_opt(&opt);
	if ((i = parse(ac, av, &opt)) == -1)
		return (-1);
	nb_arg = ac - i;
	if (!(arg_tree = fill_arg_tree(av, &opt, ac, i)))
		return (-1);
	f_width = get_f_width(arg_tree, &opt);
	if (traverse(arg_tree, &opt, nb_arg, f_width) == -1)
		return (-1);
	free(f_width);
	if (opt.opt_bigr)
		free_traverse(arg_tree);
	else
		free_traverse_no_bigr(arg_tree);
	return (0);
}
