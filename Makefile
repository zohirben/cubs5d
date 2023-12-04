SRC_MAIN = main.c drawing/check.c drawing/dda.c drawing/draw.c drawing/render.c \
	parsing/check_map.c parsing/check_textures.c parsing/check_rgb.c parsing/ft_rgb_insert.c parsing/ft_rgb_c_insert.c \
	textures/draw_textures.c textures/textures_move.c parsing/check_walls.c parsing/check_elements.c  parsing/begin_text.c\
	parsing/ft_separate_map.c parsing/fill.c \

SRC_BONUS = main_bonus.c drawing/check.c drawing/dda.c drawing/draw.c drawing/render.c \
	parsing/check_map.c parsing/check_textures.c parsing/check_rgb.c parsing/ft_rgb_insert.c parsing/ft_rgb_c_insert.c \
	textures/draw_textures.c textures/textures_move.c parsing/check_walls.c parsing/check_elements.c parsing/begin_text.c \
	parsing/ft_separate_map.c parsing/fill.c \

NAME = cub3d
NAME_BONUS = cub3d_bonus
CC = cc
CFLAGS =
RM = rm -rf
INCLUDES = -Iinclude ./MLX42/libmlx42.a -lglfw -L"/Users/sbellafr/.brew/opt/glfw/lib"

.SILENT:

all: $(NAME)
	@echo "\033[104mThe mandatory part is made\033[0m"

bonus: $(SRC_BONUS)
	make  -C libft
	$(CC) -Ilibft $(INCLUDES) -framework Cocoa -framework OpenGL -framework IOKit $(CFLAGS) ./libft/libft.a $(SRC_BONUS) -o $(NAME_BONUS)

$(NAME): $(SRC_MAIN)
	make  -C libft
	$(CC) -Ilibft $(INCLUDES) -framework Cocoa -framework OpenGL -framework IOKit $(CFLAGS) ./libft/libft.a $(SRC_MAIN) -o $(NAME)

%.o: %.c
	$(CC) -Ilibft $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS) 
	make fclean  -C libft

re: fclean all
