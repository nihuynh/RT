#!/bin/bash
curl -L https://www.libsdl.org/release/SDL2-2.0.9.tar.gz | tar xz
cd SDL-2.0.9
./configure
make
make install
cd ..
rm -rf SDL-2.0.9
echo "SDL2 install successful"
exit 0

