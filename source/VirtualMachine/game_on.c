/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_on.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:56:17 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/19 16:05:39 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/vrichese/Workspace/Rus42/Algorithms/Corewar/include/corewar.h"

void	reg_write(unsigned char *reg, void *data, int num_reg, int data_size)
{
	int iter;

	iter = REG_SIZE * num_reg;
	while (--iter >= REG_SIZE * (num_reg - 1))
		reg[iter] = ((unsigned char *)data)[--data_size];
}

void	reg_read(unsigned char *reg , int num_reg, unsigned char *where int data_location)
{
	int iter;

	iter = REG_SIZE * num_reg;
	while (--iter >= REG_SIZE * (num_reg - 1))
}

int get_waiting_time(int command)
{
	if (command == 0x01 || command == 0x04 || command == 0x05 || command == 0x0d)
		return (10);
	else if (command == 0x02 || command == 0x03)
		return (5);
	else if (command == 0x06 || command == 0x07 || command == 0x08)
		return (6);
	else if (command == 0x09)
		return (20);
	else if (command == 0x0a || command == 0x0b)
		return (25);
	else if (command == 0x0c)
		return (800);
	else if (command == 0x0e)
		return (50);
	else if (command == 0x0f)
		return (1000);
	else if (command == 0x10)
		return (2);
	return (0);
}

int				compute_sum(char target, int trim_byte)
{
	int total;
	int iter;

	total = 2;
	iter = 4;
	while (iter >= 0)
	{
		if (target & (REG_CODE << iter))
			total += 1;
		else if (target & (DIR_CODE << iter))
			trim_byte ? total += 2 : (total += 4);
		else if (target & (IND_CODE << iter))
			total += 2;
		iter -= 2;
	}
	return (total);
}

void	introduce_players(corewar_t *game)
{
	int iter;

	iter = 0;
	printf("Introducing contestants...\n");
	while (iter < game->players_amount)
	{
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\")\n",
		game->players[iter]->id, game->players[iter]->code_size,
		game->players[iter]->name, game->players[iter]->comment);
		++iter;
	}
}

int		get_reg(char data)
{
	return ((int)data);
}

int 	recomp_addr(arena_t *arena, int location)
{
	int total;
	int iter;

	total = 0;
	iter = 0;
	while (iter < 4)
	{
		total |= arena->field[location--] << (8 * iter);
		++iter;
	}
	return (total);
}

void	ld_exec(corewar_t *game)
{
	if (game->arena->field[game->carriages->current_location + 1] >> 4 == 2)
		reg_write(game->carriages->registers,
		game->arena->field[game->carriages->current_location + 5],
		get_reg(game->arena->field[game->carriages->current_location + 6]), 4);
	else if (game->arena->field[game->carriages->current_location + 1] >> 4 == 3)
		reg_write(game->carriages->registers,
		game->arena->field[game->carriages->current_location + recomp_addr(game->arena, game->carriages->current_location + 5) + 4],
		get_reg(game->arena->field[game->carriages->current_location + 6]), 4);
	else
		printf("Bug!\n");
}

void	st_exec(corewar_t *game)
{

}

void	start_execution(corewar_t *game)
{
	if (game->carriages->current_command == LIVE)
		printf("Live ");
	else if (game->carriages->current_command == LD)
		ld_exec(game);
	else if (game->carriages->current_command == ST)
		st_exec(game);
	else if (game->carriages->current_command == ADD)
		add_exec(game);
	else if (game->carriages->current_command == SUB)
		sub_exec(game);
	else if (game->carriages->current_command == AND)
		and_exec(game);
	else if (game->carriages->current_command == OR)
		or_exec(game);
	else if (game->carriages->current_command == XOR)
		xor_exec(game);
	else if (game->carriages->current_command == ZJMP)
		zjmp_exec(game);
	else if (game->carriages->current_command == LDI)
		ldi_exec(game);
	else if (game->carriages->current_command == STI)
		sti_exec(game);
	else if (game->carriages->current_command == FORK)
		fork_exec(game);
	else if (game->carriages->current_command == LLD)
		lld_exec(game);
	else if (game->carriages->current_command == LLDI)
		lldi_exec(game);
	else if (game->carriages->current_command == LFORK)
		lfork_exec(game);
	else if (game->carriages->current_command == AFF)
		aff_exec(game);
	else
		printf("%x ", game->carriages->current_command);
}

void	delete_carriage(corewar_t *game, carriage_t **tmp)
{
	if (game->carriages)
	{
		if (game->carriages->prev)
		{
			if (game->carriages->next)
			{
				game->carriages->prev->next = game->carriages->next;
				game->carriages->next->prev = game->carriages->prev;
				game->carriages = game->carriages->next;
			}
			else
				game->carriages->prev->next = NULL;
		}
		else
		{
			if (game->carriages->next)
			{
				game->carriages = game->carriages->next;
				game->carriages->prev = NULL;
				*tmp = game->carriages;
			}
			else
			{
				game->carriages = NULL;
				*tmp = NULL;
			}
		}
	}
}

int		here_we_go(corewar_t *game)
{
	carriage_t	*tmp;

	while (1)
	{
		tmp = game->carriages;
		if ((game->arena->loop_amount > 0 && game->arena->loop_amount % game->arena->cycle_to_die == 0) || game->arena->loop_amount <= 0)
		{
			while (game->carriages)
			{
				if (game->carriages->last_live_loop >= game->arena->cycle_to_die)
					delete_carriage(game, &tmp);
				if (game->arena->cycle_to_die <= 0)
					delete_carriage(game, &tmp);
				if (game->carriages)
					game->carriages = game->carriages->next;
			}
			if (game->arena->live_amount >= NBR_LIVE || game->arena->check_amount >= MAX_CHECKS)
			{
				game->arena->cycle_to_die -= CYCLE_DELTA;
				if (game->arena->check_amount >= MAX_CHECKS)
					game->arena->check_amount = 0;
				else
				{
					game->arena->live_amount = 0;
					game->arena->check_amount = 0;
				}
			}
			else
				game->arena->check_amount += 1;
			game->carriages = tmp;
		}
		while (game->carriages)
		{
			if (game->carriages->waiting_time == 0)
			{
				game->carriages->current_command = game->arena->field[game->carriages->current_location];
				game->carriages->waiting_time = get_waiting_time(game->carriages->current_command);
			}
			if (game->carriages->waiting_time > 0)
				game->carriages->waiting_time--;
			if (game->carriages->waiting_time == 0)
				start_execution(game);
			game->carriages = game->carriages->next;
		}
		usleep(100000);
		system("clear");
		print_arena(game);
		game->arena->loop_amount++;
		game->carriages = tmp;
		if (!game->carriages)
			break;
	}
	exit(1);
}