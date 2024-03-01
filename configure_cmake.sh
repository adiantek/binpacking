#!/bin/bash

os=$1
arch=$2
shift 2
if [ "$os" == "windows-latest" ]; then
    cmake -A $arch $@
elif [ "$os" == "ubuntu-latest" ] && [ "$arch" == "arm64" ]; then
    cmake -DCMAKE_TOOLCHAIN_FILE=linux-aarch64.cmake $@
elif [ "$os" == "macos-latest" ]; then
    if [ "$arch" == "x64" ]; then
        arch="x86_64"
    fi
    cmake -DCMAKE_OSX_ARCHITECTURES=$arch $@
else
    cmake $@
fi