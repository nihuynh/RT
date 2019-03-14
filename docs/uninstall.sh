# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    uninstall.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/30 21:46:24 by nihuynh           #+#    #+#              #
#    Updated: 2019/01/30 21:49:04 by nihuynh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

read -r -p "Are you sure you want to remove RT? [y/N] " confirmation
if [ "$confirmation" != y ] && [ "$confirmation" != Y ]; then
  echo "Uninstall cancelled"
  exit
fi

echo "Removing libft"
if [ -d ../lib/libft ]; then
  rm -rf ../lib/libft
fi

echo "Removing librt"
if [ -d ../lib/librt ]; then
  rm -rf ../lib/librt
fi

echo "Removing libui"
if [ -d ../lib/libui ]; then
  rm -rf ../lib/libui
fi

echo "Removing RT"
if [ -d ../RT ]; then
  rm -rf ../RT
fi