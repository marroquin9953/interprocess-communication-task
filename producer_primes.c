#include "common.h"

int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main() {
    int msgid;
    struct message_buffer message;

    // Obtener el ID de la cola de mensajes
    msgid = msgget(QUEUE_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("Error al crear la cola de mensajes");
        exit(EXIT_FAILURE);
    }

    message.msg_type = TYPE_PRIME;

    int count = 0;
    int num = 2;
    while (count < 10) {
        if (is_prime(num)) {
            message.int_val = num;
            if (msgsnd(msgid, &message, sizeof(message) - sizeof(long), 0) == -1) {
                perror("Error al enviar primo");
            } else {
                printf("Productor Primos: Enviado %d\n", num);
            }
            count++;
            sleep(1);
        }
        num++;
    }

    // Enviar mensaje de finalizacion (opcional o manejado por el consumidor)
    return 0;
}
