/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:44:16 by nicolasdiam       #+#    #+#             */
/*   Updated: 2023/05/10 11:13:05 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_INT 2147483647
# define MIN_INT -2147483648
# define BLANK_TOKEN 0
# define PIPE_TOKEN 1
# define BUILTIN_TOKEN 2

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft_printf/includes/libft.h"
# include "../libft_printf/includes/ft_printf.h"

typedef struct s_vars
{
	struct s_token	*first;
	char			**splitted_path;
}t_vars;

typedef struct s_token
{
	void			*class;
	int				id;
	struct s_token	*next;
	struct s_token	*prev;

}t_token;

typedef struct s_cmd
{
	int		id;
	char	*content;
	char	**args;
	int		fdin;
	int		fdout;
}t_cmd;

typedef struct s_redir
{
	int		id;
	char	*content;
	int		fdin;
	int		fdout;
}t_redir;

int		ft_token_len(char *str, int i);
int		ft_token_qty(char *str);
void	ft_parsing(char *line, t_vars *vars);
int		main(int ac, char **av, char **envp);
int		ft_is_quote(char c);
int		ft_is_blank(char c);
int		ft_is_separator(char *str, int i);
void	ft_sort_tokens(char	**tmp, t_vars *vars);
void	ft_sort_separators(char **tmp, int i, t_vars *vars);
void	ft_sort_cmd_arg(char **tmp, int *i, int *temoin, t_vars *vars);
void	ft_sort_dollar(char **tmp, int i);
int		ft_check_cmd(char *tok, t_vars *vars);

t_cmd	*ft_init_cmd_token(char *content, int id, char **args);
void	ft_add_token(t_vars *vars, t_token *to_add);
void	ft_connect_token(t_token *list, t_token *to_add);
t_token	*ft_create_cmd_token(char *content, int id, char **args);
t_token	*ft_init_token(void);
t_token	*ft_create_redir_token(char *content, int id);
t_redir	*ft_init_redir_token(char *content, int id);
void	ft_print_tokens(t_vars *vars);

#endif