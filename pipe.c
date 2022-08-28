/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:08 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/28 10:08:50 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
# define FD_READ 0
# define FD_WRITE 1

void	execute_tree(t_node *root, t_envp *env)
{
	if (root->type == LINE)
		make_process(root, env);
	//ㅇㅕ기서 heredoc이 있으면 먼저 실행
	else if (root->type == PIPE)
		execute_pipe(root, env);
	else{
		printf("wrong ast\n");
	}
}

//left right를 제대로 확인하고 진입할것
//만약에 left면, 
void	execute_pipe(t_node *root, t_envp *env)
{
	int	process;
	int	**fd;
	pid_t	*pid;
	int	i;

	process = count_process(root);
	fd = (int **)ft_calloc(sizeof(int *), process);
	if (fd == NULL)
		return ;
	i = 0;
	while (i < process)
	{
		fd[i] = (int *)ft_calloc(sizeof(int), 2);
		if (fd[i] == NULL)
			return ;
		i += 1;
	}
	pid = (pid_t *)ft_calloc(sizeof(pid_t), process);
	if (pid == NULL)
		return ;
	i = 0;
	while (root->type != PIPE)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			printf("error\n");
			return ;
		}
		if (pid[i])
		{
			if (root->left)
			{
				execute_process(root, env); // execute_line
			}
			//부모 프로세스
			if (root->right)
			{
				root = root->right;
				i += 1;
				continue ;
			}
			close(fd[i][FD_READ]);
			close(fd[i][FD_WRITE]);
			if (i == process - 1)
			{
				i = 0;
				while (i < process)
				{
					waitpid(pid[i], NULL, 0);
					i += 1;
				}
			}
		}
		else
		{
			if (i == 0)
			{
				close(fd[0][FD_READ]);
			}
			else{
				dup2(fd[i - 1][FD_READ], STDIN_FILENO);
			}
			if (root->right)
			{
				close(fd[i][FD_WRITE]);
			}
			else
			{
				dup2(fd[i][FD_WRITE], STDOUT_FILENO);
			}
			int j = 0;
			while (j < i)
			{
				close(fd[i][FD_READ]);
				close(fd[i][FD_WRITE]);
			}
			//자식 프로세스
			execute_function(root, env, 1);
		}
	}
	// if (root->type == LINE)
	// 	execute_line(root, env);
	// if (root->type == PIPE)
	// {
	// 	execute_pipe(root->left, env);
	// 	execute_pipe(root->right, env);
	// }
	// else{
	// 	printf("wrong ast2\n");
	// }
}


void	make_process(t_node *line, t_envp *env)
{
	int		fd[2];

	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	if (line->left)
		check_redirection(line->left, fd);
	if (line->right)
	{
		execute_function(line->right, env, 1);
	}
	else
		add_to_env("?=0", env, HIDE); //$?만 0으로 초기화
}

int	count_process(t_node *root)
{
	int	i;

	i = 1;
	while (root->type == PIPE)
	{
		i += 1;
		root = root->right;
	}
	return (i);
}

int	get_command_size(t_node *command)
{
	int	size;

	size = 0;
	while (command)
	{
		size += 1;
		command = command->right;
	}
	return (size);
}

char	**make_command_array(t_node *command)
{
	int		size;
	int		i;
	char	**command_array;

	size = get_command_size(command);
	command_array = (char **)ft_calloc(sizeof(char *), size + 1);
	if (command_array == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		command_array[i] = ft_strdup(command->str);
		if (command_array[i] == NULL)
		{
			free_double_array(command_array);
			return (NULL);
		}
		i += 1;
		command = command->right;
	}
	return (command_array);
}
