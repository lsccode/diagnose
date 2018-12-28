CROSS    := arm-linux-gnueabihf-
CXX      := $(CROSS)g++
CC       := $(CROSS)gcc
CPPFLAGS += -I ../include

ALL := diaglog libdiag.a
all:$(ALL)

diaglog:diaglog.o main.o
	$(CXX) -o $@ $^

libdiag.a:diaglog.o
	ar rf $@ $^

install:
	cp -rf $(ALL) $(TARGET_DIR)
	cp -rf diaglog.h      /mnt/workSpace/nextvpu/dig/nvpmidware/NvpMedia/Include
	cp -rf ../include/*.h /mnt/workSpace/nextvpu/dig/nvpmidware/NvpMedia/Include
	cp -rf libdiag.a      /mnt/workSpace/nextvpu/dig/nvpmidware/Bin/jx
	cp -rf diaglog.h      /root/workspace/nvpsdk/nvpmidware/NvpMedia/Include
	cp -rf ../include/*.h /root/workspace/nvpsdk/nvpmidware/NvpMedia/Include
	cp -rf libdiag.a      /root/workspace/nvpsdk/nvpmidware/Bin/jx

clean:
	rm -rf *.o *.d $(ALL);cd $(TARGET_DIR);rm -rf $(ALL)
