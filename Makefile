SRCDIR = src
OBJDIR = obj

SRCFILES = $(wildcard $(SRCDIR)/*.cpp)
x = $(SRCFILES:.cpp=.o)
OBJFILES = $(subst $(SRCDIR)/,$(OBJDIR)/,$(x))

CFLAGS = -fconcepts -std=c++2a -g -Wall -pedantic

Papo: $(OBJFILES)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJFILES) Papo