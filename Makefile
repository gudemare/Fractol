# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/18 01:13:53 by gudemare          #+#    #+#              #
#    Updated: 2017/08/25 00:33:38 by gudemare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	fractol

#==============================================================================#
#                            Compilation parameters                            #
#==============================================================================#

CC				=	clang
CFLAGS			=	-Wall -Wextra#-Werror

LIBS			=	libft,mlx
LIBFT_DIR		=	libft
MLX_DIR			=	minilibx_macos

HEADERS_LIB		=	libft/includes
HEADERS_DIR		=	includes/
HFLAGS			=	-I $(HEADERS_DIR) -I $(HEADERS_LIB) -I $(MLX_DIR)

LFLAGS			=	-lft -L$(LIBFT_DIR) -lmlx -framework OpenGL -framework AppKit -L$(MLX_DIR) -lm
SRCS_DIR		=	srcs/
SRCS_LIST		=	\
					draw_utils.c \
					fractals.c \
					loop_hook.c \
					key_hooks.c \
					main.c
SRCS			=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR		=	./objs/
OBJS_LIST		=	$(patsubst %.c, %.o, $(SRCS_LIST))
OBJS			=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))

#==============================================================================#
#                             Colors Escape Codes                              #
#==============================================================================#

END_GRAPHICS	=	\e[0m
BOLD			=	\e[1m
DARK			=	\e[2m
ITALIC			=	\e[3m
UNDERSCORE		=	\e[4m
REVERSE_VID		=	\e[7m
BLACK			=	\e[30m
RED				=	\e[31m
GREEN			=	\e[32m
YELLOW			=	\e[33m
BLUE			=	\e[34m
MAGENTA			=	\e[35m
CYAN			=	\e[36m
WHITE			=	\e[37m
BLACK_BG		=	\e[40m
RED_BG			=	\e[41m
GREEN_BG		=	\e[42m
YELLOW_BG		=	\e[43m
BLUE_BG			=	\e[44m
MAGENTA_BG		=	\e[45m
CYAN_BG			=	\e[46m
WHITE_BG		=	\e[47m

#==============================================================================#
#                                 Instructions                                 #
#==============================================================================#

.PHONY : all norme clean fclean re debug debug_lib debug_re project_re $(LIBS) $(SUBPROJECTS)

all: $(NAME)
	@printf "$(MAGENTA)WARNING : -Werror is disabled.\n$(END_GRAPHICS)"

$(NAME) : $(LIBS) $(OBJS)
	@$(CC) $(CFLAGS) $(HFLAGS) $(LFLAGS) $(OBJS) -o $(NAME)
	@printf "$(GREEN)The program $(BOLD)$(NAME)$(END_GRAPHICS)$(GREEN) has successfully compiled.$(END_GRAPHICS)\n"

$(LIBS) :
	@printf "\e[K$(CYAN)Compiling $(BOLD)MLX$(END_GRAPHICS)$(CYAN) ...\n\e[A$(END_GRAPHICS)"
	@make -C $(MLX_DIR) -j8 &>/dev/null
	@printf "$(GREEN)Library $(BOLD)MLX$(END_GRAPHICS)$(GREEN) successfully compiled.$(END_GRAPHICS)\n"
	@printf "\e[K$(CYAN)Compiling $(BOLD)libft$(END_GRAPHICS)$(CYAN) ...\n\e[A$(END_GRAPHICS)"
	@make -C $(LIBFT_DIR) -j8 &>/dev/null
	@printf "$(GREEN)Library $(BOLD)libft$(END_GRAPHICS)$(GREEN) successfully compiled.$(END_GRAPHICS)\n"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@printf "\e[K$(CYAN)Compiling $(BOLD)$(notdir $<)$(END_GRAPHICS)$(CYAN) ...\n\e[A$(END_GRAPHICS)"
	@$(CC) $(CFLAGS) $(HFLAGS) -c $< -o $@

norme :
	@if type "norminette" &> /dev/null ; then\
		printf "$(YELLOW)Checking Norm ...\n$(END_GRAPHICS)" && \
		norminette **/*.[ch] | grep -v -B 1 "^Norme: " || printf "$(GREEN)Norme OK.\n" ; \
	else\
		printf "$(RED)Norminette not installed, not checking norm.$(END_GRAPHICS)\n";\
	fi

clean :
	@rm -rf $(OBJS_DIR)
	@make -C $(LIBFT_DIR) clean 1>/dev/null
	@make -C $(MLX_DIR) clean 1>/dev/null
	@printf "$(BOLD)$(YELLOW)$(NAME)$(END_GRAPHICS)$(YELLOW)'s objects files have been removed.$(END_GRAPHICS)\n"
fclean :
	@rm -rf $(NAME) $(OBJS_DIR)
	@make -C $(LIBFT_DIR) fclean 1>/dev/null
	@make -C $(MLX_DIR) clean 1>/dev/null
	@printf "$(YELLOW)The program $(BOLD)$(NAME)$(END_GRAPHICS)$(YELLOW) and its projects files have been removed.$(END_GRAPHICS)\n"

re: fclean all

project_re:
	@rm -rf $(OBJS_DIR) $(NAME)
	@make

debug_lib :
	@make -C $(LIBFT_DIR) -j8 debug

debug : CFLAGS=-Wall -Wextra -fsanitize=address -g
debug : debug_lib all
	@printf "\e[K$(GREEN)The program $(BOLD)$(NAME)$(END_GRAPHICS)$(GREEN) has successfully compiled $(YELLOW)(with debug symbols).$(END_GRAPHICS)\n"

debug_re : fclean debug
