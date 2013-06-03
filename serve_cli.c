#include <stdio.h>

void* serve_client(void* connection) {
    int conn = *((int*) connection);
    char* buffer;
    FILE* file;
    long size;

    file = fopen("transfer", "r");
    if (!file) {
        strcpy(buffer, "File not found, sorry.\n");
    } else {
        fseek(file, 0L, SEEK_END);
        size = ftell(file);
        fseek(file, 0L, SEEK_SET);
        printf("File size: %ld\n", size);
        buffer = (char*) malloc(sizeof(char) * size);
        fread(buffer, sizeof(char), size, file);
    }

    write(conn, buffer, strlen(buffer));
    printf("Client served.\n");
    close(conn);
}
