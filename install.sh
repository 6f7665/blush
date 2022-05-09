#!/bin/sh

if [ "$(id -nu)" = "root" ]; then
	echo "please don't run this script as root"
	exit
fi

#compile everything
make

#check if everthing got compiled, exit if not
while true; do

	if test -f cshg && test -f cshg-imp && test -f cshg-md; then
		break;
	else
		echo "all targets hasn't been compiled, exiting script"
		exit 1
	fi
done

#everything got compiled, check if user has sudo right, if not ask if user wants aliases
check=$(sudo -l -U "$(id -nu)" | grep -c "User $(id -nu) may run the following commands on")
if [ ! "$check" ]; then
	echo "it appears you dont have sudo rights this system, do you want to generate aliases[y/n]"
	while true; do
		read -r yn
		if [ "$yn" = n ]; then
			break;
		fi
		if [ "$yn" = y ]; then
			dir=$(pwd)
			echo "please copy and paste this into you shell config:"
			echo ""
			echo "alias cshg=\"/./${dir}/cshg\""
			echo "alias cshg-imp=\"/./${dir}/cshg-imp\""
			echo "alias cshg-md=\"/./${dir}/cshg-md\""
			echo ""
			break;
		fi
		echo "please answer y/n"
	done


#if the user was root, install programs to /usr/bin
else
	echo "installing to /usr/bin/"
	sudo cp cshg /usr/bin/cshg
	sudo cp cshg-imp /usr/bin/cshg-imp
	sudo cp cshg-md /usr/bin/cshg-md
fi

#check if user wants to process example files and open in browser
echo "do you want to generate documentation files and open them in browser[y/n]"
while true; do
	read -r yn
	if [ "$yn" = n ]; then
		exit
	fi
	if [ "$yn" = y ]; then
		break;
	fi
	echo "please answer y/n"
done

./cshg -i -f txt/

echo "please enter webbrowser command (eg. firefox)"
read -r browser
${browser} html/index.html && exit
