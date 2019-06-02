#!/bin/sh
curl -L https://www.libsdl.org/release/SDL2-2.0.9.tar.gz | tar xz
cd SDL2-2.0.9
./configure
make
make install
cd ..
rm -rf SDL2-2.0.9
echo "SDL2 install successful"

curl -L https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.4.tar.gz | tar xz
cd SDL2_image-2.0.4
./configure
make
make install
cd ..
rm -rf SDL2_image-2.0.4
echo "SDL2_image install successful"

exit 0
