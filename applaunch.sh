#!/bin/bash
xoffset=$[(`xdpyinfo | grep dimensions: | grep -o '[0-9]\+' | sed -n 1p` - 384) / 2]
yoffset=$[(`xdpyinfo | grep dimensions: | grep -o '[0-9]\+' | sed -n 2p` - (`[[ \`find ~/.applsh -maxdepth 1 -type f -printf "%f\n" | wc -l\` > 10 ]] && echo 10 || \`find ~/.applsh -maxdepth 1 -type f -printf "%f\n" | wc -l\`` + 1) * 21) / 2]
app=`find ~/.applsh -maxdepth 1 -type f -printf "%f\n" | dmenu -x $xoffset -y $yoffset -z 384 -l 10 -i -p "Select application:"`
find ~/.applsh -maxdepth 1 -type f -printf "%f\n" | grep -F -q -x "$app" && sh -c "`cat ~/.applsh/\"$app\"`" || [[ $app = "" ]] || st -e sh -c "echo Invalid application && sleep 3"
