/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivautrav <ivautrav@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 06:50:06 by ivautrav          #+#    #+#             */
/*   Updated: 2023/05/10 11:18:45 by ivautrav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bashmaster.h>

static char	*check_infile(t_bash *bash)
{
	(void) bash;
	/*char	*infile_name;

	infile_name = get_infile_name(bash);
	if (infile_name == NULL)
		return (NULL);
	if (access(infile_name, F_OK) != 0)
		return ("");
	return (infile_name);*/
	return (NULL);
}

t_bool	execute_command(t_bash *bash)
{
	int		fdpipe[2];
	int		*childs;
	int		ret;
	int		i;
	char	*ret_file;
	//char	output[4096];

	bash->fdin_orig = dup(STDIN_FILENO);
	bash->fdout_orig = dup(STDOUT_FILENO);
	ret_file = check_infile(bash);
	if (ret_file != NULL && ft_strncmp(ret_file, "", 1) == 0)
		return (FALSE);
	if (ret_file != NULL)
	{
		printf("%s\n", ret_file);
		bash->fdin = open(ret_file, O_RDONLY);
	}
	else
		bash->fdin = dup(bash->fdin_orig);
	i = 0;
	childs = (int *) malloc(sizeof(int) * bash->nb_commands);
	if (childs == NULL)
		return (FALSE);
	while (i < bash->nb_commands)
	{
		dup2(bash->fdin, STDIN_FILENO);
		close(bash->fdin);
		if (i != bash->nb_commands - 1)
		{
			pipe(fdpipe);
			bash->fdout = fdpipe[1];
			bash->fdin = fdpipe[0];
		}
		else
			bash->fdout = dup(bash->fdout_orig);
		dup2(bash->fdout, STDOUT_FILENO);
		close(bash->fdout);
		ret = fork();
		childs[i] = ret;
		if (ret == 0)
		{
			if (bash->commands[i].exec_path == NULL)
				exit(1);
			execve(bash->commands[i].exec_path, bash->commands[i].args, \
					bash->envp);
			perror("Error Execution");
			exit(1);
		}
		i++;
	}
	i = -1;
	while (++i < bash->nb_commands)
		waitpid(childs[i], NULL, 0);
	dup2(bash->fdin_orig, 0);
	dup2(bash->fdout_orig, 1);
	close(bash->fdin_orig);
	close(bash->fdout_orig);
	free(ret_file);
	free(childs);
	return (TRUE);
}
