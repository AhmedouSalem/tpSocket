#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock = 0;
    struct sockaddr_in server_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};

    // Créer un socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nErreur : Échec de la création du socket\n");
        return -1;
    }

    // Définir l'adresse du serveur
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    // Convertir l'adresse IP en format binaire
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        printf("\nErreur : Adresse invalide\n");
        return -1;
    }

    // Se connecter au serveur
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("\nErreur : Échec de la connexion\n");
        return -1;
    }

    // Envoyer un message
    send(sock, hello, strlen(hello), 0);
    printf("Message envoyé au serveur\n");

    // Recevoir la réponse
    read(sock, buffer, 1024);
    printf("Message reçu du serveur : %s\n", buffer);

    // Fermer le socket
    close(sock);
    return 0;
}
