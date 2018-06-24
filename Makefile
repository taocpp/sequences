# The Art of C++
# Copyright (c) 2015-2018 Daniel Frey
# Please see LICENSE for license or visit https://github.com/taocpp/json

.SUFFIXES:
.SECONDARY:

ifeq ($(OS),Windows_NT)
UNAME_S := $(OS)
else
UNAME_S := $(shell uname -s)
endif

CPPFLAGS ?= -pedantic
CXXSTD ?= c++11
CXXFLAGS ?= -O3 -Wall -Wextra -Werror

CLANG_TIDY ?= clang-tidy

HEADERS := $(shell find include -name '*.hpp')
SOURCES := $(shell find src/ -name '*.cpp')
DEPENDS := $(SOURCES:%.cpp=build/%.d)
BINARIES := $(SOURCES:%.cpp=build/%)

UNIT_TESTS := $(filter build/src/test/%,$(BINARIES))

.PHONY: all
all: compile check

.PHONY: compile
compile: $(BINARIES)

.PHONY: check
check: $(UNIT_TESTS)
	@set -e; for T in $(UNIT_TESTS); do echo $$T; $$T > /dev/null; done
	@build/src/test/seq/tester

.PHONY: clean
clean:
	@rm -rf build
	@find . -name '*~' -delete

build/%.d: %.cpp Makefile
	@mkdir -p $(@D)
	$(CXX) $(CXXSTD) -Iinclude $(CPPFLAGS) -MM -MQ $@ $< -o $@

build/%: %.cpp build/%.d
	$(CXX) $(CXXSTD) -Iinclude $(CPPFLAGS) $(CXXFLAGS) $< -o $@

build/%.clang-tidy: %
	$(CLANG_TIDY) -extra-arg "-Iinclude" -extra-arg "-std=c++11" -checks=*,-fuchsia-*,-cppcoreguidelines-pro-bounds-array-to-pointer-decay,-misc-macro-parentheses,-hicpp-no-array-decay -warnings-as-errors=* $< 2>/dev/null
	@mkdir -p $(@D)
	@touch $@

.PHONY: clang-tidy
clang-tidy: $(HEADERS:%=build/%.clang-tidy) $(SOURCES:%=build/%.clang-tidy)
	@echo "All $(words $(HEADERS) $(SOURCES)) clang-tidy tests passed."

ifeq ($(findstring $(MAKECMDGOALS),clean),)
-include $(DEPENDS)
endif
