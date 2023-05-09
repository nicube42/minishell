#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_INT 2147483647
# define MIN_INT -2147483648

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

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
void	ft_parsing(char *line);
int		main(void);
int		ft_is_quote(char c);
int		ft_is_blank(char c);
int		ft_is_separator(char *str, int i);
void	ft_sort_tokens(char	**tmp);

#endif