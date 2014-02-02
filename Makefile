SHELL := bash
CXX := clang++ -std=c++11
UPX := upx --best --ultra-brute --lzma -qqq

TARGET := tiny-qt-launcher

CXXFLAGS = -fPIE -Oz -g0 -s -Weverything -Wno-c++98-compat $(shell pkg-config --cflags --libs Qt5Gui Qt5Widgets fluidsynth | sed 's/-I\//-isystem\ \//g')

.PHONY : clean

$(TARGET): main.cpp Makefile
	@echo "BUILD $@"
	@$(CXX) $(CXXFLAGS) $< -o $@
ifeq ($(RELEASE), y)
	@echo "UPX $@"
	@$(UPX) $@
endif

clean:
	rm -f $(TARGET)
