/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:59:12 by aen-naas          #+#    #+#             */
/*   Updated: 2023/05/14 18:09:24 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_status()
{
    int status = exit_s;
    if (WIFEXITED(status)) {
        status = WEXITSTATUS(status);
        // printf("Exit status was %d\n", status);
    }
	else if (WIFSIGNALED(status)) 
	{
        // puts("---");
        status = WIFSIGNALED(status) + 128;
        // printf("Child process terminated by signal %d\n", status);
    }
    exit_s = status;
	// if (WIFEXITED(status)) 
	// {
    //     status = WEXITSTATUS(status);
    //     printf("Child process exited normally with status %d\n", status);
    // } 
}