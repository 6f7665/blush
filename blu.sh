#!/bin/sh
#cat materials/ascii

#generate menu
cp materials/menu gen/menu.temp
for file in gen/*.cat
do
	echo "$file"
	page=$( echo "$file" | sed "s#gen/##g" | sed "s#.cat##g" )
	itemname=$( grep -m 1 '!title:' txt/"$page".md | awk -F":" '{printf $2}' )
	sed "s#MENUITEM#$page#" materials/mbracket | sed "s#ITEMNAME#$itemname#" > gen/menuitem.temp
	cat gen/menuitem.temp >> gen/menu.temp
done
cat materials/closemenu >> gen/menu.temp
printf '\033[34m>menu generated\033[39m\n'
#menu generated

#adding link sheets and catting html pages
for file in txt/*.md
do
	./imp.sh "$file" &
done
wait

printf '\033[34m>finished!\033[39m\n'
