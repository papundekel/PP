SRCDIR = src
OBJDIR = obj
DEPDIR = dep

SRCFILES = $(wildcard $(SRCDIR)/*.cpp)
OBJFILES = $(subst $(SRCDIR)/,$(OBJDIR)/,$(SRCFILES:.cpp=.o))
DEPFILES = $(subst $(SRCDIR)/,$(DEPDIR)/,$(SRCFILES:.cpp=.d))

CXXFLAGS = -Ofast -fconcepts -std=c++2a -g -Wall -Wextra -Wpedantic
LDFLAGS = -Ofast

Papo.out: $(OBJFILES)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(DEPDIR)/%.d: $(SRCDIR)/%.cpp
	mkdir -p $(DEPDIR)
	$(CXX) -MM $^ -MT $(OBJDIR)/$*.o -MF $@

$(OBJDIR)/%.o: $(DEPDIR)/%.d

include $(DEPFILES)

$(OBJDIR)/%.o:
	mkdir -p $(OBJDIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJFILES) $(DEPFILES) Papo.out