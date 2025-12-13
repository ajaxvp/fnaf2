OUT=fnaf2
SOURCES := $(notdir $(shell find src -name '*.c'))
OBJECTS := $(addprefix build/,$(addsuffix .o,$(basename $(SOURCES))))
LIBRARIES := $(shell find lib -name '*.dylib')

.PHONY: default test

default: $(OUT)

clean:
	rm -f $(OUT) $(OBJECTS)
	rm -rf build

$(OUT): $(OBJECTS)
	gcc -g -o $(OUT) $^ $(LIBRARIES)

build/%.o: src/%.c build
	gcc -c -g -Wall -Werror -pedantic --std=c99 --include-directory=include -o $@ $<

build:
	mkdir -p build