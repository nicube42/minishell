/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivautrav <ivautrav@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:09:25 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/10 11:15:38 by ivautrav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*ft_create_redir_token(char *content, int id)
{
	t_token	*token;

	token = ft_init_token();
	token->id = id;
	token->class = ft_init_redir_token(content, id);
	return (token);
}

t_redir	*ft_init_redir_token(char *content, int id)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->id = id;
	redir->content = content;
	redir->fdin = STDIN_FILENO;
	redir->fdout = STDOUT_FILENO;
	return (redir);
}
