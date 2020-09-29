grep -oE '\b.{8}\b' moby.txt | while read -r line ; do
	if ["$(wc -l)" == "36"]
		echo "$line"
	fi
done
