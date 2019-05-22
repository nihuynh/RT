

# RT
[![Build Status](https://travis-ci.com/nihuynh/RT.svg?token=PdGtpZGzFKLd1CBjD7Ym&branch=master)](https://travis-ci.com/nihuynh/RT)

---

## Summary
_This is a ray tracing program using SDL2 and imgui._
_Built and tested on mac OSX 10, (Untested on linux)_

## How to install

On mac, this command will built an binary:
```
git clone --recurse-submodules https://github.com/nihuynh/RT && cd RT && make
```

## How to use

### Keymap :

<kbd>ESC</kbd> | Quit the program

---

# Features:

* Refraction (Glass)
* Reflection (Mirror)
* Controllable camera
* Screenshot
* Edit or create scenes
* Load/Reload/Export scenes
  Under and over-sampling
* UI pane to edit or create scenes
* Fullscreen
* Texture on all basic shapes

# In-progress Features:
* sky-box
* CSG

# TODO Features:
* Disk
* Triangle
* Tore
* Better material list

# Shape availables:
* Plane
* Cube
* Sphere
* Cylinder
* Cone

# Dev_log:

cloc lib/lib* srcs includes Makefile
17 march => 6261	LOC
12 april => 5363	LOC
22 mai => 7620		LOC
pmc to mesure the cache misses

