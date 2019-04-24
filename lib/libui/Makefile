# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/27 19:33:22 by nihuynh           #+#    #+#              #
#    Updated: 2019/04/24 12:12:38 by sklepper         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libui.a
RUNMODE		?=	dev
SDL_SRC		:=	init_sdl.c error_sdl.c exit_sdl.c putcolor_sdl.c\
				render_sdl.c loop_sdl.c init_mthr_sdl.c render_mthr_sdl.c \
				save_screenshot.c render_fullscreen.c
SRC			:=	$(SDL_SRC)
# directories :
SRCDIR  	:=	srcs
OBJDIR 		:=	objs
INCDIR  	:=	includes
# LIBFT
LIBFT_NAME	:=	libft.a
LIBFT_PATH	:=	../libft
LFT_LIB	:=	-L $(LIBFT_PATH) -lft
LFT_INC	:=	-I $(LIBFT_PATH)/includes
# SDL
LSDL_LIB	:=	$(shell sdl2-config --libs)
LSDL_INC	:=	$(shell sdl2-config --cflags)
# IMGUI_IMPL
IMGUI_IMPL_NAME	:=	imgui_impl.a
IMGUI_IMPL_PATH	:=	../imgui_impl
IMGUI_IMPL_LIB	:=	-L $(IMGUI_IMPL_PATH) -limgui_impl
IMGUI_IMPL_INC	:=	-I $(IMGUI_IMPL_PATH)
IMGUI_IMPL_RULE	:=	$(IMGUI_IMPL_PATH)/$(IMGUI_IMPL_NAME)
# **************************************************************************** #
# make specs :
CC			:=	clang
CFLAGS		:=	-Werror -Wall -Wextra
CFLAGS		+=	-Wstrict-aliasing -pedantic -Wunreachable-code
ifeq ($(RUNMODE),dev)
    CFLAGS	+=	-g3 -O0
	# CFLAGS	+=	-Wpedantic -ggdb -fsanitize=address
else
	CFLAGS	+= -O2 -march=native -flto
endif
ifndef VERBOSE
.SILENT:
endif
RM			:=	/bin/rm -f
.SUFFIXES:
# **************************************************************************** #
# Automatic variable :
OBJ			:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEP			:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.d))
LIB			:=	$(LFT_LIB) $(LSDL_LIB) $(IMGUI_IMPL_LIB)
INC			:=	-I $(INCDIR) $(LFT_INC) $(LSDL_INC) $(IMGUI_IMPL_INC)
# **************************************************************************** #
OKLOGO		:=	\033[80G\033[32m[OK]\033[0m\n
GREP_ERR	:=	grep 'Error\|Warning' -C1 2> /dev/null || true
# **************************************************************************** #
# Rules :
all: $(NAME)
.PHONY: all
$(NAME): $(OBJ) $(LFT_RULE)
	ar rc $@ $(OBJ) && ranlib $@
	@printf "\033[1;34m$@\033[25G\033[32mBuilt $@ $(OKLOGO)\n"
-include $(DEP)
$(LFT_RULE):
	make -C $(LFT_PATH)/
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir $(OBJDIR) 2> /dev/null || true
	$(CC) $(CFLAGS) -MMD -MP -c -o $@ $< $(INC)
	@printf "\033[1;34m$(NAME)\033[25G\033[33mCompile $< $(OKLOGO)"
clean:
	$(RM) $(OBJ)
	$(RM) $(DEP)
	rmdir $(OBJDIR) 2> /dev/null || true
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning objs $(OKLOGO)"
.PHONY: clean
fclean: clean
	$(RM) $(NAME)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning $(NAME) $(OKLOGO)"
.PHONY: fclean
re: fclean all
.PHONY: re
test: all
	$(CC) $(CFLAGS) test_pool_render.c $(INC) $(LIB) libui.a
.PHONY: test
norme:
	norminette srcs includes | $(GREP_ERR)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mNorminette $(OKLOGO)"
.PHONY: norme
