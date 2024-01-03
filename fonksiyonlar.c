#include "Kütüphane.h"
#include <stdio.h>
#include <stdlib.h>
#define max_kisi 100
#include <string.h>
#define max_gun 31


int eklenenKisiSayisi=0; // bu değer ileride değişecek fakat program en baştan başladığında 0 olması gerekiyor

struct Kisi {
    char isim[50];
    int sicilNo;
    int gunler[max_gun];
} kisiler[max_kisi];

void dosyaAcma() {
    FILE *dosya = fopen("personel.txt", "r");
    if (dosya == NULL) {
        printf("Dosya acma hatasi!\n");
        return;
    }

    // Her bir personeli dosyadan oku ve kisiler dizisine yükle
    
    while (fscanf(dosya, "%s %d", kisiler[eklenenKisiSayisi].isim, &kisiler[eklenenKisiSayisi].sicilNo) == 2) {
        
        // Burada devam durumlarını okuyarak kisiler dizisine ekle
        
        for (int gun = 0; gun < max_gun; gun++) {
            fscanf(dosya, "%d", &kisiler[eklenenKisiSayisi].gunler[gun]);
        }
        eklenenKisiSayisi++;
    }

    fclose(dosya);
}

void dosyaKaydet() {
    FILE *dosya1 = fopen("devam_durumlar.txt", "w");
    if (dosya1 == NULL) {
        fprintf(stderr, "Dosya acma hatasi\n");
        return;
    }

    for (int i = 0; i < eklenenKisiSayisi; i++) {
        fprintf(dosya1, "%d ", kisiler[i].sicilNo);

        for (int gun = 0; gun < max_gun; gun++) {
            fprintf(dosya1, "%d ", kisiler[i].gunler[gun]);
        }

        fprintf(dosya1, "\n");
    }

    fclose(dosya1);
}

// kişinin devam durumunu güncelleyen fonksiyon

void devamDurumuGuncelle(int index, int gun, int durum) {
    kisiler[index].gunler[gun - 1] = durum;
}

// kişinin devam durumunu kontrol eden fonksiyon

int devamDurumuKontrol(int index, int gun) {
    return kisiler[index].gunler[gun - 1];
}

//yetkili tüm çalışanlar için devam raporunu 31 gün için istediğinde kisiler adlı dizide ilk kişiden itibaren sicil no, isim ve devam durumunu yazdıran fonksiyon

void raporOlustur() {
printf("Devam Raporu:\n");

    for (int i = 0; i < eklenenKisiSayisi; i++) {
        if (kisiler[i].sicilNo != 0) {
            printf("Isim: %s, Sicil No: %d, Devam Durumu: ", kisiler[i].isim, kisiler[i].sicilNo);

            // Devam durumlarını yazdır
            for (int gun = 0; gun < max_gun; gun++) {
                printf("%d ", devamDurumuKontrol(i, gun + 1));
            }

            printf("\n");
        }
    }
}

//yetkili menüsüne ulaşmak için girilmesi gereken şifre ve bu şifreyle girilen şifreyi karşılaştırıp aynı değerler ise menuye yönlendiren fonksiyon

void parola() {
    int dogru_sifre = 1234;
    int girilen_sifre;

    do {
        printf("Yetkili Menusune ulasmak icin 4 haneli sifreyi giriniz: ");
        scanf("%d", &girilen_sifre);

        if (girilen_sifre == dogru_sifre) {
            yetkiliMenu2();
            break;  // Doğru şifre girildiğinde while döngüsündenden çık
        } else {
            printf("Parolayi yanlis girdiniz, tekrar deneyiniz:\n");
        }
    } while (1);  // while(1) sonsuz döngüyü ifade eder if in içinde girip de break i görünce döngüden çıkılır
}


//burada ise her yeni kişi eklendiğinde dosyadaki sicil no nun sıfırlanmaması için yazdığımız,son sicil no yu dosyada tutması için yazılan fonksiyon

int sonSicilNoOku() {
    FILE *dosya = fopen("personel.txt", "r");
    if (dosya == NULL) {
        printf("Dosya acma hatasi!\n");
        return 0;
    }

    int sonSicilNo = 1000;    // personellerin sicil no larının okunaklı olması için belirlediğimiz başlangıç sicil numarası
    char isim[50];
    int sicilNo;

    //burada, dosya tarafından işaret edilen dosyadan bir satır okur,bir string (isim) ve bir tamsayı değeri (sicil no) okur, ikisi de dosyadan gelen değerlere atanır.
    
    while (fscanf(dosya, "%s %d", isim, &sicilNo) == 2) {
        sonSicilNo = sicilNo;
    }

    fclose(dosya);
    return sonSicilNo;
}

// bu fonksiyon ise yetkilinin personel eklemesine olanak sağlayan,eklediğinde ise o kişiye son sicil no ne ise bir fazlasını o kişiye atar ve kaydeder

void yeniKisiEkle() {
    FILE *dosya;
    dosya = fopen("personel.txt", "a"); // a modu dosya yok ise açar var ise üstüne yazar

    if (dosya == NULL) {
        printf("Dosya acma hatasi!\n");
        return;
    }

    // Dosyadaki son sicil numarasını oku
    
    int sonSicilNo = sonSicilNoOku();

    int kisiSayisi;
    printf("Kac kisi kayit edilecek? (en fazla %d): ", max_kisi - eklenenKisiSayisi);
    scanf("%d", &kisiSayisi);

    if (kisiSayisi > max_kisi - eklenenKisiSayisi) {
        printf("Hata: Maksimum kisi sayisini astiniz!\n");
        fclose(dosya);
        return;
    }

    int i;
    for (i = 0; i < kisiSayisi; i++) {
        printf("Lutfen %d. kisinin adini girin: ", i + 1);
        scanf("%s", kisiler[i].isim);

        // girilen kişinin sicil numarasını bir önceki personelin sicil numarasından bir sonraki değere ata
        
        kisiler[i].sicilNo = sonSicilNo + 1;

        // dosyaya kişi bilgilerini işle
        
        fprintf(dosya, "%s %d\n", kisiler[i].isim, kisiler[i].sicilNo);
        printf("Kisi kaydedildi! Isim: %s, Sicil No: %d\n", kisiler[i].isim, kisiler[i].sicilNo);
        eklenenKisiSayisi++; // her kişi eklendiğinde max kisi sayısından azaltarak şirketin kapasitesini aşmamasını sağlıyor
        // son sicil numarasını güncellemesini sağlıyor
       
        sonSicilNo = kisiler[i].sicilNo;
    }

    // Dosyayı kapat
    
    fclose(dosya);
}

//yetkili menunun seçim ekranını yazdıran fonksiyon

void yetkiliMenu2() {
    int yetkiliSecim;
    printf("Yetkili Menusune Hosgeldiniz\n\n");
    printf(" 1. Tum calisan icin rapor olustur: \n");
    printf(" 2. Yeni personel ekle: \n");
    printf(" Seciminiz:");
    scanf("%d", &yetkiliSecim);

    switch (yetkiliSecim) {
        case 1:
            raporOlustur();
            break;

        case 2:
            yeniKisiEkle();
            break;

        default:
            printf("Geçersiz seçim!\n");
            break;
    }
}


//personel ismini ve sicil nosunu girdiğinde o kişi için hangi gündelerse kisiler dizisindeki devam durumunu o gün için güncelliyor

int devam() {
    char arananIsim[50];
    int arananSicilNo;
    int durum = 0; // Default olarak 0

    FILE *dosya = fopen("personel.txt", "r");

    if (dosya == NULL) {
        printf("Dosya acma hatasi!\n");
        return 0;
    }

    int eslesme = 0; // aşağıda kontrol edilecek olan eşleşme durumu için gösterge

    // personelden aranan isim ve sicil numarasını al
    
    printf("Isminizi Girin: ");
    scanf("%s", arananIsim);

    printf("Sicil No'yu Girin: ");
    scanf("%d", &arananSicilNo);

    // dosyayı baştan sona oku ve eşleşmeyi ikili şekilde kontrol et
    
    for (int i = 0; i < eklenenKisiSayisi; i++) {

        //burada dosyadan 1 string 1 de integer değeri tarıyor ve tarama her ikisi için de başarılıysa 1+1=2 oluyor ve koşul sağlanıyor
        if (fscanf(dosya, "%s %d", kisiler[i].isim, &kisiler[i].sicilNo) == 2) {

            //burada ise dosyadan taradığı 1 string değeri ile personelden aldığı 1 string değerini ve dosyadan ve personelden aldığı integer değerlerini karşılaştırıyor
            if (kisiler[i].sicilNo != 0 && strcmp(kisiler[i].isim, arananIsim) == 0 && kisiler[i].sicilNo == arananSicilNo) {

                eslesme = 1; // isim ve sicil numarası eşleşiyor anlamına geliyor
                printf("%s için devam durumunu güncellemek için 1 tusuna basiniz: ", kisiler[i].isim);
                scanf("%d", &durum);

                // güncellenmiş devamDurumuGuncelle fonksiyonunu kullan
                devamDurumuGuncelle(i, okuGun(), durum);

                printf("Girisiniz tamamlandi\n");
                break;
            }
        } else {
            break;   // dosya sonuna gelindiği için döngüyü sonlandır
        }
    }

    //eğer eslesme değeri 0 ise, yani isim ve sicil numarası ile eşleşmemişse bu koşul sağlanır
   
    if (!eslesme) {
        printf("Yanlis sicil no veya isim girdiniz, tekrar deneyiniz\n");
    }

    fclose(dosya);
    return eslesme;
}


int okuGun() {
    FILE *gunler;
    int gun;

    gunler= fopen("gun.txt", "r");
    if (gunler== NULL) {
       
        // Dosya yoksa veya okuma hatası olursa, varsayılan olarak 1 günle başla
        return 1;
    }

    fscanf(gunler, "%d", &gun);
    fclose(gunler);

    return gun;
}
void sifirlaGun() {
    FILE *gunler;

    gunler = fopen("gun.txt", "w");
    if (gunler == NULL) {
        fprintf(stderr, "Dosya acma hatasi\n");
        return;
    }

    fprintf(gunler, "1");  // Güncel günü 1 olarak ayarla
    fclose(gunler);
}
void yazGun(int gun) {
    FILE *gunler;

    gunler = fopen("gun.txt", "w");
    if (gunler == NULL) {
        printf("Dosya yazma hatasi.\n");
        return;
    }

    fprintf(gunler, "%d", gun);
    fclose(gunler);
}

int gungecis() {
    int gun;

    // Gün sayısını dosyadan oku
    gun = okuGun();

    // Günü artır
    gun++;

    // Gün sayısını dosyaya yaz
    yazGun(gun);

    printf("Isleminiz basarili. Guncel gun: %d\n", gun);

    // Sadece güncel günün devam durumunu güncelle
    for (int i = 0; i < eklenenKisiSayisi; i++) {
        kisiler[i].gunler[gun - 1] = 0;  // Devamsız olarak işaretle (0)
    }

    return 0;
}

//
int dosyasilme(){
    FILE *dosya;
    // "dosya.txt" adlı dosyayı sıfırla (içeriğini sil)
    
    dosya= fopen("personel.txt","w");
    if (dosya== NULL) {
        fprintf(stderr, "Dosya acma hatasi\n");
        return 1;
    }
    fprintf(dosya, ""); // dosya içeriğini sıfırla

    fclose(dosya);

    printf("Dosyanin icerigi sifirlandi.\n");

    FILE *gunler;
    // "dosya.txt" adlı dosyayı sıfırla (içeriğini sil)
    gunler= fopen("gun.txt","w");
    if (gunler== NULL) {
        fprintf(stderr, "Dosya acma hatasi\n");
        return 1;
    }
    fprintf(gunler, ""); // içeriği sıfırla

    fclose(gunler);

    printf("Dosyanin icerigi sifirlandi.\n");

    return 0;

}
