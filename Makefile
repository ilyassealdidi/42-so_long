NAME = so_long
B_NAME = so_long_bonus
SRCS = $(shell find src -name "*.c") lib/get_next_line/get_next_line.c
OBJS = $(SRCS:.c=.o)
B_SRCS = $(shell find bonus/src -name "*.c") lib/get_next_line/get_next_line.c
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

%_bonus.o : %_bonus.c $(B_INC)
	cc $(CFLAGS) -c $< -o $@

%.o : %.c $(INC)
	cc $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C lib/libft/

$(FT_PRINTF):
	@make -C lib/ft_printf/

bonus: $(B_NAME)

$(B_NAME) : $(B_OBJS) $(LIBFT) $(FT_PRINTF) 
	cc $(CFLAGS) $(B_SRCS) $(LIBFT) $(FT_PRINTF) $(LIBRARY) -o $(B_NAME)

clean :
	@make clean -C lib/libft/
	@make clean -C lib/ft_printf/
	$(RM) $(OBJS) $(B_OBJS)

fclean : clean
	@make fclean -C lib/libft/
	@make fclean -C lib/ft_printf/
	$(RM) $(NAME) $(B_NAME)

re : fclean all

run : re
	@if [ -f maps/map.ber ]; then \
		./so_long maps/map.ber; echo ""; \
	else \
		echo "Missing file: maps/map.ber"; \
	fi

run_bonus : fclean bonus
	@if [ -f maps/map_bonus.ber ]; then \
		./so_long_bonus maps/map_bonus.ber; echo ""; \
	else \
		echo "Missing file: maps/map_bonus.ber"; \
	fi
