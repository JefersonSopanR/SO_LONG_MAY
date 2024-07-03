#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "../LIBFT/libft.h"
# include "../minilibx-linux/mlx.h"

# define    WIDTH   42
# define    HEIGHT  42

# define    WALL    '1'
# define    GRASS   '0'
# define    EXIT    'E'
# define    PLAYER  'P'
# define    COINS   'C'
# define	LAVA	'L'

# define    KEY_W   119
# define    KEY_A   97
# define    KEY_S   115
# define    KEY_D   100
# define	KEY_Q	113
# define	KEY_ESC	65307

# define    KEY_UP      65362
# define    KEY_LEFT    65361
# define    KEY_RIGHT   65363
# define    KEY_DOWN    65364

# define    FRONT   1
# define    LEFT    2
# define    RIGHT   3
# define    BACK    4

# define WALL_XPM			"sprites/wall.xpm"
# define GRASS_XPM			"sprites/grass.xpm"
# define COINS_XPM			"sprites/coin_dollar.xpm"
# define PLAYER_FRONT_XPM	"sprites/player/front-baby.xpm"
# define PLAYER_RIGHT_XPM	"sprites/player/left-baby.xpm"
# define PLAYER_LEFT_XPM	"sprites/player/right-baby.xpm"
# define PLAYER_BACK_XPM	"sprites/player/back-baby.xpm"
# define EXIT_OPEN_XPM		"sprites/door_open.xpm"
# define EXIT_CLOSE_XPM		"sprites/door_close.xpm"
# define LAVA_XPM			"sprites/enemy_bonus.xpm"

typedef	struct	s_state
{
	bool	exit;
	int		coins;
}		t_state;

typedef struct  s_position
{
    int y;
    int x;
}       t_position;

typedef struct  s_image
{
    void    *xpm_ptr;
    int     y;
    int     x;
}       t_image;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	char		**map_floodfill;
	int			close_game;
	int			columns;
	int			rows;
	int			players;
	int			coins;
	int			exits;
	int			movements;
	int			player_side;
    int			map_alloc;
	int			num_coins;
	t_image		wall;
	t_image		grass;
	t_image		img_coins;
	t_image		exit_open;
	t_image		exit_close;
	t_image		player_front;
	t_image		player_left;
	t_image		player_right;
	t_image		player_back;
	t_image		lava;
	t_position	player;
}		t_game;

void	ft_check_player_side(t_game *game, int y, int x);
int		ft_loss(t_game *game);
void    ft_check_arguments(int ac, char **av, t_game *game);
void    ft_init_map(t_game *game, char *av);
void    ft_check_empty_lines(t_game *game, char *map_line);
void    ft_init_vars(t_game *game);
void    ft_check_map(t_game *game, char *av);
void    ft_check_sorrounders(t_game *game);
void    ft_check_chr(t_game *game, char letter, int y, int x);
void    ft_check_characters(t_game *game);
void    ft_check_map_shape(t_game *game);
void    ft_check_valid_path(t_game *game, int fd);
void	free_floodfill(t_game *game);
int	ft_victory(t_game *game);
int	ft_close_game(t_game *game);
int	ft_error_game(char *msg, t_game *game);
void	ft_free_all_allocated_memory(t_game *game);
int	ft_handle_input(int keysym, t_game *game);
void	ft_move_player(t_game *game, int new_y, int new_x, int player_side);
void    ft_init_mlx(t_game *game);
void    ft_init_sprites(t_game *game);
t_image	ft_create_sprite(void *mlx_ptr, char *path, t_game *game);
int		ft_render_game(t_game *game);
void	ft_identify_sprite(t_game *game, char character, int y, int x);
void	ft_render_sprite(t_game *game, t_image sprite, int y, int x);

#endif
