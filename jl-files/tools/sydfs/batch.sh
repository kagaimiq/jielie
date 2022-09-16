flist=""

for fil in $(ls $1)
do
	if [[ -f "$1$fil" ]]
	then
		flist+="$1$fil 0 "
	fi
done

./sydtool -pfc $2 $flist
