#CROSS     = arm-linux-gnueabihf-
CXX      := $(CROSS)g++
CC       := $(CROSS)gcc
CPPFLAGS += -I ../include

ALL := ser
all:$(ALL)

ser:diagser.o
	$(CXX) -o $@ $^

install:
	cp -rf $(ALL) $(TARGET_DIR)	

clean:
	rm -rf *.o *.d $(ALL);cd $(TARGET_DIR);rm -rf $(ALL)

