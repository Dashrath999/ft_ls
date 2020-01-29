/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_arg_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 15:26:09 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/05/21 19:36:43 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_node		*fill_arg_tree(char **av, t_opt *opt, int ac, int i)
{
	int		nb_arg;
	t_node	*root;

	nb_arg = ac - i;
	root = (nb_arg == 0) ? new_node("./") : new_node(av[i]);
	if (root == NULL)
		return (NULL);
	root->data->name = (nb_arg == 0) ? ft_strdup(".") : ft_strdup(av[i]);
	if (nb_arg != 0)
		root->data->path = (root->data->type == 'd') ? get_arg_path(av[i])
		: ft_strdup(av[i]);
	else
		root->data->path = ft_strdup("./");
	if (root->data->name == NULL || root->data->path == NULL)
		return (NULL);
	nb_arg--;
	i++;
	while (nb_arg-- > 0)
	{
		if (multiple_arg(av[i], root, opt) == -1)
			return (NULL);
		i++;
	}
	return (root);
}

int			multiple_arg(char *av_i, t_node *root, t_opt *opt)
{
	t_node *node;

	node = new_node(av_i);
	if (!node)
		return (-1);
	node->data->name = ft_strdup(av_i);
	node->data->path = (node->data->type == 'd') ? get_arg_path(av_i)
	: ft_strdup(av_i);
	if (!node->data->name || !node->data->path)
		return (-1);
	if (!opt->opt_r)
		add_arg_node(node, root, opt);
	else if (opt->opt_r)
		rev_add_arg_node(node, root, opt);
	return (0);
}

void		add_arg_node(t_node *node, t_node *root, t_opt *opt)
{
	int (*cmp) (t_node *node, t_node *root, t_opt *opt);

	cmp = (opt->opt_t) ? cmp_type_time : cmp_type_alpha;
	if (!cmp(node, root, opt))
	{
		if (root->left == NULL)
			root->left = node;
		else
			add_arg_node(node, root->left, opt);
	}
	if (cmp(node, root, opt))
	{
		if (root->right == NULL)
			root->right = node;
		else
			add_arg_node(node, root->right, opt);
	}
}

void		rev_add_arg_node(t_node *node, t_node *root, t_opt *opt)
{
	int (*cmp) (t_node *node, t_node *root, t_opt *opt);

	cmp = (opt->opt_t) ? cmp_type_time : cmp_type_alpha;
	if (cmp(node, root, opt))
	{
		if (root->left == NULL)
			root->left = node;
		else
			rev_add_arg_node(node, root->left, opt);
	}
	if (!cmp(node, root, opt))
	{
		if (root->right == NULL)
			root->right = node;
		else
			rev_add_arg_node(node, root->right, opt);
	}
}

char		*get_arg_path(char *av_i)
{
	int		last_char;
	int		count;

	count = 0;
	last_char = ft_strlen(av_i) - 1;
	if (av_i[last_char] == '/' && av_i[last_char - 1] == '/')
	{
		while (av_i[last_char] == '/')
		{
			count++;
			last_char--;
		}
		return (ft_strsub(av_i, 0, ft_strlen(av_i) - count + 1));
	}
	else if (av_i[last_char] != '/')
		return (ft_strjoin(av_i, "/"));
	return (ft_strdup(av_i));
}
