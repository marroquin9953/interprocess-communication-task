#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define QUEUE_KEY 1234
#define TYPE_PRIME 1
#define TYPE_EVEN 2
#define TYPE_CHAR 3
#define TYPE_END 4

struct message_buffer {
    long msg_type;
    int int_val;
    char char_val;
};

#endif
