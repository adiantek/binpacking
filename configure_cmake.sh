#!/bin/bash

os=$1
arch=$2
shift 2
if [ "$os" == "windows" ]; then
    cmake -A $arch $@
elif [ "$os" == "linux" ] && [ "$arch" == "arm64" ] ; then
    cmake -DCMAKE_TOOLCHAIN_FILE=linux-aarch64.cmake $@
else
    cmake $@
fi