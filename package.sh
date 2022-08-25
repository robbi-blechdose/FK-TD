#!/bin/sh

make oclean
make TARGET=funkey

mkdir -p opk
cp  main.elf opk/main.elf
cp -r ./res opk/res
cp icon.png opk/icon.png
cp fk-td.funkey-s.desktop opk/fk-td.funkey-s.desktop

mksquashfs ./opk FK-TD.opk -all-root -noappend -no-exports -no-xattrs

rm -r opk