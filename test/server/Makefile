cc = gcc

LD_FLAG=-g -Wall -I. -shared -fPIC

BIN = urpc_server_test
#deps = $(shell find ../../include -name "*.h")
deps = -I $(PRJ_ROOT)/include
src = $(shell find ./ -name "*.c")
obj = $(src:%.c=%.o) 

$(BIN): $(obj)
	$(cc) -o $(BIN) $(obj) -L$(PRJ_ROOT)/lib -lurpc  -los -lpthread -lrt
	mv $(BIN) $(PRJ_ROOT)/bin

%.o: %.c
	$(cc) $(LD_FLAG) -o $@ $< $(deps)

clean:
	rm -rf $(obj) $(PRJ_ROOT)/bin/$(BIN)
