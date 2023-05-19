/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 08:54:06 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/19 10:08:21 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_dollard_to_string(char *line, t_vars *vars, int i)
{
	int	count;
	int	start;

	start = i;
	count = 0;
	while (line[i] && !ft_is_blank(line[i]) && !ft_is_separator(line, i)
		&& line[i + 1] != '|' && line[i] != '$')
	{
		i++;
		count++;
	}
	vars->tmp_tok[vars->j] = ft_calloc(count + 2, sizeof(char));
	vars->tmp_tok[vars->j][0] = '$';
	count = 1;
	i = start + 1;
	while (line[i] && !ft_is_blank(line[i]) && !ft_is_separator(line, i)
		&& line[i + 1] != '|' && line[i] != '$')
	{
		i = ft_handle_quote(line, vars, i);
		vars->tmp_tok[vars->j][count] = line[i];
		i++;
		count++;
	}
	vars->j++;
	return (i);
}

int	ft_heredoc_to_string(char *line, t_vars *vars, int i)
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
	vars->tmp_tok[vars->j][count] = '<';
	vars->tmp_tok[vars->j][count + 1] = '<';
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

int	ft_red_entry_to_string(char *line, t_vars *vars, int i)
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
	vars->tmp_tok[vars->j][count] = '<';
	count++;
	while (!ft_is_blank(line[i]) && line[i] && !ft_sep_or_doll(line, i))
	{
		vars->tmp_tok[vars->j][count] = line[i];
		count++;
		i++;
	}
	i = ft_skip_blank(line, i);
	vars->j++;
	return (i);
}

int	ft_cmd_to_string(char *line, t_vars *vars, int i)
{
	int	count;
	int	start;

	start = i;
	count = 0;
	while (line[i] && !ft_is_blank(line[i]) && !ft_sep_or_doll(line, i))
	{
		i++;
		count++;
	}
	vars->tmp_tok[vars->j] = ft_calloc(count + 2, sizeof(char));
	count = 0;
	i = start;
	while (line[i] && !ft_is_blank(line[i]) && !ft_sep_or_doll(line, i))
	{
		vars->tmp_tok[vars->j][count] = line[i];
		i++;
		count++;
	}
	vars->j++;
	return (i);
}
