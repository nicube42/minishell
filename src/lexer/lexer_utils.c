/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:17:26 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/19 10:06:46 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_token_len(char *str, int i)
{
	int	quote;
	int	dquote;

	quote = 0;
	dquote = 0;
	while (str[i])
	{
		if (ft_is_quote(str[i]) == 1)
			quote = !quote;
		if (ft_is_quote(str[i]) == 2)
			dquote = !dquote;
		if (ft_is_blank(str[i]) && !quote && !dquote)
			return (i);
		i++;
	}
	return (i);
}

void	ft_count_quote(int *quote, int *dquote, char *str, int i)
{
	if (ft_is_quote(str[i]) == 1)
		*quote = !(*quote);
	if (ft_is_quote(str[i]) == 2)
		*dquote = !(*dquote);
}

int	ft_token_qty(char *str)
{
	int	quote;
	int	dquote;
	int	i;
	int	k;

	i = 0;
	k = 1;
	quote = 0;
	dquote = 0;
	while (str[i])
	{
		ft_count_quote(&quote, &dquote, str, i);
		if (ft_is_blank(str[i]) && !quote && !dquote)
		{
			while (ft_is_blank(str[i]))
				i++;
			k++;
		}
		else if (ft_is_separator(str, i) && !quote && !dquote)
			k++;
		else if (str[i] == '$' && !quote && !dquote)
			k++;
		i++;
	}
	return (k);
}

int	ft_check_cmd(char *tok, t_vars *vars)
{
	int		i;
	char	*cmd;

	i = -1;
	vars->tmp_path = NULL;
	while (vars->splitted_path[++i])
	{
		cmd = ft_strjoin(vars->splitted_path[i], tok);
		if (access(cmd, F_OK) == 0)
		{
			vars->tmp_path = ft_strdup(cmd);
			free(cmd);
			return (0);
		}
		free(cmd);
	}
	return (1);
}
