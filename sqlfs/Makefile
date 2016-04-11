CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++

SQL3 = 3rdparty/sqlite3

CFLAGS += -I$(SQL3) -fPIC

default: libsqlfs.so $(SQL3)/sqlite

all: default sqlfscat sqlfsls

$(SQL3)/sqlite3.o: $(SQL3)/sqlite3.c
	$(CC) $(CFLAGS) -c -o $@ $^

$(SQL3)/libsqlite3.a: $(SQL3)/sqlite3.o
	$(AR) cr $@ $^

$(SQL3)/sqlite: $(SQL3)/shell.c $(SQL3)/libsqlite3.a
	$(CC) $(CFLAGS) -o $@ $^ -L$(SQL3) -lsqlite3 -lpthread -ldl

libsqlfs.so: sqlfs.c $(SQL3)/libsqlite3.a
	$(CC) $(CFLAGS) -o $@ -shared $^ -L$(SQL3) -lsqlite3

sqlfsls: sqlfsls.cpp libsqlfs.so
	$(CXX) $(CFLAGS) -o $@ sqlfsls.cpp -L. -lsqlfs -lpthread -ldl

sqlfscat: sqlfscat.c libsqlfs.so
	$(CC) $(CFLAGS) -o $@ sqlfscat.c -L. -lsqlfs -lpthread -ldl

clean:
	rm -f libsqlfs.so sqlfsls sqlfscat $(SQL3)/sqlite $(SQL3)/sqlite3.o $(SQL3)/libsqlite3.a

