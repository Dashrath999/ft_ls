/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir_root.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:21:03 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/06/13 17:23:42 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					get_dir(t_node *dir_node, t_node **dir_root, t_opt *opt)
{
	DIR				*s_dir;

	if ((s_dir = opendir(dir_node->data->path)) == NULL)
	{
		if (create_error_node(dir_root) == -1)
			return (-1);
		(*dir_root)->data->error = errno;
		(*dir_root)->data->empty_dir = 1;
		return (1);
	}
	if (readdir(s_dir) == NULL)
	{
		if (create_error_node(dir_root) == -1)
			return (-1);
		(*dir_root)->data->error = 0;
		(*dir_root)->data->empty_dir = 1;
		closedir(s_dir);
		return (1);
	}
	closedir(s_dir);
	return (get_empty_dir(dir_node, dir_root, opt));
}

int					get_empty_dir(t_node *d_nd, t_node **dir_root, t_opt *opt)
{
	struct dirent	*sd;
	DIR				*s_dir;

	s_dir = opendir(d_nd->data->path);
	while ((sd = readdir(s_dir)) != NULL)
	{
		while ((sd->d_name[0] == '.' && !opt->opt_a) &&
				(sd = readdir(s_dir)))
			;
		if (sd == NULL)
		{
			closedir(s_dir);
			if (create_error_node(dir_root) == -1)
				return (-1);
			(*dir_root)->data->error = 0;
			(*dir_root)->data->empty_dir = 1;
			return (1);
		}
		closedir(s_dir);
		return (0);
	}
	return (0);
}

int					create_error_node(t_node **dir_root)
{
	if (!(*dir_root = malloc(sizeof(t_node))))
		return (-1);
	if (!((*dir_root)->data = malloc(sizeof(t_data))))
		return (-1);
	(*dir_root)->data->dir_tree = NULL;
	(*dir_root)->left = NULL;
	(*dir_root)->right = NULL;
	return (0);
}

int					assign_dir_root(char *dir_node_path, struct dirent *sd,
					t_node **dir_root)
{
	char *path;

	if (!(path = get_path(dir_node_path, sd->d_name, sd->d_type)))
		return (-1);
	(*dir_root) = new_node(path);
	(*dir_root)->data->name = ft_strdup(sd->d_name);
	(*dir_root)->data->path = ft_strdup(path);
	if (!(*dir_root)->data->name || !(*dir_root)->data->path)
		return (-1);
	free(path);
	return (0);
}
