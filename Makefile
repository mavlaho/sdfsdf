CXXC = g++

STD = -std=c++17

LDFLAGS = -lm

OPT = -D NDEBUG -ffast-math -O3 -march=native

DBG = -D DEBUG -Og -g -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy \
                      -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op          \
                      -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept             \
                      -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow     \
                      -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel                \
                      -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused     \

INCL = -I ./src/headers

run:
	$(CXXC) $(STD) $(OPT) $(INCL) $(SRC) ./src/main.cpp $(LDFLAGS) -o run

dbg:
	$(CXXC) $(STD) $(DBG) $(INCL) $(SRC) ./src/main.cpp $(LDFLAGS) -o dbg

test1:
	$(CXXC) $(STD) $(OPT) $(INCL) $(SRC) ./test/test1.cpp $(LDFLAGS) -o runtest1

dbgtest1:
	$(CXXC) $(STD) $(DBG) $(INCL) $(SRC) ./test/test1.cpp $(LDFLAGS) -o dbgtest1



clear:
	rm -f run dbg runtest1 dbgtest1
	
	
