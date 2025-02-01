#!/bin/bash
#unix compile and run scripts

if [ $# -ne 1 ]; then
	echo "SCRIPTI ASAGIDAKI GIBI KULLANIN"
	echo "./cr-UNIX.sh ARGUMAN"
	echo "ARGUMANLAR:"
	echo "compile veya c"
	echo "run veya r"


elif [ "$1" == "compile" ] || [ "$1" == "c" ]; then
	clear
	echo "::UNIX COMPILE STARTED::"
	rm -rf build
	mkdir build
	cp settings.cfg build
	cd build
	cmake ..
	make
	echo "::UNIX COMPILE FINISHED::"

elif [ "$1" == "run" ] || [ "$1" == "r" ]; then
	echo "::UNIX RUN::"
	cd build
	./MC_RCON_CLIENT
fi
