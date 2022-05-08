#!/bin/sh

#compile everything
make

#check if everthing got compiled, exit if not
while true; do

	if test -f cshg && test -f cshg-imp && test -f cshg-md; then
	#if [ ! -f "cshg" ] || [ ! -f "cshg-imp" ] || [ ! -f "cshg-md" ]; then
		break;
	else
		echo "all targets hasn't been compiled, exiting script"
		exit 1
	fi
done

#everything got compiled, check if user is root and ask if user wants alias for cshg if not
if [ "$(id -nu)" != "root" ]; then
	echo "you arent root on this system, do you want to generate aliases[y/n]"
	while true; do
		read yn
		if [ "$yn" = n ]; then
			exit
		fi
		if [ "$yn" = y ]; then
			break;
		fi
		echo "please answer y/n"
	done

	dir=$(pwd)
	echo "please copy and paste this into you shell config:"
	echo ""
	echo "alias cshg=\"/./${dir}/cshg\""
	echo "alias cshg-imp=\"/./${dir}/cshg-imp\""
	echo "alias cshg-md=\"/./${dir}/cshg-md\""
	echo ""

#if the user was root, install programs to /usr/bin
else
	cp cshg /usr/bin/cshg
	cp cshg-imp /usr/bin/cshg-imp
	cp cshg-md /usr/bin/cshg-md
fi
