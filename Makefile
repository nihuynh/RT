# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/27 19:33:22 by nihuynh           #+#    #+#              #
#    Updated: 2019/05/24 02:13:43 by nihuynh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	RT
RUNMODE		?=	release
# RUNMODE		?=	dev
#VERBOSE	:= TRUE
SRC			:=	free_node.c main.c parser.c read.c render.c parse_toolbox.c	\
				setter.c light.c key_mapping.c camera.c update.c	\
				cast.c utils.c interface.c interface_scene.c	\
				interface_objects.c interface_tools.c	\
				object_tools.c texture_toolbox.c new_object_tools.c	\
				interface_lists.c filters.c export.c export_shape.c	\
				fullscreen.c export_toolbox.c new_object.c \
				reload.c perturbation.c texture_loader.c free.c csg.c  \
				obj_data.c parse_txt.c parse_utils.c interface_menu.c \
				ui_file_win.c ui_edit_win.c ui_render.c parse_csg.c \
				export_csg.c get_scenes.c test.c
SRC			+=	init_sdl.c error_sdl.c exit_sdl.c \
				render_sdl.c loop_sdl.c init_mthr_sdl.c render_mthr_sdl.c \
				save_screenshot.c render_pool.c post_process.c render_time.c
# directories :
VPATH       :=	./srcs ./srcs/parser ./srcs/render ./srcs/tools	\
				./srcs/interface ./srcs/render_utils

LIB_DEP		=	lib/libft/libft.a	\
				lib/librt/librt.a		\
				lib/imgui_impl/libimgui_impl.a

# **************************************************************************** #
# Makefile dependency :
include basic.mk
include basic_lib.mk
include basic_runner.mk
include basic_app.mk
# **************************************************************************** #
# Additionnal linkers :
ifeq ($(shell uname -s), Linux)
	CIMGUI_NAME = cimgui.so
endif
ifeq ($(shell uname -s), Darwin)
	CIMGUI_NAME = cimgui.dylib
endif
CIMGUI_PATH :=	lib/cimgui

# **************************************************************************** #
# Additionnal linkers :
# SDL
LIB_LINK	+=	$(shell sdl2-config --libs)  -lSDL2_Image
INC			+=	$(shell sdl2-config --cflags)
INC			+=	-I $(CIMGUI_PATH)
LIB_LINK	+=	$(CIMGUI_NAME) -lstdc++ -framework OpenGl
BANNER		:=	$(shell cat resources/script/banner.txt)
# **************************************************************************** #
# Target rules :
.DEFAULT_GOAL := all
all: $(CIMGUI_NAME) $(LIB_DEP) $(NAME)## Built the project (Default goal).
.PHONY: all
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(INC) $(LIB_LINK)
	@printf "\033[1;34m$(NAME)\033[25G\033[32mBuilt $@ $(OKLOGO)\n"
	@printf "$(BANNER)"
-include $(DEP)
$(CIMGUI_NAME):
	$(MAKE) -sC $(CIMGUI_PATH)
	cp $(CIMGUI_PATH)/$(CIMGUI_NAME) .
dclean: ## Clean of the documentation.
	$(RM) -r docs/html 2> /dev/null || true
	$(RM) -r docs/latex 2> /dev/null || true
.PHONY: dclean
fclean: $(LIB_DEP_CLEAN) clean dclean aclean ## Full clean of the directory & the libs.
	$(RM) $(NAME)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning $(NAME) $(OKLOGO)"
.PHONY: fclean
doc: ## Generate a documentation using doxygen.
	doxygen Doxyfile
	open docs/html/index.html
.PHONY: doc
test: all ## This check the parsing on all the map in the scenes directory.
	@for file in `LS scenes | grep .rt | sort -u`; \
		do echo $$file && ./RT scenes/$$file -t; done
.PHONY: test
norme: ## Check the norme of the project and the libraries.
	$(MAKE) -C $(LFT_PATH) norme
	$(MAKE) -C $(LRT_PATH) norme
	norminette srcs includes | $(GREP_ERR)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mNorminette $(OKLOGO)"
.PHONY: norme
