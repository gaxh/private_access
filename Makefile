
all : demo.exe

demo.exe : demo.cpp
	${CXX} -o $@ $< -g -O2 -Wall

all : access_helper_demo.exe

access_helper_demo.exe : access_helper_demo.cpp access_helper.h
	${CXX} -o $@ $< -g -O2 -Wall

clean:
	rm -f *.exe
