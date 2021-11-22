name=$(echo "${1##*/}" $1 | awk -F"." '{printf $1}') #cut out the name from file

grep "impsub:" $1 | awk -F":" '{print $2}' > gen/$name.dat.tmp #find out what subcategories to link
subimports=$(cat gen/$name.dat.tmp)
cat $1 > gen/$name.tmp #fix this fugly hack.

subv=$(grep "impsub:" $1 | wc -l)
if [ $subv -ge "1" ]
then
	for Line in $subimports
	do
		links=$(sort $Line.sub.blu | tr '\n' ' ') #removes lines cuz sed gets sad
	        sed -i "s#impsub:$Line#$links#g" gen/$name.tmp #> gen/$name.temp #sed -i doesnt work the same on BSD
	#	mv gen/$name.temp gen/$name.tmp
	done
#else
#cat $1 > gen/$name.tmp
fi
tagv=$(grep "imptag:" $1 | wc -l)
if [ $tagv -ge "1" ]
then
	grep "imptag:" $1 | awk -F":" '{print $2}' > gen/$name.tagimp #find out what tags to link
	for Line in gen/$name.tagimp
	do
		tagn=$(echo "${Line##*/}" $Line | awk -F"." '{printf $1}')
		links=$(sort $tagn.tag.blu | tr '\n' ' ') #remove lines for sed
		sed "s#imptag:$tagn#$links#g" gen/$name.tmp > gen/$name.temp.tmp
		mv gen/$name.temp.tmp gen/$name.tmp
	done
fi
tags=$(head -4 $1 | grep tags | awk -F":" '{printf $2}')
lnbr=$(grep -n ':start:' gen/$name.tmp)

sed "s#TAGS#$tags#g" materials/head > html/$name.html
cat menu.blu materials/bodyprefix >> html/$name.html
tail -n +5 gen/$name.tmp >> html/$name.html #should use grep and/or have a start flag
cat materials/bodysuffix materials/footer >> html/$name.html
echo "generated $name.html"
