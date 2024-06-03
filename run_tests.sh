#!/bin/bash

os=$1
arch=$2
shift 2
app=./build/binpacking
if [ "$os" == "windows-latest" ]; then
    app=./build/Release/binpacking.exe
elif [ "$os" == "ubuntu-latest" ] && [ "$arch" == "arm64" ]; then
    app="qemu-aarch64 -L /usr/aarch64-linux-gnu $app"
fi
$app bfdh float 2000
$app ffdh float 2000
$app nfdh float 2000
$app wfdh float 2000
$app bfdh int 2000
$app ffdh int 2000
$app nfdh int 2000
$app wfdh int 2000