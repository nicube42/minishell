/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bashmaster.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:01:49 by ivautrav          #+#    #+#             */
/*   Updated: 2023/05/10 15:01:44 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASHMASTER_H
# define BASHMASTER_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <constant.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"

typedef struct s_command
{
	int		nb_args;
	char	**args;
	char	*exec_path;
}	t_command;

typedef struct s_bash
{
	//t_lexer		lexer;
	t_command	*commands;
	int			nb_commands;
	int			fdin;
	int			fdin_orig;
	int			fdout;
	int			fdout_orig;
	char		**splitted_path;
	char		**envp;
}	t_bash;

t_bool	extract_tokens(t_bash *bash, char *input);
t_bool	check_syntax(t_bash *bash);

void	parsing_execve(t_bash *bash);
char	*get_command_fullpath(t_bash *bash, char *command);

t_bool	execute_command(t_bash *bash);
t_bool	set_commands(t_bash *bash);

char	*get_infile_name(t_bash *bash);

char	*append_char(char *str, char c);

#endif