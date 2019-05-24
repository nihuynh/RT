# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    basic_app.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/24 01:23:21 by nihuynh           #+#    #+#              #
#    Updated: 2019/05/24 03:55:38 by nihuynh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CONTENT_FILES	:=	./resources/built/Info.plist
RESRCS_FILES	:=	./resources/built/fe_icon.icns
CONTENT_BIN		:=  ./resources/materialList.csv 	\
					./resources/textures
WITH_THE_BIN	:=  ./scenes 						\
					./cimgui.dylib

aclean: ## Clean the app bundle.
	$(RM) -r built
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning $(NAME).app $(OKLOGO)"
.PHONY: aclean

built: $(NAME)  aclean ## Built the app bundle (Only on mac).
	mkdir -p "./built/$(NAME).app"/Contents/{MacOS,Resources} 2> /dev/null || true
	mkdir "./built/$(NAME).app"/Contents/MacOS/resources 2> /dev/null || true
	cp $(CONTENT_FILES) "./built/$(NAME).app/Contents/"
	cp $(RESRCS_FILES) "./built/$(NAME).app/Contents/Resources"
	cp -r $(CONTENT_BIN) "./built/$(NAME).app/Contents/MacOS/resources"
	cp -r $(WITH_THE_BIN) "./built/$(NAME).app/Contents/MacOS"
	cp ./$(NAME) "./built/$(NAME).app/Contents/MacOS/binary"
	@printf "\033[1;34m$(NAME)\033[25G\033[32mBuilt $(NAME).app $(OKLOGO)"
.PHONY: built
