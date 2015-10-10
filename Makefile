# The Art of C++
# Copyright (c) 2015 Daniel Frey

.SUFFIXES:
.SECONDARY:

ifeq ($(OS),Windows_NT)
UNAME_S := $(OS)
else
UNAME_S := $(shell uname -s)
endif

ifeq ($(CXXSTD),)
CXXSTD := -std=c++14
ifeq ($(UNAME_S),Darwin)
CXXSTD += -stdlib=libc++
endif
endif

CPPFLAGS ?= -pedantic
CXXFLAGS ?= -O3 -Wall -Wextra -Werror

SOURCES := $(shell find -name '*.cpp')
DEPENDS := $(SOURCES:./%.cpp=build/%.d)
BINARIES := $(SOURCES:./%.cpp=build/%)

UNIT_TESTS := $(filter build/src/test/%,$(BINARIES))

.PHONY: all
all: $(BINARIES)
	@set -e; for T in $(UNIT_TESTS); do echo $$T; $$T > /dev/null; done

.PHONY: clean
clean:
	rm -rf build
	find -name '*~' -delete

build/%.d: %.cpp Makefile
	@mkdir -p $(@D)
	$(CXX) $(CXXSTD) -Iinclude $(CPPFLAGS) -MM -MQ $@ $< -o $@

build/%: %.cpp build/%.d
	$(CXX) $(CXXSTD) -Iinclude $(CPPFLAGS) $(CXXFLAGS) $< -o $@

ifeq ($(findstring $(MAKECMDGOALS),clean),)
-include $(DEPENDS)
endif
