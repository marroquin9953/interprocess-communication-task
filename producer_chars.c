#include "common.h"
#include <time.h>

int main() {
    int msgid;
    struct message_buffer message;

    msgid = msgget(QUEUE_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("Error en msgget");
        exit(EXIT_FAILURE);
    }

    message.msg_type = TYPE_CHAR;
    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        message.char_val = 'A' + (rand() % 26);
        if (msgsnd(msgid, &message, sizeof(message) - sizeof(long), 0) == -1) {
            perror("Error al enviar caracter");
        } else {
            printf("Productor Caracteres: Enviado %c\n", message.char_val);
        }
        sleep(1);
    }

    return 0;
}
