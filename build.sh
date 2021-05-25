#!/data/data/com.termux/files/usr/bin/sh

if [ ! -d ./build ]
then
	mkdir ./build
fi

cmake -DCURSES_LIBRARY=/data/data/com.termux/files/usr/lib/libncurses.so -DCURSES_INCLUDE_PATH=/data/data/com.termux/files/usr/include -H. -B build
