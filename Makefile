SRCDIR = src
OBJDIR = obj
DEPDIR = dep

SRCFILES = $(wildcard $(SRCDIR)/*.cpp)
OBJFILES = $(subst $(SRCDIR)/,$(OBJDIR)/,$(SRCFILES:.cpp=.o))

CFLAGS = -fconcepts -std=c++2a -g -Wall -pedantic

Papo: $(OBJFILES)
	mkdir -p $(OBJDIR)
	mkdir -p $(DEPDIR)
	$(CXX) -o $@.o $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.p
	$(CXX) -c -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJFILES) Papo