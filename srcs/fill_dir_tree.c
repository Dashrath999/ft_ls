/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_dir_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:06:02 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/06/13 19:57:02 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_node		*fill_dir_tree(t_node *dir_node, t_opt *opt)
{
	t_node			*dir_root;
	DIR				*dir;
	struct dirent	*sd;
	int				ret;

	ret = get_dir(dir_node, &dir_root, opt);
	if (ret == -1)
		return (NULL);
	if (ret == 1)
		return (dir_root);
	if (!(dir = opendir(dir_node->data->path)))
		return (NULL);
	sd = readdir(dir);
	while ((sd->d_name[0] == '.' && !opt->opt_a) &&
	(sd = readdir(dir)))
		;
	if (assign_dir_root(dir_node->data->path, sd, &dir_root) == -1)
		return (NULL);
	while ((sd = readdir(dir)) != NULL)
		if (multiple_f(sd, dir_node, opt, dir_root) == -1)
			return (NULL);
	closedir(dir);
	return (dir_root);
}

int			multiple_f(struct dirent *sd, t_node *dir_node, t_opt *opt,
			t_node *dir_root)
{
	t_node	*node;
	char	*path;

	if (sd->d_name[0] == '.' && !opt->opt_a)
		return (0);
	if (!(path = get_path(dir_node->data->path, sd->d_name, sd->d_type)))
		return (-1);
	if (!(node = new_node(path)))
		return (-1);
	node->data->name = ft_strdup(sd->d_name);
	node->data->path = ft_strdup(path);
	free(path);
	if (!node->data->name || !node->data->path)
		return (-1);
	if (!opt->opt_r)
		add_dir_node(node, dir_root, opt);
	else if (opt->opt_r)
		rev_add_dir_node(node, dir_root, opt);
	return (0);
}

void		add_dir_node(t_node *node, t_node *root, t_opt *opt)
{
	int (*cmp) (t_node *node, t_node *root);

	cmp = (opt->opt_t) ? cmp_time : cmp_alpha;
	if (!cmp(node, root))
	{
		if (root->left == NULL)
			root->left = node;
		else
			add_dir_node(node, root->left, opt);
	}
	if (cmp(node, root))
	{
		if (root->right == NULL)
			root->right = node;
		else
			add_dir_node(node, root->right, opt);
	}
}

void		rev_add_dir_node(t_node *node, t_node *root, t_opt *opt)
{
	int (*cmp) (t_node *node, t_node *root);

	cmp = (opt->opt_t) ? cmp_time : cmp_alpha;
	if (cmp(node, root))
	{
		if (root->left == NULL)
			root->left = node;
		else
			rev_add_dir_node(node, root->left, opt);
	}
	if (!cmp(node, root))
	{
		if (root->right == NULL)
			root->right = node;
		else
			rev_add_dir_node(node, root->right, opt);
	}
}

char		*get_path(char *dir_path, char *f_name, char type)
{
	char *dir_slash;
	char *tmp;
	char *path;

	if (dir_path[ft_strlen(dir_path) - 1] != '/')
	{
		if (!(dir_slash = ft_strjoin(dir_path, "/")))
			return (NULL);
		if (!(path = ft_strjoin(dir_slash, f_name)))
			return (NULL);
		free(dir_slash);
	}
	else
	{
		if (!(path = ft_strjoin(dir_path, f_name)))
			return (NULL);
	}
	if (type == 'd')
	{
		if (!(tmp = ft_strjoin(path, "/")))
			return (NULL);
		free(path);
		return (tmp);
	}
	return (path);
}
