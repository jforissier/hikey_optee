WITH_LIBFUSE = 1

CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++

SQL3 = 3rdparty/sqlite3

ifeq ($(WITH_LIBFUSE),1)
CFLAGS_LIBFUSE = -DHAVE_LIBFUSE -DFUSE_USE_VERSION=30 \
			-I$(LIBFUSE_PATH)/include/fuse3
LDFLAGS_LIBFUSE = -L$(LIBFUSE_PATH)/lib -lfuse3
endif

CFLAGS += $(CFLAGS_LIBFUSE) -I. -I$(SQL3) -fPIC
LDFLAGS_LIBSQLFS = -L. -lsqlfs $(LDFLAGS_LIBFUSE)

all: libsqlfs.so $(SQL3)/sqlite
all: sqlfscat sqlfsls sqlfstest
ifeq ($(WITH_LIBFUSE),1)
all: fuse_sqlfs
endif

$(SQL3)/sqlite3.o: $(SQL3)/sqlite3.c
	$(CC) $(CFLAGS) -c -o $@ $^

$(SQL3)/libsqlite3.a: $(SQL3)/sqlite3.o
	$(AR) cr $@ $^

$(SQL3)/sqlite: $(SQL3)/shell.c $(SQL3)/libsqlite3.a
	$(CC) $(CFLAGS) -o $@ $^ -L$(SQL3) -lsqlite3 -lpthread -ldl

libsqlfs.so: sqlfs.c $(SQL3)/libsqlite3.a
	$(CC) $(CFLAGS) -o $@ -shared $^ -L$(SQL3) -lsqlite3

fuse_sqlfs: fuse_sqlfs.c libsqlfs.so
	$(CC) $(CFLAGS) -o $@ fuse_sqlfs.c $(LDFLAGS_LIBSQLFS) -lpthread -ldl

sqlfsls: sqlfsls.cpp libsqlfs.so
	$(CXX) $(CFLAGS) -o $@ sqlfsls.cpp -static-libstdc++ -static-libgcc $(LDFLAGS_LIBSQLFS) -lpthread -ldl

sqlfscat: sqlfscat.c libsqlfs.so
	$(CC) $(CFLAGS) -o $@ sqlfscat.c $(LDFLAGS_LIBSQLFS) -lpthread -ldl

sqlfstest: sqlfstest.c libsqlfs.so
	$(CC) $(CFLAGS) -o $@ sqlfstest.c $(LDFLAGS_LIBSQLFS) -lpthread -ldl

clean:
	rm -f libsqlfs.so sqlfsls sqlfscat $(SQL3)/sqlite $(SQL3)/sqlite3.o $(SQL3)/libsqlite3.a

