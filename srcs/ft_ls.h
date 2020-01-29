/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:50:29 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/06/13 19:46:35 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"
# include <dirent.h>
# include <sys/types.h>
# include <time.h>
# include <sys/stat.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <pwd.h>
# include <grp.h>

#include <sys/sysmacros.h>
typedef	struct			s_opt
{
	int					opt_a;
	int					opt_l;
	int					opt_bigr;
	int					opt_r;
	int					opt_t;
}						t_opt;

typedef struct			s_data{
	char				type;
	char				*perm;
	int					links;
	char				*owner;
	char				*group;
	off_t				size;
	time_t				time;
	char				*name;
	char				*path;
	struct s_node		*dir_tree;
	blksize_t			nb_blk;
	int					error;
	int					empty_dir;
	char				*linkname;
	char				linktype;
	unsigned int		r_dev;
	int					freed;
}						t_data;

typedef struct			s_node
{
	t_data				*data;
	struct s_node		*left;
	struct s_node		*right;
}						t_node;

void					init_opt(t_opt *opt);
void					init_d_tab(int *tab);

int						parse(int ac, char **av, t_opt *opt);
int						is_opt(char c);
void					update_opt(t_opt *opt, char c);

t_node					*fill_arg_tree(char **av, t_opt *opt, int ac, int i);
int						multiple_arg(char *av_i, t_node *root, t_opt *opt);
void					add_arg_node(t_node *node, t_node *root, t_opt *opt);
char					*get_arg_path(char *av);
void					rev_add_arg_node(t_node *node, t_node *root,
						t_opt *opt);

t_node					*new_node(char *path);
int						read_link(struct stat buf, t_node *node, char *path);
int						fill_node_info(t_node *node, struct stat buf);
char					*get_perm(struct stat buf);
char					get_arg_type(struct stat buf);

int						cmp_type_time(t_node *node, t_node *root, t_opt *opt);
int						cmp_type_alpha(t_node *node, t_node *root, t_opt *opt);
int						cmp_alpha(t_node *node, t_node *root);
int						cmp_time(t_node *node, t_node *root);
int						is_not_dir(t_node *node, t_opt *opt);

int						traverse(t_node *root, t_opt *opt, int nb_arg,
						int *f_width);
int						traverse_reccur(t_node *root, t_opt *opt, int nb_arg,
						int *f_width);
void					traverse_d_width(t_node *dir_root, int *tab,
						t_opt *opt);
void					traverse_f_width(t_node *arg_tree, int *tab,
						t_opt *opt);

t_node					*fill_dir_tree(t_node *node, t_opt *opt);
int						multiple_f(struct dirent *sd, t_node *dir_node, t_opt
						*opt, t_node *dir_root);
void					add_dir_node(t_node *node, t_node *root, t_opt *opt);
char					*get_path(char *dir_path, char *f_name, char type);
void					rev_add_dir_node(t_node *node, t_node *root,
						t_opt *opt);

int						get_dir(t_node *dir_node, t_node **dir_root, t_opt *o);
int						get_empty_dir(t_node *d, t_node **dir_root, t_opt *o);
int						create_error_node(t_node **dir_root);
int						assign_dir_root(char *dir_node_path,
						struct dirent *sd, t_node **dir_root);

void					print(t_node *root, t_opt *opt, int nb_arg,
						int *f_width);
void					print_d(t_node *node, t_opt *opt, int nb_arg,
						long long *pass);
void					print_dir(t_node *dir_root, t_opt *opt, int *width);

void					print_long_format(t_node *node, int *tab_width);
void					print_dev(t_node *node, int *width);
int						*get_dir_width(t_node *dir_root, t_opt *opt);
int						*get_f_width(t_node *arg_tree, t_opt *opt);
char					*get_old_time(t_node *node);

void					free_traverse(t_node *arg_tree);
void					free_node(t_node *node);
void					free_error(t_node *node);
void					free_dir_error(t_node *node);

void					free_traverse_no_bigr(t_node *arg_tree);

int						num_len(int n);
char					*get_time(t_node *node);
void					print_dev_not_cb(t_node *node, int *width, char *t);
int						print_error(t_node *node, long long *pass);
int						get_owner(t_node *node, struct stat buf);
int						get_group(t_node *node, struct stat buf);
#endif
