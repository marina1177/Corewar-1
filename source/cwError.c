/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwError.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 16:00:50 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/02 19:50:53 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cwErrorCatcher(int error_code, const char *section)
{
	printf("Error --- %s\n", section);
	exit(-1);
}