/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 23:31:59 by smorty            #+#    #+#             */
/*   Updated: 2019/09/24 23:31:41 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		*get_label_link(char *line)
{
	char	*link;
	size_t	size;

	size = 0;
	while (line[size] && line[size] != SEPARATOR_CHAR && !IS_BLANK(line[size]))
	{
		if (!ft_strchr(LABEL_CHARS, line[size]))
			error("Lexical error: wrong characters", 1);
		++size;
	}
	if (!size)
		error("Lexial error: empty label", 1);
	if (!(link = (char *)malloc(sizeof(char) * (size + 1))))
		error(strerror(errno), 0);
	link[size] = 0;
	while (size--)
		link[size] = line[size];
	return (link);
}

static int		get_registry_value(char *line)
{
	int val;

	if (!IS_DIGIT(*line))
		error("Syntax error: wrong registry value", 1);
	val = *line++ - 48;
	if (IS_DIGIT(*line))
		val = val * 10 + (*line++ - 48);
	++g_cur_col;
	if (!val || (*line && *line != SEPARATOR_CHAR && !IS_BLANK(*line)))
		error("Syntax error: wrong registry value", 1);
	return (val);
}

static void		get_parameter(t_opcode_param *param, char *line)
{
	if (*line == REGISTRY_CHAR)
	{
		param->type = crw_registry;
		param->value = get_registry_value(line + 1);
		return ;
	}
	if (*line == DIRECT_CHAR)
	{
		param->type = crw_direct;
		++line;
	}
	else if (*line == LABEL_CHAR || IS_DIGIT(*line) || *line == '-')
		param->type = crw_indirect;
	else
		error("Syntax error: wrong parameter type", 1);
	if (*line == LABEL_CHAR)
		param->link = get_label_link(line + 1);
	else
		param->value = ft_atoi(line);
}

t_opcode_param	*parse_parameter(char *line)
{
	t_opcode_param *param;

	param = NULL;
	if (*line)
	{
		if (!(param = (t_opcode_param *)malloc(sizeof(t_opcode_param))))
			error(strerror(errno), 0);
		param->value = 0;
		param->link = NULL;
		get_parameter(param, line);
	}
	return (param);
}
