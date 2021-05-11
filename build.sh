#!/bin/sh

if [ ! -d ./build ]
then
	mkdir ./build
fi

cmake -H. -B build
