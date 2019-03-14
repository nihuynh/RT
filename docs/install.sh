# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    install.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/30 21:38:06 by nihuynh           #+#    #+#              #
#    Updated: 2019/02/03 21:11:10 by nihuynh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# curl -fsSL https://raw.githubusercontent.com/nihuynh/RT/Nico/install.sh | sh

# Exit if any subcommand fails
set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NO_COLOR='\033[0m'
CLEAR_LINE='\r\033[K'
# **************************************************************************** #

CORE_DIR="$HOME/Master/TestRT/RT"
LIB_DIR="$HOME/Master/TestRT/lib"
RT_GIT="${CORE_DIR} https://github.com/nihuynh/RT.git"
LIB_GIT=(
	"${LIB_DIR}/libft https://github.com/nihuynh/Libft.git libft"
	"${LIB_DIR}/librt https://github.com/nihuynh/libvect.git librt"
	"${LIB_DIR}/libui https://github.com/nihuynh/libui.git libui"
	)
# **************************************************************************** #
check_lib ()
{
	for i in "${LIB_GIT[@]}"
	do
		DIRECTORY=$(echo $i | cut -d ' ' -f 1)
		REPO=$(echo $i | cut -d ' ' -f 2)
		LIB_NAME=$(echo $i | cut -d ' ' -f 3)
		if [ ! -d "$DIRECTORY" ]; then
  			printf "Installing $DIRECTORY\n"
			cd $LIB_DIR
			git clone $REPO $LIB_NAME
			cd -
		fi
	done
}
check_core ()
{
	REPO=$(echo $RT_GIT | cut -d ' ' -f 2)
   	DIRECTORY=$(echo $RT_GIT | cut -d ' ' -f 1)
	if [ ! -d "$DIRECTORY" ]; then
  		printf "Installing $DIRECTORY\n"
		cd $CORE_DIR
		git clone $REPO
		cd -
	fi
}
# **************************************************************************** #
if ! command -v sdl2-config --version > /dev/null; then
  printf "${CLEAR_LINE}💀${RED}   You must install SDL2 on your system before setup can continue${NO_COLOR}\n"
  printf "ℹ️   On macOS🍎 you should 'brew install SDL2'\n"
  exit -1
fi
if [ ! -d "$LIB_DIR" ]; then
  	printf "Creating the lib directory in $LIB_DIR\n"
	mkdir $LIB_DIR
fi
check_lib
check_core
# Create config.cfg
# Built the binary
# built the app
cd $CORE_DIR
make RUNMODE=release
printf "${CLEAR_LINE}${GREEN}   Finished!${NO_COLOR}\n"
