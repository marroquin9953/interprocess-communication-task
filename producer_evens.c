#include "common.h"

int main() {
    int msgid;
    struct message_buffer message;

    msgid = msgget(QUEUE_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("Error en msgget");
        exit(EXIT_FAILURE);
    }

    message.msg_type = TYPE_EVEN;

    for (int i = 1; i <= 10; i++) {
        message.int_val = i * 2;
        if (msgsnd(msgid, &message, sizeof(message) - sizeof(long), 0) == -1) {
            perror("Error al enviar par");
        } else {
            printf("Productor Pares: Enviado %d\n", message.int_val);
        }
        sleep(1);
    }

    return 0;
}
