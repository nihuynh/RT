# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    basic_lib.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/24 00:52:58 by nihuynh           #+#    #+#              #
#    Updated: 2019/05/24 01:06:41 by nihuynh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INC			+=	-I includes $(foreach word,$(LIB_DEP),-I $(dir $(word))includes)
LIB_LINK	:=	$(foreach word,$(LIB_DEP),-L $(dir $(word)) -l$(patsubst lib%.a,%,$(notdir $(word))))
LIB_DEP_CLEAN	:=  $(foreach word,$(LIB_DEP),$(patsubst %.a,%,$(word))_clean)
ifndef VERBOSE
LIBFLAGS 	:=	-j32 RUNMODE=$(RUNMODE)
else
LIBFLAGS 	:=	-j32 RUNMODE=$(RUNMODE) VERBOSE=$(VERBOSE)
endif
# **************************************************************************** #
# Libs links :
$(LIB_DEP):
	$(MAKE) -C $(dir $@) $(LIBFLAGS)
.PHONY: $(LIB_DEP)
$(LIB_DEP_CLEAN):
	$(MAKE) -C  $(dir $@) fclean $(LIBFLAGS)
.PHONY: $(LIB_DEP_CLEAN)
