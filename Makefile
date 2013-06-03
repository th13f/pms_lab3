($(CROSS_COMPILE),)
all: arm
else
all: x86
endif

x86:
 @echo "Compiling for x86..."
 gcc -pthread -o server server.c
 gcc -o client client.c

arm:
 @echo "Compiling for ARM..."
 $(CROSS_COMPILE)gcc -pthread -o server_arm server.c
 $(CROSS_COMPILE)gcc -o client_arm client.c
