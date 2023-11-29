/****************************************************************************
**					SAKARYA ÜNİVERSİTESİ
**			         BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
**				    BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
**				          PROGRAMLAMAYA GİRİŞİ DERSİ
**
**				ÖDEV NUMARASI.............: Ödev 1
**				ÖĞRENCİ ADI...............: Selma ADIYAMAN
**				ÖĞRENCİ NUMARASI..........: B231210414
**				DERS GRUBU................: B Grubu
****************************************************************************/


#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

// Ogrenci isimli yapı veri tipi
struct Ogrenci {
    string isim;
    string soyisim;
    double vizeNotu;
    double odevNotu1;
    double odevNotu2;
    double kisaSinavNotu1;
    double kisaSinavNotu2;
    double yilSonuNotu;
    string harfNotu;
};

// Rastgele isim ve soyisim seçen fonksiyon
string rastgeleIsimSoyisim() {
    string isimler[] = { "Selma", "Hayrunnisa", "Fatma Zehra", "Ferhan Izgi", "Edanur", "Hulya"};
    string soyisimler[] = { "Adiyaman", "İsen", "Kotan", "Gumustop", "Ay", "Gunes" };
    string rastgeleIsim = isimler[rand() % 6];
    string rastgeleSoyisim = soyisimler[rand() % 6];
    return rastgeleIsim + " " + rastgeleSoyisim;
}

// Rastgele not üreten fonksiyon
double rastgeleNot(double min, double max ) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

// Notu harf sistemine çeviren fonksiyon
string notuHarfeCevir(double notu) {
    if (notu >= 90.00) {
        return "AA";
    }
    else if (notu >= 85.00) {
        return "BA";
    }
    else if (notu >= 80.00) {
        return "BB";
    }
    else if (notu >= 75.00) {
        return "CB";
    }
    else if (notu >= 65.00) {
        return "CC";
    }
    else if (notu >= 58.00) {
        return "DC";
    }
    else if (notu >= 50.00) {
        return "DD";
    }
    else if (notu >= 40.00) {
        return "FD";
    }
    else {
        return "FF";
    }
}

int main() {
    int ogrenciSayisi;
    cout << "Lutfen ogrenci sayisini girin: ";
    cin >> ogrenciSayisi;

    // Harf notu sayacı başlat
    int harf_notu_sayac['F' - 'A' + 1] = { 0 };

    // Vize, 1.ödev,2.ödev, 1. kısa sınav ve 2. kısa sınavın ağırlıkları kullanıcıdan alınır.
    double vizeAgirlik, odevAgirlik1, odevAgirlik2, kisaSinavAgirlik1, kisaSinavAgirlik2;
    cout << "Vize agirlik degerini giriniz (%): ";
    cin >> vizeAgirlik;
    cout << "1. Odevin agirlik degerini giriniz (%): ";
    cin >> odevAgirlik1;
    cout << "2. Odevin agirlik degerini giriniz (%): ";
    cin >> odevAgirlik2;
    cout << "1. Kisa sinavin agirlik degerini giriniz (%): ";
    cin >> kisaSinavAgirlik1;
    cout << "2. Kisa sinavin agirlik degerini giriniz (%): ";
    cin >> kisaSinavAgirlik2;

    // Geçme notu etkiis kullanıcıdan alınır.
    double gecmeNotuEtkisi;
    cout << "Yil ici puaninin gecme notuna etkisini girin (%): ";
    cin >> gecmeNotuEtkisi;

    vector<Ogrenci> ogrenciler;
    // Her bir öğrenciye rastgele not ataması yap
    for (int i = 0; i < ogrenciSayisi; ++i) {
        Ogrenci ogrenci;
        ogrenci.isim = rastgeleIsimSoyisim();        // Öğrenciye rastgele bir isim atama
        ogrenci.vizeNotu = rastgeleNot(80, 100);     // Öğrenciye rastgele bir vize notu atama (80 ile 100 arasında)
        ogrenci.odevNotu1 = rastgeleNot(50, 80);     // Öğrenciye rastgele bir odev1 notu atama (50 ile 80 arasında)
        ogrenci.odevNotu2 = rastgeleNot(50, 80);     // Öğrenciye rastgele bir odev2 notu atama (50 ile 80 arasında)
        ogrenci.kisaSinavNotu1 = rastgeleNot(0, 50); // Öğrenciye rastgele bir kisasınav1 notu atama (0 ile 50 arasında)
        ogrenci.kisaSinavNotu2 = rastgeleNot(0, 50); // Öğrenciye rastgele bir kisasinav2 notu atama (0 ile 50 arasında)

    // Ağırlıkları yüzde cinsinden kullanarak yıl sonu notunu hesapla
        ogrenci.yilSonuNotu
            = ogrenci.vizeNotu * vizeAgirlik / 100
            + ogrenci.odevNotu1 * odevAgirlik1 / 100
            + ogrenci.odevNotu2 * odevAgirlik2 / 100
            + ogrenci.kisaSinavNotu1 * kisaSinavAgirlik1 / 100
            + ogrenci.kisaSinavNotu2 * kisaSinavAgirlik2 / 100;

    // Yıl içi puanının geçme notuna etkisini hesapla

        ogrenci.yilSonuNotu /= (vizeAgirlik+ odevAgirlik1+ odevAgirlik2+ kisaSinavAgirlik1+ kisaSinavAgirlik2)/100;

    // Harf notunu belirle
        ogrenci.harfNotu = notuHarfeCevir(ogrenci.yilSonuNotu);

    // Harf notu sayacını güncelle
        harf_notu_sayac[ogrenci.harfNotu[0] - 'A']++;

        ogrenciler.push_back(ogrenci);
    }
    // Öğrenci bilgilerini yazdır
    for (const Ogrenci& ogrenci : ogrenciler) {
        cout << "Ogrencinin Adi Soyadi: " << ogrenci.isim << "\nVize: " << ogrenci.vizeNotu
            << "\n1.Odev Notu: " << ogrenci.odevNotu1 << "\n2.Odev Notu: " << ogrenci.odevNotu2
            << "\n1.Kisa Sinav Notu: " << ogrenci.kisaSinavNotu1 << "\n2.Kisa Sinav Notu: " << ogrenci.kisaSinavNotu2
            << "\nYil Sonu Notu: " << ogrenci.yilSonuNotu << "\nHarf Notu: " << ogrenci.harfNotu << endl;
    }
    // Sınıfın yıl sonu notlarının toplamı alınıyor.
    double sinifOrtalamasi = 0.0;
    for (const Ogrenci& ogrenci : ogrenciler) {
        sinifOrtalamasi += ogrenci.yilSonuNotu;
    }
    sinifOrtalamasi /= ogrenciSayisi;

    cout << "Sinif Ortalamasi: \n" << sinifOrtalamasi << endl;

    // Standart sapmayı hesaplıyor.
    double toplamKareFark = 0.0;
    for (const Ogrenci& ogrenci : ogrenciler) {
        toplamKareFark += pow(ogrenci.yilSonuNotu - sinifOrtalamasi, 2);
    }
    double standartSapma = sqrt(toplamKareFark / ogrenciSayisi);

    cout << "Standart Sapma: \n" << standartSapma << endl;
    // Sınıfın en yüksek en düşük notu hesaolanıyor.
    double enYuksekNot = ogrenciler[0].yilSonuNotu;
    double enDusukNot = ogrenciler[0].yilSonuNotu;
    for (const Ogrenci& ogrenci : ogrenciler) {
        if (ogrenci.yilSonuNotu > enYuksekNot) {
            enYuksekNot = ogrenci.yilSonuNotu;
        }
        if (ogrenci.yilSonuNotu < enDusukNot) {
            enDusukNot = ogrenci.yilSonuNotu;
        }
    }

    cout << "En Yuksek Not: \n" << enYuksekNot << "\nEn Dusuk Not: \n" << enDusukNot << endl;
    //  Harfin indeksi hesaplanıyor
    for (char harf = 'A'; harf <= 'F'; harf++) {
        int harf_indeksi = harf - 'A';
    // Her harf için oran hesaplanıyor. Harf notunun sınıf içindeki yüzdesi bulunuyor.
        double harf_orani = (static_cast<double>(harf_notu_sayac[harf_indeksi]) / ogrenciSayisi) * 100;

        cout << harf << " notundan " << harf_notu_sayac[harf_indeksi] << " adet var. Sinif yuzdesi: " << fixed << setprecision(2) << harf_orani << "%" << endl;
    }

    return 0;
}