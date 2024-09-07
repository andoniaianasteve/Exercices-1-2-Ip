#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Fonction pour vérifier si une chaîne est un nombre valide
int is_digit_string(const char *str) {
    while (*str) {
        if (*str < '0' || *str > '9') return (0);
        str++;
    }
    return (1);
}

// Fonction pour vérifier si l'adresse IP est valide
int is_valid_ip(const char *ip) {
    int octets[4];
    int count = sscanf(ip, "%d.%d.%d.%d", &octets[0], &octets[1], &octets[2], &octets[3]);
    //printf("IP=%d\n", count);

    if (count != 4) return (0);

    for (int i = 0; i < 4; i++) {
        if (octets[i] < 0 || octets[i] > 255) return (0);
    }
    return (1);
}

// Fonction pour vérifier si le masque de sous-réseau est valide
int is_valid_subnet_mask(const char *mask) {
    int mask_value[4];
    int count = sscanf(mask, "%d.%d.%d.%d", &mask_value[0], &mask_value[1], &mask_value[2], &mask_value[3]);
    //printf("mask=%d\n", count);

    if (count != 4) return (0);

    char A[]="255.0.0.0",
        B[]="255.255.0.0",
        C[]="255.255.255.0";
    int valid=0;

    
    if(strcmp(mask, A)==0){
        valid=1;
        for (int i = 0; i < 4; i++) {
            if (mask_value[i] < 0 || mask_value[i] > 255) return (0);
        }
    }else if(strcmp(mask, B)==0){
        valid=1;
        for (int i = 0; i < 4; i++) {
            if (mask_value[i] < 0 || mask_value[i] > 255) return (0);
        }
    }else if(strcmp(mask, C)==0){
        valid=1;
        for (int i = 0; i < 4; i++) {
            if (mask_value[i] < 0 || mask_value[i] > 255) return (0);
        }
    }else{
        valid=0;
        printf("Erreur de MSR\n");
        //return (0);
    }
    if(valid!=1){
        return (0);
    }else{
        return (4);
    }
    printf("%s", mask);
}

// Fonction pour obtenir la classe de l'adresse IP
char get_ip_class(const char *ip) {
    int first_octet;
    sscanf(ip, "%d", &first_octet);

    if (first_octet >= 1 && first_octet <= 126) return 'A';
    if (first_octet >= 128 && first_octet <= 191) return 'B';
    if (first_octet >= 192 && first_octet <= 223) return 'C';
    return 'N'; // Not a standard class (D & E)
}

// Fonction pour calculer l'adresse de l'émetteur du réseau
void calculate_network_address(const char *ip, const char *mask, char *network_address) {
    int ip_octets[4], mask_octets[4];
    sscanf(ip, "%d.%d.%d.%d", &ip_octets[0], &ip_octets[1], &ip_octets[2], &ip_octets[3]);
    sscanf(mask, "%d.%d.%d.%d", &mask_octets[0], &mask_octets[1], &mask_octets[2], &mask_octets[3]);

    int network_octets[4];
    for (int i = 0; i < 4; i++) {
        network_octets[i] = ip_octets[i] & mask_octets[i];
    }

    sprintf(network_address, "%d.%d.%d.%d", network_octets[0], network_octets[1], network_octets[2], network_octets[3]);
}

// Fonction pour calculer le nombre d'adresses IP utilisables
int calculate_usable_ips(const char *mask) {
    int mask_octets[4];
    sscanf(mask, "%d.%d.%d.%d", &mask_octets[0], &mask_octets[1], &mask_octets[2], &mask_octets[3]);

    int mask_int = 0;
    for (int i = 0; i < 4; i++) {
        mask_int |= (mask_octets[i] << (24 - 8 * i));
    }

    // Nombre de bits à 0 dans le masque pour le calcul des adresses
    int host_bits = 0;
    for (int i = 0; i < 32; i++) {
        if ((mask_int & (1 << i)) == 0) host_bits++;
    }

    // Nombre total d'adresses IP = 2^host_bits
    int total_ips = 1 << host_bits;

    // Soustraire les adresses de réseau et de diffusion
    return (total_ips - 2);
}

//appel du fonction

char display(){
    char ip[16];
    char mask[16];
    char network_address[16];

    printf("Entrez l'adresse IP: ");
    scanf("%15s", ip);
    printf("Entrez le masque de sous-réseau: ");
    scanf("%15s", mask);

    if (!is_valid_ip(ip)) {
        printf("Adresse IP invalide.\n");
        return (1);
    }else if (is_valid_subnet_mask(mask)!=4) {
        printf("Masque de sous-réseau invalide.%d\n", is_valid_subnet_mask(mask));
        return (1);
    }
    printf("\n*********************************************************\n\n");
    printf("Adresse IP valide.\n");
    printf("Classe de l'adresse IP: %c\n", get_ip_class(ip));

    calculate_network_address(ip, mask, network_address);
    printf("Adresse de l'émetteur du réseau: %s\n", network_address);

    int usable_ips = calculate_usable_ips(mask);
    printf("Nombre d'adresses IP utilisables: %d\n", usable_ips);

    printf("\n*********************************************************\n");
}

int main() {
    display();
    return 0;
}
