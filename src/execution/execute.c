/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 06:50:06 by ivautrav          #+#    #+#             */
/*   Updated: 2023/05/17 10:22:11 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bashmaster.h>
#include <minishell.h>

/*static char	*check_infile(t_vars *vars)
{
	char	*infile_name;
	t_token	*tok;

	tok = vars->first;
	while (tok && tok->id != RED_ENTRY_TOKEN)
		tok = tok->next;
	if (tok == NULL)
		return (NULL);
	infile_name = ((t_redir *)tok->class)->content + 1;
	if (infile_name == NULL)
		return (NULL);
	if (access(infile_name, F_OK) != 0)
		return ("");
	return (infile_name);
}

int	get_nb_commands(t_vars *vars)
{
	t_token	*tmp;
	int		cnt;

	cnt = 0;
	tmp = vars->first;
	while (tmp != NULL)
	{
		if (tmp->id == CMD_TOKEN)
			cnt++;
		tmp = tmp->next;
	}
	return (cnt);
}*/

t_bool	execute_command(t_vars *vars)
{
	(void)	vars;
	/*int		*childs;
	int		ret;
	t_token	*tok;
	int		i;
	char	*ret_file;
	int		fdpipe[2];

	//char	output[4096];

	(void) vars;
	vars->fdin_orig = dup(STDIN_FILENO);
	vars->fdout_orig = dup(STDOUT_FILENO);
	ret_file = check_infile(vars);
	if (ret_file != NULL && ft_strncmp(ret_file, "", 1) == 0)
		return (FALSE);
	if (ret_file != NULL)
	{
		vars->fdin = open(ret_file, O_RDONLY);
	}
	else
		vars->fdin = dup(vars->fdin_orig);
	i = 0;
	childs = (int *) malloc(sizeof(int) * get_nb_commands(vars));
	if (childs == NULL)
		return (FALSE);
	while (i < get_nb_commands(vars))
	{
		if (i == get_nb_commands(vars) - 1)
		{
			vars->fdout = dup(vars->fdout_orig);
		}
		else
		{
			pipe(fdpipe);
		}
		ret = fork();
		childs[i] = ret;
		if (ret == 0)
		{
			dup2(vars->fdin, STDIN_FILENO);
			dup2(fdpipe[1], STDOUT_FILENO);
			close(fdpipe[0]);
			close(fdpipe[1]);
			tok = vars->first;
			while (tok && tok->next)
				tok = tok->next;
			if (tok->id != CMD_TOKEN)
				exit(1);
			((t_cmd *)tok->class)->args[0] = ((t_cmd *)tok->class)->path;
			execve(((t_cmd *)tok->class)->path, ((t_cmd *)tok->class)->args, \
					vars->splitted_path);
			perror("Error Execution");
			exit(1);
		}
		else
		{
			ret = fork();
			childs[i] = ret;
			if (ret == 0)
			{
				printf("test\n");
				dup2(fdpipe[0], STDIN_FILENO);
				close(fdpipe[1]);
				close(fdpipe[0]);
				dup2(vars->fdout, STDOUT_FILENO);
				tok = vars->first;
				while (tok && tok->next)
					tok = tok->next;
				if (tok->id != CMD_TOKEN)
					exit(1);
				((t_cmd *)tok->class)->args[0] = ((t_cmd *)tok->class)->path;
				execve(((t_cmd *)tok->class)->path, ((t_cmd *)tok->class)->args, \
					vars->splitted_path);
			}
		}
		i++;
	}
	i = -1;
	//while (++i < get_nb_commands(vars))
		waitpid(childs[0], NULL, 0);
		waitpid(childs[1], NULL, 0);
	dup2(vars->fdin_orig, 0);
	dup2(vars->fdout_orig, 1);
	close(vars->fdin_orig);
	close(vars->fdout_orig);
	//free(ret_file);
	free(childs);
	return (TRUE);
	*/
	return (0);
}
