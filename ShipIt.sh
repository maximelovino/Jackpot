#!/usr/bin/env bash

if [[ -f groupe5.tar.gz ]]; then
	rm groupe5.tar.gz
fi

mkdir groupe5

cp const.h groupe5/
cp display.c groupe5/
cp display.h groupe5/
cp handler.c groupe5/
cp handler.h groupe5/
cp jackpot.c groupe5/
cp makefile groupe5/
cp wheel.c groupe5/
cp wheel.h groupe5/
cp report/report.pdf groupe5/

tar -cvzf groupe5.tar.gz groupe5
rm -r groupe5
