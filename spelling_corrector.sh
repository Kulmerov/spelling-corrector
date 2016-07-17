#!/bin/bash

selected_text=$(xsel -o)
user_clipboard=$(xsel)
response_from_server=$(wget -U "Opera/9.80 (J2ME/MIDP; Opera Mini/4.5.33867/35.2883; U; en) Presto/2.8.119 Version/11.10" -qO - "http://www.google.com/search?&q=$(echo $selected_text)&num=0")
corrected_text=$(echo "$response_from_server" | grep -o -P '<a.*spell.*><b><i>\K.*(?=<\/i><\/b><\/a>)')
notify-send "$selected_text" "$corrected_text" -i accessories-dictionary
echo $corrected_text
if [ "$corrected_text" != "" ]
then
	echo -n $corrected_text | xsel -i -b
	./XFakeKey
	sleep 0.05 
	echo -n $user_clipboard | xsel -i -b
else
	exit 0
fi