/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 18:43:00 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/06/14 16:03:45 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			cmp_time(t_node *node, t_node *root)
{
	int		res;
	char	*s1;
	char	*s2;

	s1 = root->data->name;
	s2 = node->data->name;
	res = root->data->time - node->data->time;
	if (res > 0)
		return (1);
	if (res == 0)
	{
		if (ft_strcmp(s1, s2) < 0)
			return (1);
	}
	return (0);
}

int			cmp_alpha(t_node *node, t_node *root)
{
	char *s1;
	char *s2;

	s1 = root->data->name;
	s2 = node->data->name;
	if (ft_strcmp(s1, s2) < 0)
		return (1);
	return (0);
}

int			cmp_type_time(t_node *node, t_node *root, t_opt *opt)
{
	int		res;

	res = root->data->time - node->data->time;
	if (root->data->error && !node->data->error)
		return (1);
	if (root->data->error && node->data->error)
	{
		if (res > 0)
			return (1);
		return (0);
	}
	if (is_not_dir(root, opt) && !is_not_dir(node, opt))
		return (1);
	if (((is_not_dir(root, opt) && is_not_dir(node, opt)) ||
	(!is_not_dir(root, opt) && !is_not_dir(node, opt))) && res > 0)
		return (1);
	if (res == 0)
	{
		if (ft_strcmp(root->data->name, node->data->name) < 0)
			return (1);
	}
	return (0);
}

int			cmp_type_alpha(t_node *node, t_node *root, t_opt *opt)
{
	char	*s1;
	char	*s2;
	int		res;

	s1 = (root->data->name[0] == '/') ? ft_strsub(root->data->name, 1,
	ft_strlen(root->data->name) - 1) : ft_strdup(root->data->name);
	s2 = (node->data->name[0] == '/') ? ft_strsub(node->data->name, 1,
	ft_strlen(node->data->name) - 1) : ft_strdup(node->data->name);
	res = ft_strcmp(s1, s2);
	free(s1);
	free(s2);
	if (root->data->error && !node->data->error)
		return (1);
	if (root->data->error && node->data->error)
	{
		if (res < 0)
			return (1);
		return (0);
	}
	if (is_not_dir(root, opt) && !is_not_dir(node, opt))
		return (1);
	if (((is_not_dir(root, opt) && is_not_dir(node, opt)) ||
	(!is_not_dir(root, opt) && !is_not_dir(node, opt))) && res < 0)
		return (1);
	return (0);
}

int			is_not_dir(t_node *node, t_opt *opt)
{
	char c;

	c = node->data->type;
	if ((c == 'l' && (node->data->linktype != 'd' || opt->opt_l)) ||
	(c != 'd' && c != 'l'))
		return (1);
	return (0);
}
