#include <stdio.h>
#include <stdlib.h>
#include "Kütüphane.h"
#include "calisanMenu.h"
#define max_kisi 10

int menu() {
    int secim;
    printf(" \nCALISAN DEVAM TAKIP SISTEMI \n\n ");
    printf("1. Yetkili icin giris \n");
    printf("2. Personel icin giris \n");
    printf("3. Gunu artir \n");
    printf("4. Devam durumunu sil \n");
    printf("5. Guncel gunu sifirla \n");
    printf("6. Dosya ac \n");
    printf("7. Cikis yap \n");
    printf("Seciminiz: ");
    scanf("%d", &secim);


    return secim;
}

int main() {
    int secim;

    do {
        secim = menu();

        switch (secim) {
            case 1:
                parola();
                break;
            case 2:
                devam();
                break;
            case 3:
                gungecis();
                printf("Gun artirildi!\n");
                break;
            case 4:
                dosyasilme();
                break;
            case 5:
                sifirlaGun();
                printf("Gun sifirlandi...\n");
                break;
            case 6:
                dosyaAcma();
                printf("Dosya acildi...\n");
                break;
            case 7:
                dosyaKaydet();
                printf("Cikis yapiliyor...\n");
                break;
            default:
                printf("Gecersiz secim! Lutfen tekrar deneyin.\n");
        }


    } while (secim != 7);

    return 0;
}
