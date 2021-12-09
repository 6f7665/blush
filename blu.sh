#!/bin/sh
#cat materials/ascii

#remove old files
rm gen/*
#old files removed

#initialize and setup categories for menu entries
cats=$(grep -v "#" settings/categories.dat | grep : | awk '{print $1}')
cp materials/menu gen/menu.tmp
for Line in $cats
do
	itemname=$(grep $Line categories.dat | awk -F":" '{printf $3}')
	#sed "s#MENUITEM#$Line#g" materials/mbracket | echo >> gen/menu.tmp #gives empty output, fix this l8r
	sed "s#MENUITEM#$Line#" materials/mbracket | sed "s#ITEMNAME#$itemname#" > gen/item.tmp
	cat gen/item.tmp >> gen/menu.tmp
done
cat gen/menu.tmp materials/closemenu > menu.blu
echo "menu generated"
#menu generated

#starting to categorize html pages
for file in txt/*.md
do
	./blu.kat $file
	#generates links to all pages and writes them to .tag and .sub files in gen/
done
echo "subcategories and tags generated"
#everything is now categorised, html generation can start

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

#turn all tags into a big page
#cat menu.blu materials/bodyprefix > html/tags.html
#for file in gen/*.tag
#do
#	filename=$(echo "${file##*/}" $file | awk -F"." '{printf $1}')
#	echo "<p><b>$filename</b><br>" >> html/tags.html
#	cat $file >> html/tags.html
#	echo "</p>" >> html/tags.html
#done
#cat materials/bodysuffix materials/footer >> html/tags.html
#tagsheets generated, all pages can be linked using tags

#adding link sheets and catting html pages
for file in txt/*.md
do
	newfile=$( echo $file | awk -F"/" '{printf $2}')
	#./aux.sh $file &
	./blu.imp $file > gen/$newfile.temp
	#generates temporary pages and puts them in gen/
done
wait

#rm gen/* #removes tmp files in gen/

echo " "
echo "finished!"
