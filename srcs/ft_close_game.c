#include "so_long.h"

int	ft_victory(t_game *game)
{
	ft_printf("Congratulations!\nYou won with %d Moves\n", ++game->movements);
	ft_free_all_allocated_memory(game);
	exit (EXIT_FAILURE);
}

int	ft_close_game(t_game *game)
{
	if (!game->close_game)
		ft_printf("Movements: %d\n", game->movements);
	ft_free_all_allocated_memory(game);
	ft_printf("GAME CLOSED\n");
	exit (EXIT_FAILURE);
}

int	ft_error_game(char *msg, t_game *game)
{
    int i;

    i = 0;
	if (game->map_alloc == 1)
	{
        while (i < game->rows)
		    free(game->map[i++]);
	    free(game->map);
    }
	free(game);
	ft_printf("Error\n""%s\n", msg);
	exit (EXIT_FAILURE);
}

void	ft_free_all_allocated_memory(t_game *game)
{
    int i;

    i = 0;
    while (i < game->rows)
		free(game->map[i++]);
	free(game->map);
	mlx_destroy_image(game->mlx_ptr, game->wall.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->grass.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_coins.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_front.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_left.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_right.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_back.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->exit_close.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->exit_open.xpm_ptr);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	free(game);
}
