/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:05:20 by gletilly          #+#    #+#             */
/*   Updated: 2025/06/10 06:56:44 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

int	ft_pwd(bool print)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * 1024);
	if (getcwd(buffer, 1024) == NULL)
		perror("pwd error");
	else
	{
		if (print)
			printf("%s\n", buffer);
	}
	free(buffer);
	return (0);
}
