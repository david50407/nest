
SRC = main.cxx entry.cxx bbsd.cxx

OBJ = main.o entry.o bbsd.o

EXE = bbsd
CXX = clang++
CXXFLAGS := -std=c++11 -DLINUX -O2 -pipe -fomit-frame-pointer -Wunused -I../include
CXXFLAGS += -I/usr/lib/llvm-3.4/lib/clang/3.4.1/include
LDFLAGS = -s -rdynamic -L ../lib
LIBS = -ljson11

all:
	@echo "Please enter 'make sys-type', "
	@echo " make linux   : for Linux"

linux:
	@$(MAKE) CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)" LDFLAGS="$(LDFLAGS)" LIBS="$(LIBS)" $(EXE)

%.o: %.cxx
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

bbsd: $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(EXE) *.exe *.o *~
