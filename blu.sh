#!/bin/sh
#cat materials/ascii

#remove old files
rm gen/*
#old files removed

#starting to categorize html pages
for file in txt/*.md
do
	./blu.kat "$file"
	#generates links to all pages and writes them to .tag and .sub files in gen/
done
echo "subcategories and tags generated"
#everything is now categorised, html generation can start

categories=$(find gen/*.cat | awk -F"/" '{printf $2}' | awk -F"." '{printf $1}')
for Line in $categories
do
	itemname=$(cat txt/"$categories".md | grep "!title:" | awk -F":" '{print $1}')
	sed "s#MENUITEM#$Line#" materials/mbracket | sed "s#ITEMNAME#$itemname#" > gen/menuitem.tmp
	cat gen/menuitem.tmp >> gen/menu.tmp
done
echo "menu created"

#filter out rare tags
#for file in gen/*.tag
#do
#	lines=$(wc -l $file | awk '{print $1}')
#	if [ ! $lines -gt "2" ]
#	then
#		rm $file
#	fi
#done
#rare tags filtered out

#adding link sheets and catting html pages
for file in txt/*.md
do
	newfile=$( echo "$file" | awk -F"/" '{printf $2}')
	#./aux.sh $file &
	./blu.imp "$file" > gen/"$newfile".temp
	#generates temporary pages and puts them in gen/

	#post processing for markdown and moving files from gen/ to html/
	filename=$( echo "$newfile" | awk -F"." '{printf $1}')
	./blu.bmd gen/"$newfile".temp > html/$filename.html
	#write html files to html directory
done
wait

echo " "
echo "finished!"
