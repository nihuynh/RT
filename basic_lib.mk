# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    basic_lib.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/24 00:52:58 by nihuynh           #+#    #+#              #
#    Updated: 2019/05/24 03:55:46 by nihuynh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# This makefile will create the  build & clean rules for the libs in LIB_DEP.
# It also add the include path to INC.
# LIB_DEP is a list of path to library format like this : /path/lib*.a
# exemple : lib/libft/libft.a
# LIB_DEP_CLEAN is the target to clean the libs.

INC				+=	-I includes $(foreach word,$(LIB_DEP),-I $(dir $(word))includes)
LIB_LINK		:=	$(foreach word,$(LIB_DEP),-L $(dir $(word)) -l$(patsubst lib%.a,%,$(notdir $(word))))
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
