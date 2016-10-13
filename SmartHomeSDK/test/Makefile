BUILDDIR := build
OUTPUTDIR := release
SRCEXT := cpp

APPNAME := SmartHomeSDKTest
APPEXT := o
LIBNAME = SmartHomeSDK
LIBEXT := so
LIBDIR := ../$(OUTPUTDIR)
INCLDIR := ../$(OUTPUTDIR)

CXX := g++
CXXFLAGS := -Wall -O2
CXXFLAGS += $(addprefix -I,$(INCLDIR))

TARGET := $(OUTPUTDIR)/$(APPNAME).$(APPEXT)
LDFLAGS := -o -Wl
SHAPILIB := $(LIBDIR)/$(LIBNAME).$(LIBEXT)
LIBS := $(SHAPILIB) -lpthread

SOURCES := Test.cpp
OBJECTS := $(addprefix $(BUILDDIR)/,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.deps)

default: $(TARGET)
 
$(TARGET): $(OBJECTS)

	@mkdir -p $(OUTPUTDIR)	
	@cp $(SHAPILIB) $(OUTPUTDIR)
	@echo " Linking..."; $(CXX) $(LDFLAGS) $^ -o $(TARGET) $(LIBS) 
 
$(BUILDDIR)/%.o: %.$(SRCEXT)

	@mkdir -p $(BUILDDIR)
	@echo " CXX $<"; $(CC) $(CXXFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

clean:

	@echo " Cleaning..."; $(RM) -rf $(BUILDDIR) $(OUTPUTDIR)	
 
-include $(DEPS)
 
.PHONY: clean
