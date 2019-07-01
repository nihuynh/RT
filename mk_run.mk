# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_run.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/24 01:00:59 by nihuynh           #+#    #+#              #
#    Updated: 2019/07/01 21:07:20 by nihuynh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# This handle the make run.
# If the first argument is "run"...
ifeq (run,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif

SCENE		:=	playground
RUN_SCENE	:=	$(or $(RUN_ARGS),$(SCENE))
SCENES		:= 	$(addprefix $(addprefix scenes/, $(RUN_SCENE)), .rt)

run: all ## Run scenes from the scenes folder.
	@printf "\033[1;34m$(NAME)\033[25G\033[31mRunning $(SCENES) $(OKLOGO)"
	./$(NAME) $(SCENES)
.PHONY: run
