#!/bin/bash

case "$1" in
raspberry)
    sudo apt-get update
    sudo apt-get upgrade
    gpio -v
    make clean all target=raspberry
    exit 0
    ;;
linux)
    make clean all
    exit 0
    ;;
esac

echo "Please specify platform: raspberry, linux"
exit 1
