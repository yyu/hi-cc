CFLAGS := $(shell PKG_CONFIG_PATH="/usr/local/opt/curl/lib/pkgconfig" pkg-config --cflags libcurl)
CFLAGS += $(shell PKG_CONFIG_PATH="/usr/local/opt/curl/lib/pkgconfig" pkg-config --libs libcurl)

all:
	gcc $(CFLAGS) simple.c
