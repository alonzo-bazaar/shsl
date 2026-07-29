#!/usr/bin/env sh

# for when I fucked something up in shsl and thus cannot run make.shsl to
# recompile it 

# I'm kinda tired or rewriting this same command all the time so just made a
# script

# far from the being the most advanced shit out there, it's really just here to
# get me in a position where shsl can build itself again so I can continue
# development as normal

clang -Wall -Wextra -Wpedantic -Werror -g3 -ggdb -o shsl shsl.c
