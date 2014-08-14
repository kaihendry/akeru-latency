curl -s 'https://docs.google.com/spreadsheets/d/1XTbKO1F6QBLg--qjekc_iMVKjFOn2Zps89SV4mRg4QY/export?format=csv&id=1XTbKO1F6QBLg--qjekc_iMVKjFOn2Zps89SV4mRg4QY&gid=0' | grep 87B5 | while read -r line
do
	IFS=","
	set -- $line
	test ${#3} -eq 8 || continue
	echo $line
	# Fix time to be parsable
	var="$1"; date=$(echo ${var:6:4}-${var:3:2}-${var:0:2} ${var:11:8})
	epoch=$(date --date='TZ="Asia/Singapore" '$date +%s)
	# Fix endianness of hex
	var=$3; var="0x${var:6:2}${var:4:2}${var:2:2}${var:0:2}"; rectime=$(printf "%d" "$var")
	echo rectime $rectime - epoch $epoch
	echo $(($rectime - $epoch))
done
