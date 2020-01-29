/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:16:39 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/06/03 17:17:11 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		free_traverse(t_node *arg_tree)
{
	if (arg_tree->left != NULL)
		free_traverse(arg_tree->left);
	if (arg_tree->data->dir_tree != NULL &&
	!arg_tree->data->dir_tree->data->empty_dir &&
	!arg_tree->data->dir_tree->data->error)
	{
		arg_tree->data->freed = 1;
		free_traverse(arg_tree->data->dir_tree);
	}
	if (arg_tree->right != NULL)
		free_traverse(arg_tree->right);
	if (arg_tree->data->error)
	{
		free_error(arg_tree);
		return ;
	}
	if (arg_tree->data->freed != 1 && arg_tree->data->type == 'd'
	&& (!ft_strequ(".", arg_tree->data->name) &&
	!ft_strequ(arg_tree->data->name, "..")))
		free_dir_error(arg_tree);
	free_node(arg_tree);
}

void		free_traverse_no_bigr(t_node *arg_tree)
{
	if (arg_tree->left != NULL)
		free_traverse_no_bigr(arg_tree->left);
	if (arg_tree->data->dir_tree != NULL &&
	(arg_tree->data->dir_tree->data->error ||
	arg_tree->data->dir_tree->data->empty_dir))
		free_dir_error(arg_tree);
	if (arg_tree->data->dir_tree != NULL &&
	!arg_tree->data->dir_tree->data->empty_dir &&
	!arg_tree->data->dir_tree->data->error)
		free_traverse_no_bigr(arg_tree->data->dir_tree);
	if (arg_tree->right != NULL)
		free_traverse_no_bigr(arg_tree->right);
	if (arg_tree->data->error)
	{
		free_error(arg_tree);
		return ;
	}
	free_node(arg_tree);
}

void		free_node(t_node *node)
{
	free(node->data->perm);
	free(node->data->owner);
	free(node->data->group);
	free(node->data->name);
	free(node->data->path);
	if (node->data->type == 'l')
		free(node->data->linkname);
	free(node->data);
	free(node);
}

void		free_error(t_node *node)
{
	free(node->data->name);
	free(node->data->path);
	free(node->data);
	free(node);
}

void		free_dir_error(t_node *node)
{
	free(node->data->dir_tree->data);
	free(node->data->dir_tree);
}
