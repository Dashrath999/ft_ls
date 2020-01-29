/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:02:20 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/06/14 14:59:58 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		num_len(int n)
{
	long long	i;
	int			len;
	int			sign;

	sign = (n < 0) ? 1 : 0;
	if (sign)
		n = -n;
	len = 0;
	i = n;
	if (i == 0)
		return (1);
	while (i > 0)
	{
		i /= 10;
		len++;
	}
	return (len + sign);
}

char	*get_time(t_node *node)
{
	time_t		cur_time;
	char		*t;

	if (time(&cur_time) - node->data->time >= 15770000 || time(&cur_time) -
	node->data->time < 0)
		t = get_old_time(node);
	else
		t = ft_strsub(ctime(&node->data->time), 4, 12);
	if (!t)
		return (NULL);
	return (t);
}

void	print_dev_not_cb(t_node *node, int *width, char *t)
{
	if (width == NULL)
		ft_printf("%c%s %d %s %s %ld %s %s", node->data->type,
		node->data->perm, node->data->links, node->data->owner,
		node->data->group, node->data->size, t, node->data->name);
	if (width)
		ft_printf("%c%s %*d %*s %-*s %*ld %s %s", node->data->type,
		node->data->perm, width[0], node->data->links, width[1],
		node->data->owner, width[2], node->data->group,
		width[5] + 3 + width[3], node->data->size,
		t, node->data->name);
}

int		get_owner(t_node *node, struct stat buf)
{
	struct passwd	*pwd;

	if ((pwd = getpwuid(buf.st_uid)))
	{
		if (!(node->data->owner = ft_strdup(pwd->pw_name)))
			return (-1);
	}
	else
	{
		if (!(node->data->owner = ft_itoa(buf.st_uid)))
			return (-1);
	}
	return (0);
}

int		get_group(t_node *node, struct stat buf)
{
	struct group *grp;

	if ((grp = getgrgid(buf.st_gid)))
	{
		if (!(node->data->group = ft_strdup(grp->gr_name)))
			return (-1);
	}
	else
	{
		if (!(node->data->group = ft_itoa(buf.st_uid)))
			return (-1);
	}
	return (0);
}
