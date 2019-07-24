SRCDIR = src
OBJDIR = obj

SRCFILES = $(wildcard $(SRCDIR)/*.cpp)
OBJFILES = $(subst $(SRCDIR)/,$(OBJDIR)/,$(SRCFILES:.cpp=.o))

CFLAGS = -fconcepts -std=c++2a -g -Wall -pedantic

Papo: $(OBJFILES)
	mkdir -p $(OBJDIR)
	$(CXX) -o $@.o $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJFILES) Papo