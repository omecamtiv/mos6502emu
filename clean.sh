#!/bin/sh

if [ -d ./.cache ]
then
	rm -r ./.cache
fi

if [ -d ./build ]
then
	rm -r ./build
fi
