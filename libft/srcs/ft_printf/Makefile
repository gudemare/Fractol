# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/18 01:13:53 by gudemare          #+#    #+#              #
#    Updated: 2017/07/16 00:44:05 by gudemare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_printf.o

CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror

HEADERS_DIR	=	../../includes

SRCS_DIR	=	srcs/
SRCS_LIST	=	\
				conv_c.c \
				conv_d.c \
				conv_o.c \
				conv_p.c \
				conv_s.c \
				conv_u.c \
				conv_x.c \
				fill_spec.c \
				ft_anytoa.c \
				ft_get_args.c \
				ft_printf.c \
				ft_uanytoa.c \
				ft_uanytoa_base.c \
				handle_conv.c
SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR	=	./objs/
OBJS_LIST	=	$(patsubst %.c, %.o, $(SRCS_LIST))
OBJS		=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))

.PHONY : all clean fclean re debug debug_re

all: $(NAME)

$(NAME) : $(OBJS)
	@ld -r $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I $(HEADERS_DIR) -c $< -o $@

clean :
	@rm -rf $(NAME) $(OBJS_DIR)
fclean : clean

re: fclean all

debug : CFLAGS=-Wall -Wextra -g
debug : all

debug_re : fclean debug
