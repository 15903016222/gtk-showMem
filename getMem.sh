#!/bin/bash

FILE="/tmp/mem.html"

write_html_head() 
{
	echo "<html>" > $FILE
	echo "<head>" >> $FILE
	echo "<title>存储磁盘容量信息</title>" >> $FILE
	echo "</head>" >> $FILE
	echo "<body>" >> $FILE
}

write_html_tail()
{
	echo "</body>" >> $FILE
	echo "</html>" >> $FILE
}

write_html()
{
	echo "<p align=\"center\">$1" >> $FILE
	echo "总容量:$2" >> $FILE
	echo "已使用:$3" >> $FILE
	echo "剩余:$4 </p>" >> $FILE 
}

get_disk_info()
{
	disk=`mount | grep "$1" | awk '{print $3}'`
	total=`df -h $disk | grep "$disk" | awk '{print $2}'`
	used=`df -h $disk | grep "$disk" | awk '{print $3}'`
	free=`df -h $disk | grep "$disk" | awk '{print $4}'`
	if [ "/" == "$disk" ]
	then
		disk="system"
	elif [ "/home/tt/TT/data" == "$disk" ]
	then
		# disk=${disk##*/}
		disk="doppler"
	elif [ "/opt/usbStorage" == "$disk" ]
	then
		# disk=${disk##*/}
		disk="usb"
	else
		disk=${disk##*/}
	fi
}

test -f "$FILE" && rm "$FILE"
contents=`mount | awk '{print $1}' | grep "rootfs\|/dev/sd\|/dev/mmc"`

write_html_head
for content in `echo $contents`
do
	get_disk_info $content
	write_html $disk $total $used $free
done
write_html_tail
