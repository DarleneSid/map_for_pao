NAME	=	cub3D

DIR_SRCS		=	srcs

DIR_OBJS		=	objs

SRCS_NAMES		=	main.c \
					map.c \
					check_path.c \
					what_the_path.c \
					checking_borders.c \
					borders_utils.c \
					init_n_free.c \
					utils.c \
					floor_ceiling.c \
					check_invalid.c \
					fill_all.c \
					init_game.c \
					player.c \
					render.c \
					ft_raycasting.c \
					key_handler.c

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

DEPS			=	${SRCS_NAMES:.c=.d}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

INC				=	-Iincludes

LIB				=	-Llibft -lft -Lft_printf -lftprintf

LIBFT			=	libft.a

PRINTF			=	libftprintf.a

CC				=	cc

CDFLAGS 		=	-MMD -MP

MLX_FLAGS		=	-lm -lmlx -lXext -lX11

CFLAGS			=	-Wall -Werror -Wextra

all:	${NAME}

$(NAME): $(DIR_OBJS) $(OBJS) 
	make -C libft
	make -C ft_printf
	make -C mlx
	$(CC) -g3 ${INC} $(OBJS) $(LIB)  mlx/libmlx.a mlx/libmlx_Linux.a -L. -lXext -L. -lm -lX11 -o $(NAME)
	@echo "\033[31;5mcube3d\033[0m"

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	$(CC) -g3 $(CFLAGS) $(CDFLAGS) $(INC) -c $< -o $@ 

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

norm:
	norminette srcs/ includes/

clean:
	make clean -C mlx
	make clean -C libft
	make clean -C ft_printf
	rm -rf ${DIR_OBJS}

fclean:	clean
	make fclean -C libft
	make fclean -C ft_printf
	rm -rf ${LIBFT}
	rm -rf ${NAME}

re:	fclean all

-include $(DEPS)

.PHONY:	all clean fclean re

