CXX = g++
CXXFLAGS = -DYYDEBUG=1 -Igen/
TARGET = fgc

all: $(TARGET)

$(TARGET): gen/parse.cc gen/lex.cc
	$(CXX) -DYYDEBUG=1 -o $@ $^

gen/parse.cc: gen/parse.y
	bison -dtv -o $@ $<

gen/lex.cc: gen/lex.l
	flex -o $@ $<

clean:
	$(RM) gen/parse.cc gen/lex.cc

distclean: clean
	$(RM) $(TARGET)

check: all
	./check/test.sh

relicense:
	copyright-header --license-file HEADER -g -a "check/runtime:check/test.sh:src" -o .

.PHONY: all clean distclean check relicense
