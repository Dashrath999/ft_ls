/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 17:59:47 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/06/12 20:52:05 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print(t_node *node, t_opt *opt, int nb_arg, int *f_width)
{
	static long long pass;

	if (print_error(node, &pass) == 1)
		return ;
	if (node->data->dir_tree && node->data->dir_tree->data->error &&
	ft_printf("ft_ls: %s: %s\n",
	node->data->path, strerror(node->data->dir_tree->data->error)) && ++pass)
		return ;
	else if ((node->data->type == 'l' && (node->data->linktype != 'd' ||
	opt->opt_l)) || (node->data->type != 'd' && node->data->type != 'l'))
	{
		pass++;
		if (opt->opt_l && (node->data->type == 'c' || node->data->type == 'b'))
			return (print_dev(node, f_width));
		(opt->opt_l) ? print_long_format(node, f_width) :
		ft_printf("%s\n", node->data->name);
	}
	if (node->data->type == 'd' ||
	(node->data->type == 'l' && node->data->linktype == 'd' && !opt->opt_l))
	{
		print_d(node, opt, nb_arg, &pass);
		if (opt->opt_bigr && node->data->dir_tree != NULL)
			traverse_reccur(node->data->dir_tree, opt, nb_arg, f_width);
	}
}

int			print_error(t_node *node, long long *pass)
{
	if (node->data->error)
	{
		*pass = *pass + 1;
		ft_printf("ft_ls: %s: %s\n",
		node->data->path, strerror(node->data->error));
		return (1);
	}
	return (0);
}

void		print_d(t_node *node, t_opt *opt, int nb_arg, long long *pass)
{
	int *dir_width;

	if ((nb_arg > 1 || opt->opt_bigr) && *pass == 0)
		ft_printf("%s:\n", node->data->path);
	else if (nb_arg > 1 || opt->opt_bigr)
		ft_printf("\n%s:\n", node->data->path);
	if (node->data->dir_tree->data->empty_dir)
		return ;
	*pass = *pass + 1;
	dir_width = get_dir_width(node->data->dir_tree, opt);
	if (opt->opt_l)
		ft_printf("total %d\n", dir_width[4]);
	print_dir(node->data->dir_tree, opt, dir_width);
	free(dir_width);
}

void		print_dir(t_node *dir_root, t_opt *opt, int *width)
{
	if (dir_root->left != NULL)
		print_dir(dir_root->left, opt, width);
	if (opt->opt_a || dir_root->data->name[0] != '.')
	{
		(opt->opt_l) ? print_long_format(dir_root, width) :
		ft_printf("%s\n", dir_root->data->name);
	}
	if (dir_root->right != NULL)
		print_dir(dir_root->right, opt, width);
}
