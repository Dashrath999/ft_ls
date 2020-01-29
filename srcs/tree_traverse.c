/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:04:12 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/06/13 19:01:37 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			traverse(t_node *root, t_opt *opt, int nb_arg, int *f_width)
{
	if (root->left != NULL)
		traverse(root->left, opt, nb_arg, f_width);
	if (root->data->type == 'd' || (root->data->type == 'l'
	&& (root->data->linktype == 'd' && !opt->opt_l)))
	{
		if (!(root->data->dir_tree = fill_dir_tree(root, opt)))
			return (-1);
	}
	print(root, opt, nb_arg, f_width);
	if (root->right != NULL)
		traverse(root->right, opt, nb_arg, f_width);
	return (0);
}

int			traverse_reccur(t_node *root, t_opt *opt, int nb_arg, int *f_width)
{
	if (root->left != NULL)
		traverse_reccur(root->left, opt, nb_arg, f_width);
	if (root->data->type == 'd' && ((!ft_strequ(root->data->name, ".") &&
	!ft_strequ(root->data->name, ".."))))
	{
		if (!(root->data->dir_tree = fill_dir_tree(root, opt)))
			return (-1);
		print(root, opt, nb_arg, f_width);
	}
	if (root->right != NULL)
		traverse_reccur(root->right, opt, nb_arg, f_width);
	return (0);
}

void		traverse_d_width(t_node *root, int *tab, t_opt *opt)
{
	unsigned int	major;
	unsigned int	minor;

	minor = root->data->r_dev / 256;
	major = ((256 * minor) - root->data->r_dev) * -1;
	if (root->left != NULL)
		traverse_d_width(root->left, tab, opt);
	if ((opt->opt_a || root->data->name[0] != '.') && !root->data->error)
	{
		tab[0] = (tab[0] > num_len(root->data->links)) ? tab[0] :
		num_len(root->data->links);
		tab[1] = (tab[1] > (int)ft_strlen(root->data->owner)) ? tab[1] :
		(int)ft_strlen(root->data->owner);
		tab[2] = (tab[2] > (int)ft_strlen(root->data->group)) ? tab[2] :
		(int)ft_strlen(root->data->group);
		tab[3] = (tab[3] > num_len(root->data->size)) ? tab[3] :
		num_len(root->data->size);
		tab[4] = tab[4] + root->data->nb_blk;
		tab[5] = (tab[5] > num_len(minor) + 1) ? tab[5] : num_len(minor) + 1;
		tab[6] = (tab[6] > num_len(major)) ? tab[6] : num_len(major);
		tab[7] = (root->data->type == 'c' || root->data->type == 'b')
		? tab[7] + 1 : tab[7];
	}
	if (root->right != NULL)
		traverse_d_width(root->right, tab, opt);
}

void		traverse_f_width(t_node *arg_tree, int *tab, t_opt *opt)
{
	unsigned int	major;
	unsigned int	minor;

	minor = arg_tree->data->r_dev / 256;
	major = ((256 * minor) - arg_tree->data->r_dev) * -1;
	if (arg_tree->left != NULL)
		traverse_f_width(arg_tree->left, tab, opt);
	if ((opt->opt_a || arg_tree->data->name[0] != '.')
	&& arg_tree->data->type != 'd' && !arg_tree->data->error)
	{
		tab[0] = (tab[0] > num_len(arg_tree->data->links)) ? tab[0] :
		num_len(arg_tree->data->links);
		tab[1] = (tab[1] > (int)ft_strlen(arg_tree->data->owner)) ? tab[1] :
		(int)ft_strlen(arg_tree->data->owner);
		tab[2] = (tab[2] > (int)ft_strlen(arg_tree->data->group)) ? tab[2] :
		(int)ft_strlen(arg_tree->data->group);
		tab[3] = (tab[3] > num_len(arg_tree->data->size)) ? tab[3] :
		num_len(arg_tree->data->size);
		tab[5] = (tab[5] > num_len(minor) + 1) ? tab[5] : num_len(minor) + 1;
		tab[6] = (tab[6] > num_len(major)) ? tab[6] : num_len(major);
		tab[7] = (arg_tree->data->type == 'c' || arg_tree->data->type == 'b')
		? tab[7] + 1 : tab[7];
	}
	if (arg_tree->right != NULL)
		traverse_f_width(arg_tree->right, tab, opt);
}
