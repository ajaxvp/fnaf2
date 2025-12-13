OUT=fnaf2
SOURCES := $(notdir $(shell find src -name '*.c'))
OBJECTS := $(addprefix build/,$(addsuffix .o,$(basename $(SOURCES))))

.PHONY: default test

default: $(OUT)

clean:
	rm -f $(OUT) $(OBJECTS)
	rm -rf build

$(OUT): $(OBJECTS)
	gcc -g -o $(OUT) $^

build/%.o: src/%.c build
	gcc -c -g -Wall -Werror -pedantic --std=c99 --include-directory=include -o $@ $<

build:
	mkdir -p build