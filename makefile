# TermOx examples Makefile

PWD ?= $(shell pwd)

CMAKE ?= cmake
CXX ?= clang++-20

BUILD_DIR ?= $(PWD)/build
BUILD_TYPE ?= Debug

EXAMPLES := \
	TermOx.examples.pong \
	TermOx.examples.pinbox \
	TermOx.examples.snake \
	TermOx.examples.accumulator \
	TermOx.examples.bmp_view \
	TermOx.examples.scratch \
	TermOx.examples.hello \
	TermOx.examples.form \
	TermOx.examples.progress \
	TermOx.examples.panels

.PHONY: all examples configure clean $(EXAMPLES)

all: examples

configure:
	$(CMAKE) -S $(PWD) -B $(BUILD_DIR) \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DCMAKE_CXX_COMPILER=$(CXX)

examples: configure
	$(CMAKE) --build $(BUILD_DIR) --target $(EXAMPLES)

$(EXAMPLES): configure
	$(CMAKE) --build $(BUILD_DIR) --target $@

clean:
	$(CMAKE) --build $(BUILD_DIR) --target clean || rm -rf $(BUILD_DIR)
