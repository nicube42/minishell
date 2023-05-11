/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasdiamantis <nicolasdiamantis@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:44:16 by nicolasdiam       #+#    #+#             */
/*   Updated: 2023/05/11 11:26:25 by nicolasdiam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_INT 2147483647
# define MIN_INT -2147483648
# define BLANK_TOKEN 0
# define PIPE_TOKEN 1
# define RED_ENTRY_TOKEN 2
# define HERE_DOC_TOKEN 3
# define RED_EXIT_TOKEN 4
# define APPEND_TOKEN 5
# define ERR_DOLLAR_TOKEN 6
# define ENV_VAR_TOKEN 7
# define BUILTIN_TOKEN 8
# define CMD_TOKEN 9
# define NOT_CMD_TOKEN 10

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"

typedef struct s_vars
{
	struct s_token	*first;
	char			**splitted_path;
	char			*tmp_path;
	char			*tmp_stdin;
	char			*tmp_stdout;
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
	char	*path;
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

typedef struct s_dollar
{
	int		id;
	char	*content;
	int		fdin;
	int		fdout;
}t_dollar;

int			ft_token_len(char *str, int i);
int			ft_token_qty(char *str);
void		ft_parsing(char *line, t_vars *vars);
int			main(int ac, char **av, char **envp);
int			ft_is_quote(char c);
int			ft_is_blank(char c);
int			ft_is_separator(char *str, int i);
void		ft_sort_tokens(char	**tmp, t_vars *vars);
void		ft_sort_separators(char **tmp, int i, t_vars *vars);
void		ft_sort_cmd_arg(char **tmp, int *i, int *temoin, t_vars *vars);
char		**ft_sort_args(char **tmp, int	*i);
void		ft_sort_dollar(char **tmp, int i, t_vars *vars);
int			ft_check_cmd(char *tok, t_vars *vars);
int			ft_is_builtin(char **tmp, int i);

t_cmd		*ft_init_cmd_token(char *content, int id, char **args, t_vars *vars);
void		ft_add_token(t_vars *vars, t_token *to_add);
void		ft_connect_token(t_token *list, t_token *to_add);
void		ft_delete_all_tokens(t_vars *vars);
t_token		*ft_create_cmd_token(char *content, int id, char **args, t_vars *vars);
t_token		*ft_init_token(void);
t_token		*ft_create_redir_token(char *content, int id);
t_redir		*ft_init_redir_token(char *content, int id);
void		ft_print_tokens(t_vars *vars);
t_token		*ft_create_dollar_token(char *content, int id);
t_dollar	*ft_init_dollar_token(char *content, int id);
char		**ft_parsing_execve(char **envp);

#endif