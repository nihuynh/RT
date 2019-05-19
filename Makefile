# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/27 19:33:22 by nihuynh           #+#    #+#              #
#    Updated: 2019/05/19 23:05:04 by nihuynh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	RT
RUNMODE		?=	release
# RUNMODE		?=	dev
#VERBOSE	:= TRUE
SCENE		:=	playground
SRC			:=	error.c main.c parser.c read.c render.c parse_toolbox.c	\
				setter.c light.c key_mapping.c camera.c update.c	\
				cast.c utils.c interface.c interface_scene.c	\
				interface_objects.c interface_tools.c	\
				object_tools.c texture_toolbox.c new_object_tools.c	\
				interface_lists.c filters.c export.c export_utils.c	\
				fullscreen.c export_toolbox.c new_object.c \
				reload.c perturbation.c texture_loader.c free.c csg.c  \
				obj_data.c parse_txt.c parse_utils.c \
				ui_hook_file_mng.c ui_hook_obj_mng.c ui_hook_render.c
SRC			+=	init_sdl.c error_sdl.c exit_sdl.c \
				render_sdl.c loop_sdl.c init_mthr_sdl.c render_mthr_sdl.c \
				save_screenshot.c render_pool.c post_process.c render_time.c
# directories :
VPATH       :=	./srcs ./srcs/parser ./srcs/render ./srcs/tools	\
				./srcs/interface ./srcs/render_utils
OBJDIR 		:=	objs
INCDIR  	:=	includes
# LIBFT
LFT_NAME	:=	libft.a
LFT_PATH	:=	lib/libft
LFT_LIB		:=	-L $(LFT_PATH) -lft
LFT_INC		:=	-I $(LFT_PATH)/includes
LFT_RULE	:=	$(LFT_PATH)/$(LFT_NAME)
# LIBRT
LRT_NAME	:=	librt.a
LRT_PATH	:=	lib/librt
LRT_LIB		:=	-L $(LRT_PATH) -lrt
LRT_INC		:=	-I $(LRT_PATH)/includes
LRT_RULE	:=	$(LRT_PATH)/$(LRT_NAME)
# SDL
LSDL_LIB	:=	$(shell sdl2-config --libs)
LSDL_INC	:=	$(shell sdl2-config --cflags)
# CIMGUI
UNAME_S		:=	$(shell uname -s)
ifeq ($(UNAME_S), Linux)
	CIMGUI_NAME = cimgui.so
endif
ifeq ($(UNAME_S), Darwin)
	CIMGUI_NAME = cimgui.dylib
endif
CIMGUI_PATH :=	lib/cimgui
CIMGUI_LIB	:=	$(CIMGUI_NAME) -lstdc++
CIMGUI_INC	:=	-I $(CIMGUI_PATH)
CIMGUI_RULE	:=	$(CIMGUI_NAME)
# IMGUI_IMPL
IMGUI_IMPL_NAME	:= libimgui_impl.a
IMGUI_IMPL_PATH	:= lib/imgui_impl
IMGUI_IMPL_LIB	:= -L $(IMGUI_IMPL_PATH) -limgui_impl
IMGUI_IMPL_INC	:= -I $(IMGUI_IMPL_PATH)
IMGUI_IMPL_RULE	:= $(IMGUI_IMPL_PATH)/$(IMGUI_IMPL_NAME)
# OPENGL
LOPENGL_LIB	:= -framework OpenGl
# **************************************************************************** #
# Automatic variable :
# If the first argument is "run"...
ifeq (run,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif
RUN_SCENE	:=	$(or $(RUN_ARGS),$(SCENE))
SCENES		:= 	$(addprefix $(addprefix scenes/, $(RUN_SCENE)), .rt)
OBJ			:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEP			:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.d))
LIB			:=	$(LFT_LIB) $(LRT_LIB) $(LSDL_LIB) $(CIMGUI_LIB)	\
				$(IMGUI_IMPL_LIB) $(LOPENGL_LIB)
INC			:=	-I $(INCDIR) $(LFT_INC) $(LSDL_INC) $(LRT_INC)	\
				$(CIMGUI_INC) $(IMGUI_IMPL_INC)
# **************************************************************************** #
# make specs :
CC			:=	clang
CFLAGS		:=	-Werror -Wall -Wextra -g -I$(INCDIR)
CFLAGS		+=	-Wstrict-aliasing -pedantic -Wunreachable-code
LIBFLAGS 	:=	-j32 RUNMODE=$(RUNMODE)
ifeq ($(RUNMODE),dev)
    CFLAGS	+=	-g3 -O0
	# CFLAGS	+=	-Wpedantic -ggdb -fsanitize=address -fsanitize-recover=address
else
	CFLAGS	+= -O2 -march=native -flto
endif
ifndef VERBOSE
.SILENT:
endif
RM			:=	/bin/rm -f
.SUFFIXES:
# **************************************************************************** #
OKLOGO		:=	\033[80G\033[32m[OK]\033[0m\n
GREP_ERR	:=	grep 'Error\|Warning' -C1 2> /dev/null || true
PHELP		:=	"\033[36m%-26s\033[0m %s\n"
# **************************************************************************** #
# Target rules :
.DEFAULT_GOAL := all
all: lib $(NAME) ## Built the project (Default goal).
.PHONY: all
$(NAME): $(OBJ) $(LFT_RULE) $(LRT_RULE) $(CIMGUI_RULE) $(IMGUI_IMPL_RULE)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(INC) $(LIB)
	@printf "\033[1;34m$(NAME)\033[25G\033[32mBuilt $@ $(OKLOGO)\n"
-include $(DEP)
$(LFT_RULE):
	$(MAKE) -sC $(LFT_PATH) $(LIBFLAGS)
$(LRT_RULE):
	$(MAKE) -sC $(LRT_PATH) $(LIBFLAGS)
$(CIMGUI_RULE):
	$(MAKE) -sC $(CIMGUI_PATH)
	cp $(CIMGUI_PATH)/$(CIMGUI_NAME) .
$(IMGUI_IMPL_RULE):
	$(MAKE) -sC $(IMGUI_IMPL_PATH) $(LIBFLAGS)
$(OBJDIR)/%.o: %.c
	mkdir $(OBJDIR) 2> /dev/null || true
	$(CC) $(CFLAGS) -MMD -MP -c -o $@ $< $(INC)
	@printf "\033[1;34m$(NAME)\033[25G\033[33mCompile $< $(OKLOGO)"
lib: ## Built the libraries.
	$(MAKE) -sC $(LFT_PATH) $(LIBFLAGS)
	$(MAKE) -sC $(LRT_PATH) $(LIBFLAGS)
	$(MAKE) -sC $(IMGUI_IMPL_PATH) $(LIBFLAGS)
.PHONY: lib
clean:  ## Clean of the project directory (.o & .d).
	$(RM) $(OBJ)
	$(RM) $(DEP)
	$(RM) -r $(OBJDIR) 2> /dev/null || true
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning objs $(OKLOGO)"
.PHONY: clean
lclean: ## Clean of the library.
	$(MAKE) -C $(LFT_PATH)/ fclean
	$(MAKE) -C $(LRT_PATH)/ fclean
	$(MAKE) -C $(IMGUI_IMPL_PATH)/ fclean
	$(RM) $(CIMGUI_NAME)
.PHONY: lclean
dclean: ## Clean of the documentation.
	$(RM) -r docs/html 2> /dev/null || true
	$(RM) -r docs/latex 2> /dev/null || true
.PHONY: dclean
fclean: clean lclean dclean ## Full clean of the directory & the libs.
	$(RM) $(NAME)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning $(NAME) $(OKLOGO)"
.PHONY: fclean
re: ## Rebuild the project.
	make fclean
	make all
.PHONY: re
run: all ## Run scenes from the scenes folder.
	@printf "\033[1;34m$(NAME)\033[25G\033[31mRunning $(SCENES) $(OKLOGO)"
	./$(NAME) $(SCENES)
.PHONY: run
usage: ## Print out on how to use this Makefile.
	@printf "\n$(NAME)\n  Usage:\n\tmake <target>\n\n  Targets:\n"
	@fgrep -h " ## " $(MAKEFILE_LIST) \
	| fgrep -v fgrep | awk 'BEGIN {FS = ":.*?## "}; {printf $(PHELP), $$1, $$2}'
	@printf "\n  Scenes:\n"
	@for file in `LS scenes | grep .rt | sort -u | cut -d . -f 1`; \
		do printf "make run $$file \n"; done
.PHONY: usage
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
