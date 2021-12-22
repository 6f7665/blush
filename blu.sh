#!/bin/sh
cat materials/ascii

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

#generate menu
cp materials/menu gen/menu.temp
for file in gen/*.cat
do
	echo $file
	page=$( echo $file | sed "s#gen/##g" | sed "s#.cat##g" )
	itemname=$(cat txt/"$page".md | grep "title" | awk -F":" '{printf $2}' )
	sed "s#MENUITEM#$page#" materials/mbracket | sed "s#ITEMNAME#$itemname#" > gen/menuitem.temp
	cat gen/menuitem.temp >> gen/menu.temp
done
cat materials/closemenu >> gen/menu.temp
echo "menu created"
#menu generated

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
	taglist=$(cat gen/"$newfile".temp | grep "!tag:" | awk -F":" '{printf $1}')
	sed "s/TAGS/$taglist/g" materials/head > html/$filename.html
	cat gen/menu.temp materials/bodyprefix >> html/$filename.html
	./blu.bmd gen/"$newfile".temp >> html/$filename.html #this processes pages WITH md
	#cat gen/"$newfile".temp >> html/$filename.html	#this ignores md
	cat materials/bodysuffix materials/footer >> html/"$filename".html
	#write html files to html directory
	echo "$filename generated"
done

echo " "
echo "finished!"
