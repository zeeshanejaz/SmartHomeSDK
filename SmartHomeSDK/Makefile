CXX := g++
CXXFLAGS := -Wall -O2 -fPIC
CXXFLAGS += -std=c++0x

LIBEXT := so
LIBNAME := SmartHomeSDK
BUILDDIR := build
OUTPUTDIR := release
LIBS = -lpthread
TARGET := $(OUTPUTDIR)/$(LIBNAME).$(LIBEXT)
LDFLAGS := -shared -lpthread
SRCEXT := cpp
HDREXT := h
SRCDIR := src
SOURCES := Socket.cpp Utility.cpp EnumParser.cpp ProtocolPacket.cpp CommClient.cpp ProtocolManager.cpp ModelController.cpp SmartHomeSDK.cpp
HEADERS := Socket.h Utility.h enum_defines.h EnumParser.h ProtocolPacket.h CommClient.h ProtocolManager.h ModelController.h SmartHomeSDK.h
OBJECTS := $(addprefix $(BUILDDIR)/,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.deps)
CPYHDRS := $(addprefix $(OUTPUTDIR)/, $(HEADERS))

default: $(TARGET)
 
$(TARGET): $(OBJECTS)

	@mkdir -p $(OUTPUTDIR)	
	@echo " Linking..."; $(CXX) $(LDFLAGS) $^ -o $(TARGET) $(LIBS)
 
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)

	@mkdir -p $(BUILDDIR)
	@echo " CXX $<"; $(CC) $(CXXFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

	
headers: $(CPYHDRS)
	
$(OUTPUTDIR)/%.$(HDREXT): $(SRCDIR)/%.$(HDREXT)

	cp $< $@
	

clean:

	@echo " Cleaning..."; $(RM) -rf $(BUILDDIR) $(OUTPUTDIR)	
 
-include $(DEPS)
 
.PHONY: clean
