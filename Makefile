NAME = so_long

B_NAME = so_long_bonus

SRCS = src/main.c src/map.c src/gameplay.c src/parse.c src/utils.c src/window.c lib/get_next_line/get_next_line.c

OBJS = $(SRCS:.c=.o)

B_SRCS = bonus/src/main_bonus.c bonus/src/map_bonus.c bonus/src/gameplay_bonus.c bonus/src/parse_bonus.c bonus/src/utils_bonus.c bonus/src/window_bonus.c \
		lib/get_next_line/get_next_line.c

B_OBJS = $(B_SRCS:.c=.o)

LIBRARY = -lmlx -framework OpenGL -framework AppKit

INC = includes/so_long.h includes/dictionnary.h

B_INC = bonus/includes/so_long_bonus.h bonus/includes/dictionnary_bonus.h

CFLAGS = -Wall -Wextra -Werror 

LIBFT = lib/libft/libft.a

FT_PRINTF = lib/ft_printf/libftprintf.a

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(FT_PRINTF)
	cc $(CFLAGS) $(OBJS) $(LIBFT) $(FT_PRINTF) $(LIBRARY) -o $(NAME)

%.o : %.c $(INC)
	cc $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C lib/libft/

$(FT_PRINTF):
	@make -C lib/ft_printf/

bonus: $(B_NAME)

$(B_NAME) : $(B_OBJS) $(LIBFT) $(FT_PRINTF) 
	cc $(CFLAGS) $(B_SRCS) $(LIBFT) $(FT_PRINTF) $(LIBRARY) -o $(B_NAME)

%_bonus.o : %_bonus.c $(B_INC)
	cc $(CFLAGS) -c $< -o $@

clean :
	@make clean -C lib/libft/
	@make clean -C lib/ft_printf/
	$(RM) $(OBJS) $(B_OBJS)

fclean : clean
	@make fclean -C lib/libft/
	@make fclean -C lib/ft_printf/
	$(RM) $(NAME) $(B_NAME)

re : fclean all
