#!/bin/sh

newfile=$( echo "$1" | awk -F"/" '{printf $2}')
#./aux.sh $file &
./blu.imp "$1" > gen/"$newfile".temp
#generates temporary pages and puts them in gen/

#post processing for markdown and moving files from gen/ to html/
filename=$( echo "$newfile" | awk -F"." '{printf $1}')
taglist=$(cat gen/"$newfile".temp | grep "!tag:" | awk -F":" '{printf $1}')
sed "s/TAGS/$taglist/g" materials/head > html/"$filename".html
cat gen/menu.temp materials/bodyprefix >> html/"$filename".html
./blu.bmd gen/"$newfile".temp >> html/"$filename".html #this processes pages WITH md
#cat gen/"$newfile".temp >> html/$filename.html #this ignores md
cat materials/bodysuffix materials/footer >> html/"$filename".html
#write html files to html directory
echo "$filename generated"
