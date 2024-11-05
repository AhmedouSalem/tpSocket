#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024] = {0};
    int addrlen = sizeof(client_addr);

    // Créer un socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Échec de la création du socket");
        exit(EXIT_FAILURE);
    }

    // Définir l'adresse et le port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    // Associer le socket
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Échec de l'association");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Écouter les connexions
    if (listen(server_fd, 3) < 0) {
        perror("Échec de l'écoute");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    printf("Serveur en écoute sur le port 8080...\n");

    // Accepter une connexion
    if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t*)&addrlen)) < 0) {
        perror("Échec de l'acceptation");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Recevoir un message
    recv(client_fd, buffer, 1024, 0);
    printf("Message reçu du client : %s\n", buffer);

    // Répondre au client
    char *hello = "Hello from server";
    send(client_fd, hello, strlen(hello), 0);
    printf("Message envoyé au client\n");

    // Fermer la connexion
    close(client_fd);
    close(server_fd);
    return 0;
}
