SHELL := bash

tiny-qt-launcher: main.cpp Makefile
	clang++ -std=c++11 -fPIE -Oz -s -Weverything -Wno-c++98-compat $(shell pkg-config --cflags --libs Qt5Gui Qt5Widgets | sed 's/-I\//-isystem\ \//g') $< -o $@
	upx --best --ultra-brute --lzma -qqq $@

clean:
	rm -f tiny-qt-launcher
