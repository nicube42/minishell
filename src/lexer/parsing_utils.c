/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:06:17 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/14 19:33:16 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_red_exit_to_string(char *line, t_vars *vars, int i)
{
	int	count;

	count = 0;
	i++;
	i = ft_skip_blank(line, i);
	while (!ft_is_blank(line[i]) && line[i] && !ft_is_separator(line, i))
	{
		count++;
		i++;
	}
	i -= count;
	vars->tmp_tok[vars->j] = ft_calloc((count + 2), sizeof(char));
	count = 0;
	vars->tmp_tok[vars->j][count] = '>';
	count++;
	while (!ft_is_blank(line[i]) && line[i] && !ft_is_separator(line, i))
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
	while (!ft_is_blank(line[i]) && line[i] && !ft_is_separator(line, i))
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
	while (!ft_is_blank(line[i]) && line[i] && !ft_is_separator(line, i))
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

int	ft_parse_inside_quote(char *line, t_vars *vars, int i)
{
	int	count;

	count = 0;
	vars->tmp_tok[vars->j] = ft_calloc(100, sizeof(char));
	while (line[i])
	{
		i = ft_handle_quote(line, vars, i);
		if (vars->quote || vars->dquote)
        {
		    vars->tmp_tok[vars->j][count] = line[i];
            count++;
        }
		i++;
	}
	vars->j++;
	return (i);
}

int	ft_cmd_to_string(char *line, t_vars *vars, int i)
{
	int	count;

	count = 0;
	vars->tmp_tok[vars->j] = ft_calloc(3, sizeof(char));
	while (line[i] && !ft_is_blank(line[i]) && !ft_is_separator(line, i))
	{
		vars->tmp_tok[vars->j][count] = line[i];
		i++;
		count++;
	}
	vars->j++;
	return (i);
}
