name=$(echo "${1##*/}" $1 | awk -F"." '{printf $1}')

head -4 $1 | grep ":" > gen/$name.settings.tmp #extract settings #add start tag later

if [ ! -s gen/$name.settings.tmp ]
then
	echo "warning $1 doesnt have any settings"
	break
fi

#get the subcategory of the file and print the name of the file to a category file
subcat=$(grep subcat gen/$name.settings.tmp | awk -F":" '{printf $2}') # > gen/temp.tmp)
sed "s#LINK#$name#g" materials/link >> "$subcat.sub.blu"

#we do the same thing for tags, except here we can have multiple tags
grep tags gen/$name.settings.tmp | awk -F":" '{printf $2}' | sed "s/,/\n/g" > gen/$name.tags.tmp
tags=$(cat gen/$name.tags.tmp)

for Line in $tags
do
	sed "s#LINK#$name#g" materials/link >> $Line.tag.blu
done
#everything is now categorised, html generation can start
