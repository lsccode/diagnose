#CROSS    := arm-linux-gnueabihf-
CXX      := $(CROSS)g++
CC       := $(CROSS)gcc
CPPFLAGS += -I ../include

ALL := diaglog.out libdiag.a
all:$(ALL)

diaglog.out:diaglog.o main.o libdiag.a
	$(CXX) -o $@ $^

libdiag.a:diaglog.o cbaselog.o csyslog.o cnetlog.o cstderrlog.o cfilelog.o cdiagnose.o logcapi.o
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
