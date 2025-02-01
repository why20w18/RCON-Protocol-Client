#!/bin/bash

if [ $# -ne 1 ]; then
	echo "SCRIPTI ASAGIDAKI GIBI KULLANIN:"
	echo "./cr-WIN32.sh ARGUMAN"
	echo "ARGUMANLAR:"
	echo "c veya compile"
	echo "r veya run"

elif [ "$1" == "c" ] || [ "$1" == "compile" ]; then
	echo "::WIN32 COMPILE STARTED::"
	rm -rf build-win32
	mkdir build-win32
	cp utils-WIN32/win32-dll/*.dll build-win32
	cp utils-WIN32/win32-dll/toolchain-windows.cmake build-win32
	cp utils-WIN32/settings.cfg build-win32
	cd build-win32
	cmake -DCMAKE_TOOLCHAIN_FILE=toolchain-windows.cmake ..
	make
	echo "::WIN32 COMPILE FINISHED::"

elif [ "$1" == "r" ] || [ "$1" == "run" ]; then
	echo "::WIN32 RUN::"
	wine ./build-win32/MC_RCON_CLIENT.exe

fi
