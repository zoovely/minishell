/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:02:50 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/22 22:02:51 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "parse.h"
#include "builtin.h"
#include "pipe.h"

int main(int arc, char *argv[], char *envp[])
{
	print_start_shell();
	while(1) // 프롬프트 종료조건
	{
		print_prompt();
		get_commandline();
		run_commandline();//arguments : commands 
	}
}

void print_start_shell(void)
{
	printf("sojoo ====================================== and\n");
	printf("====================    ========================\n");
	printf("==================        ======================\n");
	printf("=================          =====================\n");
	printf("================            ====================\n");
	printf("===============              ===================\n");
	printf("===============    KINDER    ===================\n");
	printf("===============              ===================\n");
	printf("================            ====================\n");
	printf("=================          =====================\n");
	printf("heeskim's ============================ minishell\n");
}
