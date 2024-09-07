#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour vérifier si une adresse IP est valide
int est_ip_valide(const char *ip) {
    int octets[4];
    return sscanf(ip, "%d.%d.%d.%d", &octets[0], &octets[1], &octets[2], &octets[3]) == 4 &&
           octets[0] >= 0 && octets[0] <= 255 &&
           octets[1] >= 0 && octets[1] <= 255 &&
           octets[2] >= 0 && octets[2] <= 255 &&
           octets[3] >= 0 && octets[3] <= 255;
}

// Fonction pour convertir une adresse IP en entier
unsigned int ip_to_int(const char *ip) {
    int octets[4];
    sscanf(ip, "%d.%d.%d.%d", &octets[0], &octets[1], &octets[2], &octets[3]);
    return (octets[0] << 24) | (octets[1] << 16) | (octets[2] << 8) | octets[3];
}

// Fonction pour convertir un entier en adresse IP
void int_to_ip(unsigned int ip, char *buffer) {
    sprintf(buffer, "%d.%d.%d.%d",
        (ip >> 24) & 0xFF,
        (ip >> 16) & 0xFF,
        (ip >> 8) & 0xFF,
        ip & 0xFF);
}

// Fonction pour vérifier si le CIDR est valide (entre 0 et 32)
int est_cidr_valide(int cidr) {
    return cidr >= 0 && cidr <= 32;
}

// Fonction pour calculer le masque de sous-réseau
unsigned int calculer_masque_cidr(int cidr) {
    return (cidr == 0) ? 0 : ~((1 << (32 - cidr)) - 1);
}
char display(){
    char ip[16];
    int cidr;
    unsigned int masque;
    unsigned int ip_uint;
    unsigned int reseau;
    unsigned int diffusion;
    char buffer[16];

    printf("Entrez une adresse IP (au format xxx.xxx.xxx.xxx) : ");
    scanf("%15s", ip);

    if (!est_ip_valide(ip)) {
        printf("Adresse IP invalide.\n");
        return (1);
    }

    // Convertir l'adresse IP en entier
    ip_uint = ip_to_int(ip);

    printf("Entrez le CIDR (un entier entre 0 et 32) : ");
    scanf("%d", &cidr);

    if (!est_cidr_valide(cidr)) {
        printf("CIDR invalide.\n");
        return (1);
    }

    // Calculer le masque de sous-réseau
    masque = calculer_masque_cidr(cidr);

    // Calculer l'adresse du réseau
    reseau = ip_uint & masque;

    // Calculer l'adresse de diffusion
    diffusion = reseau | ~masque;

    // Convertir et afficher les résultats
    int_to_ip(ip_uint, buffer);
    printf("Adresse IP : %s\n", buffer);

    int_to_ip(masque, buffer);
    printf("Masque de sous-réseau : %s\n", buffer);

    int_to_ip(reseau, buffer);
    printf("Adresse du réseau : %s\n", buffer);

    int_to_ip(diffusion, buffer);
    printf("Adresse de diffusion : %s\n", buffer);
}
// Fonction principale
int main() {
    display();
    return 0;
}
