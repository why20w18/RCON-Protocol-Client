#!/bin/bash
#unix compile and run scripts

if [ $# -ne 1 ]; then
	echo "SCRIPTI ASAGIDAKI GIBI KULLANIN"
	echo "./cr-UNIX.sh ARGUMAN"
	echo "ARGUMANLAR:"
	echo "compile veya c"
	echo "run veya r"
	echo "debug-compile veya dc"


elif [ "$1" == "compile" ] || [ "$1" == "c" ]; then
	clear
	echo "::UNIX RELASE-COMPILE STARTED::"
	rm -rf build
	mkdir build
	cp settings.cfg build
	cd build
	cmake -DCMAKE_BUILD_TYPE=Release ..
	make
	echo "::UNIX RELEASE-COMPILE FINISHED::"

elif [ "$1" == "dc" ] || [ "$1" == "debug-compile" ]; then
	clear
	echo "::UNIX DEBUG-COMPILE STARTED::"
	rm -rf build
	mkdir build
	cp settings.cfg build
	cd build
	cmake -DCMAKE_BUILD_TYPE=Debug ..
	make
	echo "::UNIX DEBUG-COMPILE FINISHED::"



elif [ "$1" == "run" ] || [ "$1" == "r" ]; then
	echo "::UNIX RUN::"
	cd build
	./MC_RCON_CLIENT

fi
