#include "common.h"

int main() {
    int msgid;
    struct message_buffer message;
    int primes_received = 0;
    int evens_received = 0;
    int chars_received = 0;

    msgid = msgget(QUEUE_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("Error en msgget");
        exit(EXIT_FAILURE);
    }

    printf("Consumidor iniciado. Esperando mensajes...\n");

    // Esperamos 10 mensajes de cada uno
    while (primes_received < 10 || evens_received < 10 || chars_received < 10) {
        if (msgrcv(msgid, &message, sizeof(message) - sizeof(long), 0, 0) == -1) {
            perror("Error al recibir mensaje");
            exit(EXIT_FAILURE);
        }

        switch (message.msg_type) {
            case TYPE_PRIME:
                printf("[Consumidor] Recibido PRIMO: %d\n", message.int_val);
                primes_received++;
                break;
            case TYPE_EVEN:
                printf("[Consumidor] Recibido PAR: %d\n", message.int_val);
                evens_received++;
                break;
            case TYPE_CHAR:
                printf("[Consumidor] Recibido CARACTER: %c\n", message.char_val);
                chars_received++;
                break;
            default:
                printf("[Consumidor] Tipo desconocido: %ld\n", message.msg_type);
        }
    }

    printf("Todos los mensajes recibidos. Limpiando cola de mensajes...\n");

    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("Error al eliminar la cola");
        exit(EXIT_FAILURE);
    }

    printf("Consumidor finalizado exitosamente.\n");
    return 0;
}
