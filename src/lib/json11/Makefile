CXXFLAGS = -std=c++11 -O2 -fno-rtti -fno-exceptions -Wunused

all: libjson11.a

libjson11.a: json11.o
	ar rvs $@ $<

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm *.o *.a
