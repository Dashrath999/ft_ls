/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 17:56:39 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/06/03 17:58:41 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_long_format(t_node *node, int *width)
{
	char	*t;

	if (width != NULL && width[7] != 0)
		return (print_dev(node, width));
	if ((t = get_time(node)) == NULL)
		return ;
	if (width == NULL)
		ft_printf("%c%s %d %s %s %ld %s %s", node->data->type,
		node->data->perm, node->data->links, node->data->owner,
		node->data->group, node->data->size, t, node->data->name);
	if (width)
		ft_printf("%c%s %*d %*s %*s %*ld %s %s", node->data->type,
		node->data->perm, width[0], node->data->links, width[1],
		node->data->owner, width[2], node->data->group, width[3],
		node->data->size, t, node->data->name);
	if (node->data->type == 'l')
		ft_printf(" -> %s", node->data->linkname);
	ft_putchar('\n');
	free(t);
}

void		print_dev(t_node *node, int *width)
{
	char			*t;

	if ((t = get_time(node)) == NULL)
		return ;
	if (node->data->type == 'b' || node->data->type == 'c')
	{
		if (width == NULL)
			ft_printf("%c%s %d %s %s %u,   %u %s %s", node->data->type,
			node->data->perm, node->data->links, node->data->owner,
			node->data->group, major(node->data->r_dev),
			minor(node->data->r_dev), t, node->data->name);
		if (width)
			ft_printf("%c%s %*d %*s %-*s %*u,   %*u %s %s", node->data->type,
			node->data->perm, width[0], node->data->links, width[1],
			node->data->owner, width[2], node->data->group, width[5],
			major(node->data->r_dev), width[6],
			minor(node->data->r_dev), t, node->data->name);
	}
	else
		print_dev_not_cb(node, width, t);
	ft_putchar('\n');
	free(t);
}

char		*get_old_time(t_node *node)
{
	char *tmp;
	char *tmp2;
	char *time;
	char *ret;

	time = ctime(&node->data->time);
	tmp = ft_strsub(time, 20, 4);
	if (!tmp)
		return (NULL);
	tmp2 = ft_strsub(time, 4, 7);
	if (!tmp2)
		return (NULL);
	time = ft_strjoin(tmp2, " ");
	if (!time)
		return (NULL);
	ret = ft_strjoin(time, tmp);
	free(tmp);
	free(tmp2);
	free(time);
	return (ret);
}

int			*get_dir_width(t_node *dir_root, t_opt *opt)
{
	int		*tab;

	if (!(tab = malloc(sizeof(int) * 8)))
		return (NULL);
	init_d_tab(tab);
	traverse_d_width(dir_root, tab, opt);
	if (tab[0] == 0 && tab[1] == 0 && tab[2] == 0 && tab[3] == 0
	&& tab[4] == 0 && tab[5] == 0 && tab[6] == 0)
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}

int			*get_f_width(t_node *arg_tree, t_opt *opt)
{
	int		*tab;

	if (!(tab = malloc(sizeof(int) * 8)))
		return (NULL);
	init_d_tab(tab);
	traverse_f_width(arg_tree, tab, opt);
	if (tab[0] == 0 && tab[1] == 0 && tab[2] == 0 && tab[3] == 0
	&& tab[4] == 0 && tab[5] == 0 && tab[6] == 0)
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}
