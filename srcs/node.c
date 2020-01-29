/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 19:00:15 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/06/14 14:59:43 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_node		*new_node(char *path)
{
	t_node		*node;
	struct stat	buf;

	if (!(node = malloc(sizeof(t_node))))
		return (NULL);
	if (!(node->data = malloc(sizeof(t_data))))
		return (NULL);
	if (lstat(path, &buf) == -1)
	{
		node->data->error = errno;
		node->data->dir_tree = NULL;
		node->left = NULL;
		node->right = NULL;
		return (node);
	}
	if (S_ISLNK(buf.st_mode))
		if (read_link(buf, node, path) == -1)
			return (NULL);
	if (fill_node_info(node, buf) == -1)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->data->dir_tree = NULL;
	return (node);
}

int			read_link(struct stat buf, t_node *node, char *path)
{
	char			*linkname;
	int				r;
	struct stat		link_buf;

	if (!(linkname = malloc(buf.st_size + 1)))
		return (-1);
	r = readlink(path, linkname, buf.st_size + 1);
	if (r < 0)
		node->data->error = errno;
	linkname[buf.st_size] = '\0';
	if (!(node->data->linkname = ft_strdup(linkname)))
		return (-1);
	free(linkname);
	stat(path, &link_buf);
	node->data->linktype = get_arg_type(link_buf);
	return (0);
}

int			fill_node_info(t_node *node, struct stat buf)
{
	node->data->type = get_arg_type(buf);
	if ((node->data->perm = get_perm(buf)) == NULL)
		return (-1);
	node->data->links = buf.st_nlink;
	if (get_owner(node, buf) == -1)
		return (-1);
	if (get_group(node, buf) == -1)
		return (-1);
	node->data->size = buf.st_size;
	node->data->time = buf.st_mtime;
	node->data->nb_blk = buf.st_blocks;
	node->data->error = 0;
	node->data->empty_dir = 0;
	node->data->freed = 0;
	if (node->data->type == 'c' || node->data->type == 'b')
		node->data->r_dev = buf.st_rdev;
	return (0);
}

char		*get_perm(struct stat buf)
{
	char *perm;

	if (!buf.st_mode)
		return (NULL);
	if (!(perm = malloc(sizeof(char) * 10)))
		return (NULL);
	perm[0] = (buf.st_mode & S_IRUSR) ? 'r' : '-';
	perm[1] = (buf.st_mode & S_IWUSR) ? 'w' : '-';
	perm[2] = (buf.st_mode & S_IXUSR) ? 'x' : '-';
	if (buf.st_mode & S_ISUID)
		perm[2] = (perm[2] == 'x') ? 's' : 'S';
	perm[3] = (buf.st_mode & S_IRGRP) ? 'r' : '-';
	perm[4] = (buf.st_mode & S_IWGRP) ? 'w' : '-';
	perm[5] = (buf.st_mode & S_IXGRP) ? 'x' : '-';
	if (buf.st_mode & S_ISGID)
		perm[5] = (perm[5] == 'x') ? 's' : 'S';
	perm[6] = (buf.st_mode & S_IROTH) ? 'r' : '-';
	perm[7] = (buf.st_mode & S_IWOTH) ? 'w' : '-';
	perm[8] = (buf.st_mode & S_IXOTH) ? 'x' : '-';
	if (buf.st_mode & S_ISVTX)
		perm[8] = (perm[8] == 'x') ? 't' : 'T';
	perm[9] = '\0';
	return (perm);
}

char		get_arg_type(struct stat buf)
{
	if (S_ISREG(buf.st_mode))
		return ('-');
	else if (S_ISDIR(buf.st_mode))
		return ('d');
	else if (S_ISCHR(buf.st_mode))
		return ('c');
	else if (S_ISBLK(buf.st_mode))
		return ('b');
	else if (S_ISFIFO(buf.st_mode))
		return ('p');
	else if (S_ISLNK(buf.st_mode))
		return ('l');
	else if (S_ISSOCK(buf.st_mode))
		return ('s');
	return (0);
}
