# kBase for Apple II
This is a clone of dBase III+ written for the Apple II platform.

# How to build
This software was developed using cc65 (http://cc65.github.io/cc65/).  To build, you'll need this development tool and Java 1.4 or greater installed.  Java will have to be in your path.  You'll also need an environmental variable CC65BASE setup that points to the base directory of you cc65 install.

I did most of my development on Mac OS X, but if you're on Windows, you'll also need several Unix utilities installed, including Make, rm, and cp.  I would recommend installing Cygwin, which is what I use on Windows.

Once you have the above setup, you can build the project by simply typing "make" at the command-line in the root directory of the project.  This will generate a binary, kbase, and a disk image with the binary, kbase.po.  You can immediately load this up in an emulator and try it out by typing "-KBASE" at the command prompt once ProDos loads.

# TUI Lib
This project uses a library for text-based user interfaces called TUI Lib.  This library was developed by Tom Raidna and generously contributed for use in this project.  Copyright on the tuilibap.h, tuilibap.c, and tuiap3.c files below to him, and these files are used here with his permission.
