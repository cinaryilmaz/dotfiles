#!/bin/sh
app=`echo -e "Terminal\nFirefox\nSpotify\nVSCode\nTor Browser\nA website" | dmenu -l 10 -i -p "Select application to launch:"`
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
  Tor\ Browser)
    tor-browser # or start-tor-browser idk i name my executables myself
    ;;
  A\ website)
    website=`echo -e "Youtube\nGithub\nQoLang\nQoLang website\nBack" | dmenu -l 10 -i -p "Select a website to open:"`
    case $website in
      Youtube)
        firefox https://youtube.com
        ;;
      Github)
        firefox https://github.com
        ;;
      QoLang)
        firefox https://github.com/QoLang/QoLang
        ;;
      QoLang\ website)
        firefox https://qolang.camroku.tech
        ;;
      Back)
        applaunch
        ;;
      *)
        exit 0
        ;;
    esac
    ;;
  "")
    exit 0
    ;;
  *)
    st -e sh -c "echo Unknown command && sleep 5"
    ;;
esac

