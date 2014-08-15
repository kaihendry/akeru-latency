curl -s 'https://docs.google.com/spreadsheets/d/1XTbKO1F6QBLg--qjekc_iMVKjFOn2Zps89SV4mRg4QY/export?format=csv&id=1XTbKO1F6QBLg--qjekc_iMVKjFOn2Zps89SV4mRg4QY&gid=0' | grep 87B5 | while read -r line
do
	IFS=","
	set -- $line
	echo $line

	# Make sure we have a epoch sized payload
	test ${#3} -eq 8 || continue

	sendtime=$(date --date='TZ="Asia/Singapore" '$1 +%s)
	test "$sendtime" || continue

	# Fix endianness of hex
	var=$3; var="0x${var:6:2}${var:4:2}${var:2:2}${var:0:2}"; rectime=$(printf "%d" "$var")

	echo rectime $rectime - sendtime $sendtime
	echo $(($rectime - $sendtime))
done
