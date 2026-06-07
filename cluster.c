// Pengelompokkan mahasiswa terhadap media pembelajaran yang berpengaruh
// pada ketertarikan mahasiswa Pendidikan Ilmu Komputer 2-A

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "data.c"

#define jumlah_soal 12
#define jumlah_data 30
#define K_Means 3

double jarak_euclidean(double *titik_a, double *titik_b) {
    double jumlah = 0;
    //menghitung data nilai mahasiswa 1
    for (int i = 0; i < jumlah_soal; i++) {
        double selisih = titik_a[i] - titik_b[i];
        jumlah += selisih * selisih;
    }
    return sqrt(jumlah);
}

int main() {
    int *pengelompokkan[jumlah_soal] = {
        no1, no2, no3, no4, no5,
        no6, no7, no8, no9, no10,
        no11, no12
    };

    //menukar jumlah mahasiswa dengan jumlah soal
    double data_mhs[jumlah_data][jumlah_soal];

    for (int s = 0; s < jumlah_soal; s++) {
        for (int m = 0; m < jumlah_data; m++) {
            data_mhs[m][s] = pengelompokkan[s][m];
        }
    }

    double centroid[K_Means][jumlah_soal];
    int cluster_awal[K_Means] = { 0, 14, 29 };

    for (int i = 0; i < K_Means; i++) { // 3
        int indeks_mhs = cluster_awal[i]; // 0 [0] 
        for (int j = 0; j < jumlah_soal; j++) { // 12
            centroid[i][j] = data_mhs[indeks_mhs][j];
        }
    }

    int cluster[jumlah_data];
    int cluster_lama[jumlah_data];

    for (int i = 0; i < jumlah_data; i++) {
        cluster[i] = -1;
        cluster_lama[i] = -1;
    }

    int iterasi = 0;
    int perubahan = 1;

    //K_Means
    while (perubahan) { // ketika true akan di ulang terus
        iterasi++;

        for (int i = 0; i < jumlah_data; i++) {
            cluster_lama[i] = cluster[i];
        }

        //Memasukkan mahasiswa ke cluster terdekat
        for (int i = 0; i < jumlah_data; i++) {
            double jarak_terkecil = jarak_euclidean(data_mhs[i], centroid[0]);
            int cluster_terdekat = 0;

            for (int k = 1; k < K_Means; k++) {
                double jarak = jarak_euclidean(data_mhs[i], centroid[k]);
                if (jarak < jarak_terkecil) {
                    jarak_terkecil = jarak;
                    cluster_terdekat = k;
                }
                cluster[i] = cluster_terdekat;
            }
        }

        //Geser pusat kelompok berdasarkan rata2 nilai anggotanya
        for (int k = 0; k < K_Means; k++) {
            int jumlah_anggota = 0;
            double total[jumlah_soal];

            for (int s = 0; s < jumlah_soal; s++) {
                total[s] = 0;
            }

            for (int i = 0; i < jumlah_data; i++) {
                if (cluster[i] == k) {
                    jumlah_anggota++;
                    for (int s = 0; s < jumlah_soal; s++) {
                        total[s] += data_mhs[i][s];
                    }
                } else {
                    jumlah_anggota = jumlah_anggota;
                }
            }

            if (jumlah_anggota > 0) {
                for (int s = 0; s < jumlah_soal; s++) {
                    centroid[k][s] = total[s] / jumlah_anggota;
                }
            } else {
                for (int s = 0; s < jumlah_soal; s++) {
                    centroid[k][s] = centroid[k][s];
                }
            }
        }

        // validasi untuk posisi mahasiswa di dalam cluster
        perubahan = 0;
        for (int i = 0; i < jumlah_data; i++) {
            if (cluster[i] !=  cluster_lama[i]) {
                perubahan = 1;
                break;
            } else {
                perubahan = perubahan;
            }
        }

        //menampilkan cluster
        for (int k = 0; k < K_Means; k++) {
            printf("Cluster %d: ", k + 1);
            
            int mhs_terakhir = -1;
            for (int i = 0; i < jumlah_data; i++) {
                if (cluster[i] == k) {
                    mhs_terakhir = i; 
                } else {
                    mhs_terakhir = mhs_terakhir;
                }
            }

            for (int i = 0; i < jumlah_data; i++) {
                if (cluster[i] == k) {
                    if (i == mhs_terakhir) {
                        printf("Mahasiswa %d.", i + 1);
                    } else {
                        printf("Mahasiswa %d, ", i + 1);
                    }
                } else {
                    int skip = 0;
                }
            }
            printf("\n");
        }
    }
    printf("Selesai! Total iterasi: %d\n\n", iterasi);
    
    return 0;
}
