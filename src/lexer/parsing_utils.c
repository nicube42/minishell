/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:06:17 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/19 09:19:56 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_red_exit_to_string(char *line, t_vars *vars, int i)
{
	int	count;

	count = 0;
	i++;
	i = ft_skip_blank(line, i);
	while (!ft_is_blank(line[i]) && line[i] && !ft_sep_or_doll(line, i))
	{
		count++;
		i++;
	}
	i -= count;
	vars->tmp_tok[vars->j] = ft_calloc((count + 2), sizeof(char));
	count = 0;
	vars->tmp_tok[vars->j][count] = '>';
	count++;
	while (!ft_is_blank(line[i]) && line[i] && !ft_sep_or_doll(line, i))
	{
		vars->tmp_tok[vars->j][count] = line[i];
		count++;
		i++;
	}
	vars->j++;
	return (i);
}

int	ft_append_to_string(char *line, t_vars *vars, int i)
{
	int	count;

	count = 0;
	i += 2;
	i = ft_skip_blank(line, i);
	while (!ft_is_blank(line[i]) && line[i] && !ft_sep_or_doll(line, i))
	{
		count++;
		i++;
	}
	i -= count;
	vars->tmp_tok[vars->j] = ft_calloc((count + 3), sizeof(char));
	count = 0;
	vars->tmp_tok[vars->j][count] = '>';
	vars->tmp_tok[vars->j][count + 1] = '>';
	count += 2;
	while (!ft_is_blank(line[i]) && line[i] && !ft_sep_or_doll(line, i))
	{
		vars->tmp_tok[vars->j][count] = line[i];
		count++;
		i++;
	}
	vars->j++;
	return (i);
}

int	ft_pipe_to_string(char *line, t_vars *vars, int i)
{
	vars->tmp_tok[vars->j] = ft_calloc(2, sizeof(char));
	vars->tmp_tok[vars->j][0] = line[i];
	i++;
	vars->j++;
	return (i);
}

int	ft_count_inside_quote(int i, t_vars *vars, char *line)
{
	int	count;

	count = 0;
	while (line[i])
	{
		if (vars->quote || vars->dquote)
			count++;
		i++;
	}
	return (count);
}

int	ft_parse_inside_quote(char *line, t_vars *vars, int i)
{
	int	count;

	count = ft_count_inside_quote(i, vars, line);
	vars->tmp_tok[vars->j] = ft_calloc(count + 2, sizeof(char));
	count = 0;
	while (line[i])
	{
		i = ft_handle_quote(line, vars, i);
		if (vars->quote || vars->dquote)
		{
			vars->tmp_tok[vars->j][count] = line[i];
			count++;
		}
		else
		{
			vars->j++;
			return (i);
		}
		i++;
	}
	vars->j++;
	return (i);
}
