#!/bin/sh
app=`echo -e "Terminal\nFirefox\nSpotify\nVSCode" | dmenu -l 10 -i -p "Select application to launch:"`
case $app in
  Terminal)
    st
    ;;
  Firefox)
    firefox
    ;;
  Spotify)
    spotify
    ;;
  VSCode)
    code
    ;;
  "")
    exit 0
    ;;
  *)
    st -e sh -c "echo Unknown command && sleep 5"
    ;;
esac

