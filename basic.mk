# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    basic.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/23 23:30:21 by nihuynh           #+#    #+#              #
#    Updated: 2019/05/24 08:03:49 by nihuynh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJDIR 		:=	objs
INCDIR  	:=	includes

OBJ			:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEP			:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.d))
INC			:=	-I includes
# **************************************************************************** #
OKLOGO		:=	\033[80G\033[32m[OK]\033[0m\n
GREP_ERR	:=	grep 'Error\|Warning' -C1 2> /dev/null || true
PHELP		:=	"\033[36m%-26s\033[0m %s\n"
RM			:=	/bin/rm -f
.SUFFIXES:
# **************************************************************************** #
# Compile custom :
CC			:=	clang
CFLAGS		:=	-Werror -Wall -Wextra
CFLAGS		+=	-Wstrict-aliasing -pedantic -Wunreachable-code
ifndef VERBOSE
.SILENT:
endif
ifeq ($(RUNMODE),dev)
    CFLAGS	+=	-g3 -O0
    # CFLAGS	+=	-fsanitize=thread
	CFLAGS	+=	-fsanitize=address -fsanitize-recover=address
else
	CFLAGS	+= -O2 -march=native -flto
endif
$(OBJDIR)/%.o: %.c
	mkdir $(OBJDIR) 2> /dev/null || true
	$(CC) $(CFLAGS) -MMD -MP -c -o $@ $< $(INC)
	@printf "\033[1;34m$(NAME)\033[25G\033[33mCompile $< $(OKLOGO)"
# **************************************************************************** #
usage: ## Print out on how to use this Makefile.
	@printf "\n$(NAME)\n  Usage:\n\tmake <target>\n\n  Targets:\n"
	@fgrep -h " ## " $(MAKEFILE_LIST) \
	| fgrep -v fgrep | awk 'BEGIN {FS = ":.*?## "}; {printf $(PHELP), $$1, $$2}'
	@printf "\n  Scenes:\n"
	@for file in `LS scenes | grep .rt | sort -u | cut -d . -f 1`; \
		do printf "make run $$file \n"; done
.PHONY: usage

clean:  ## Clean of the project directory (.o & .d).
	$(RM) $(OBJ)
	$(RM) $(DEP)
	$(RM) -r $(OBJDIR)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning objs $(OKLOGO)"
.PHONY: clean

re: ## Rebuild the project.
	make fclean
	make all
.PHONY: re
