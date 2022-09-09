#!/bin/bash
app=`ls ~/.applsh | dmenu -l 10 -i -p "Select application to launch:"`
ls ~/.applsh | grep -F -q -x "$app" && sh -c "`cat ~/.applsh/\"$app\"`" || st -e sh -c "echo Invalid application && sleep 3"
