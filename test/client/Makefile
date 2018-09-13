cc = gcc

#LD_FLAG=-g -Wall -I. -shared -fPIC            -------这种参数会导致编译的o文件不能连接到bin文件中去
LD_FLAG=-g -Wall -I. -shared -fPIC -DDEBUG -c -g

BIN = urpc_client_test
#deps = $(shell find ../../include -name "*.h")
deps = -I $(PRJ_ROOT)/include
src = $(shell find ./ -name "*.c")
obj = $(src:%.c=%.o) 

all: $(BIN)

$(BIN): $(obj)
	$(cc) -o $(BIN) $(obj) -L$(PRJ_ROOT)/lib -lurpc  -los -lpthread -lrt
	mv $(BIN) $(PRJ_ROOT)/bin

$(obj):%.o: %.c
	$(cc) $(LD_FLAG) -o $@ $< $(deps)

clean:
	rm -rf $(obj) $(PRJ_ROOT)/bin/$(BIN)
