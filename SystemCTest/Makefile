UNIT=main

OBJS=$(UNIT).o 
TARGET=$(UNIT)

CXX=g++
CC=gcc

SYSTEMC_HOME = /usr/local

LIBDIR = -L $(SYSTEMC_HOME)/lib


INCDIR = -I $(SYSTEMC_HOME)/include
LIBS = -lsystemc -lm $(EXTRA_LIBS)

all: $(TARGET)

$(TARGET): $(OBJS)
	 $(CXX) $(CFLAGS) $(INCDIR) $(LIBDIR) -o $@ $(OBJS) $(LIBS)

#%.o: %.cpp
#	 $(CXX) $(CFLAGS) $(INCDIR) -g -c -Wno-deprecated $< -o $@

$(UNIT).o: $(UNIT).cpp defines.h Ampel1.h Ampel2.h Ampel3.h Ampel4.h Tramsignal.h RoterPfeil.h Environment.h
	$(CXX) $(CFLAGS) $(INCDIR) -g -c -Wno-deprecated $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) *~
