# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/27 19:33:22 by nihuynh           #+#    #+#              #
#    Updated: 2019/06/14 05:51:41 by sklepper         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	RT
RUNMODE		?=	release
# RUNMODE		?=	dev
#VERBOSE	:= TRUE

INTERFACE	:=	delete_obj.c screen_manager.c ui_lists.c ui_menu.c				\
				ui_objects.c ui_scene_editor.c ui_tools.c ui_csg.c				\
				interface.c new_object_tools.c new_object.c object_tools.c		\
				ui_cam_win.c ui_edit_win.c ui_file_win.c ui_render.c			\
				ui_selector.c ui_render_settings.c ui_anim_toolbox.c			\
				anim_toolbox.c ui_anim.c animate.c anim_set.c
PARSER		:=	export_csg.c export_shape.c export_toolbox.c export.c			\
				obj_data.c  obj_name.c parse_csg.c parse_shape.c parse_toolbox.c\
				parse_txt.c parse_utils.c parser.c read.c setter.c
RENDER		:=	camera.c cast.c filters.c light.c normal_mapping.c				\
				perturbation.c post_process.c render.c texture_loader.c			\
				texture_toolbox.c
RENDER_U	:=	init_sdl.c error_sdl.c exit_sdl.c render_sdl.c loop_sdl.c 		\
				init_mthr_sdl.c render_mthr_sdl.c save_screenshot.c				\
				render_pool.c render_time.c
TOOLS		:=	free_scene.c free.c utils.c get_scenes.c update.c reload.c		\
				load_tools.c hook.c free2.c list_toolbox.c
SRC			:=	 $(INTERFACE) $(PARSER) $(RENDER) $(RENDER_U) $(TOOLS)
SRC			+=	 main.c  key_mapping.c test.c
# directories :
VPATH		:=	./srcs ./srcs/parser ./srcs/render ./srcs/tools	\
				./srcs/interface ./srcs/render_utils

LIB_DEP		=	lib/libft/libft.a				\
				lib/librt/librt.a				\
				lib/cimgui/libcimgui.a			\
				lib/imgui_impl/libimgui_impl.a

# **************************************************************************** #
# Makefile dependency :
include basic.mk
include basic_lib.mk
include basic_runner.mk
include basic_app.mk
# **************************************************************************** #
# Additionnal linkers :
# SDL2
LIB_LINK	+=	$(shell sdl2-config --libs)  -lSDL2_Image
INC			+=	$(shell sdl2-config --cflags)
# Imgui
LIB_LINK	+=	-lstdc++ -framework OpenGl
BANNER		:=	$(shell cat resources/script/banner.txt)
# **************************************************************************** #
# Target rules :
.DEFAULT_GOAL := all
all: $(LIB_DEP) $(NAME)  ## Built the project.
.PHONY: all

$(NAME): $(OBJ) $(LIB_DEP)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(INC) $(LIB_LINK)
	@printf "\033[1;34m$(NAME)\033[25G\033[32mBuilt $@ $(OKLOGO)\n"
	@printf "$(BANNER)"
-include $(DEP)

fclean: $(LIB_DEP_CLEAN) clean dclean aclean ## Full clean of the project & the libs.
	$(RM) imgui.ini
	$(RM) $(NAME)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning $(NAME) $(OKLOGO)"
.PHONY: fclean

test: all ## This check the parsing on maps in the scenes dir.
	@for file in `LS scenes | grep .rt | sort -u`; \
		do echo $$file && ./RT scenes/$$file -t; done
.PHONY: test

doc: ## Generate documentation using doxygen.
	doxygen Doxyfile
	open docs/html/index.html
.PHONY: doc

dclean: ## Clean the documentation.
	$(RM) -r docs/html 2> /dev/null || true
	$(RM) -r docs/latex 2> /dev/null || true
.PHONY: dclean

norme: ## Check the norme of the project and the libraries.
	$(MAKE) -C lib/libft norme
	$(MAKE) -C lib/librt norme
	norminette srcs includes | $(GREP_ERR)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mNorminette $(OKLOGO)"
.PHONY: norme
