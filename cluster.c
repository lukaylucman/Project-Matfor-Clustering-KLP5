#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define jumlah_soal 12
#define jumlah_data 30
#define K_Means 3

double jarak_euclidean(double *titik_a, double *titik_b) {
    double jumlah = 0;
    for (int i = 0; i < jumlah_soal; i++) {
        double selisih = titik_a[i] - titik_b[i];
        jumlah += selisih * selisih;
    }
    return sqrt(jumlah);
}

int main() {

    char nama[jumlah_data][10] = {
        "MHS01","MHS02","MHS03","MHS04","MHS05",
        "MHS06","MHS07","MHS08","MHS09","MHS10",
        "MHS11","MHS12","MHS13","MHS14","MHS15",
        "MHS16","MHS17","MHS18","MHS19","MHS20",
        "MHS21","MHS22","MHS23","MHS24","MHS25",
        "MHS26","MHS27","MHS28","MHS29","MHS30"
    };

    double data_mhs[jumlah_data][jumlah_soal] = {
        {4, 4, 5, 4, 3, 4, 2, 3, 4, 5, 2, 3}, {5, 5, 5, 5, 3, 4, 5, 4, 5, 5, 3, 3},
        {4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 3, 4}, {4, 5, 3, 4, 5, 4, 3, 4, 5, 4, 4, 4},
        {5, 5, 5, 5, 4, 4, 1, 4, 4, 4, 5, 4}, {5, 5, 2, 5, 3, 5, 5, 2, 5, 5, 5, 3},
        {5, 4, 4, 5, 4, 4, 3, 4, 5, 5, 3, 4}, {5, 2, 4, 3, 4, 5, 2, 5, 5, 5, 5, 4},
        {4, 5, 4, 5, 2, 3, 1, 4, 3, 4, 2, 5}, {2, 3, 1, 3, 4, 5, 3, 5, 2, 4, 2, 1},
        {2, 4, 2, 1, 5, 4, 3, 5, 3, 2, 5, 1}, {4, 5, 3, 4, 4, 5, 4, 3, 4, 5, 5, 4},
        {5, 5, 4, 4, 5, 3, 5, 4, 3, 4, 4, 4}, {5, 2, 4, 5, 4, 3, 2, 5, 4, 2, 3, 2},
        {4, 3, 4, 3, 5, 3, 4, 4, 4, 5, 4, 5}, {4, 2, 3, 3, 3, 2, 3, 4, 3, 2, 3, 2},
        {2, 4, 3, 4, 4, 3, 2, 2, 5, 4, 5, 4}, {3, 4, 5, 4, 5, 3, 4, 5, 4, 3, 5, 3},
        {5, 4, 5, 5, 3, 4, 4, 4, 5, 4, 2, 2}, {3, 2, 3, 2, 4, 3, 4, 5, 3, 2, 3, 5},
        {1, 4, 2, 3, 5, 1, 5, 2, 2, 3, 4, 5}, {3, 4, 5, 3, 4, 4, 5, 2, 3, 3, 4, 3},
        {3, 2, 4, 3, 2, 3, 1, 4, 5, 2, 1, 2}, {2, 3, 2, 3, 3, 4, 3, 4, 5, 5, 4, 5},
        {2, 3, 4, 3, 5, 4, 4, 2, 3, 4, 4, 3}, {1, 1, 1, 1, 1, 1, 2, 1, 5, 4, 2, 5},
        {5, 5, 4, 5, 3, 1, 2, 2, 1, 4, 5, 1}, {5, 5, 5, 5, 5, 5, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2}, {4, 3, 3, 5, 4, 4, 3, 5, 5, 1, 5, 4}
    };

    double centroid[K_Means][jumlah_soal];
    int cluster_awal[K_Means] = {0, 14, 29};

    for(int i = 0; i < K_Means; i++){
        for(int j = 0; j < jumlah_soal; j++){
            centroid[i][j] = data_mhs[cluster_awal[i]][j];
        }
    }

    int cluster[jumlah_data];
    int cluster_lama[jumlah_data];

    for(int i = 0; i < jumlah_data; i++){
        cluster[i] = -1;
        cluster_lama[i] = -1;
    }

    int perubahan = 1;
    int iterasi = 0;

    // K-Means
    while(perubahan){
        iterasi++;

        for(int i = 0; i < jumlah_data; i++) {
            cluster_lama[i] = cluster[i];
        }

        // Memasukan mahasiswa ke cluster terdekat
        for(int i = 0; i < jumlah_data; i++){
            double jarak_terdekat = jarak_euclidean(data_mhs[i], centroid[0]);
            int cluster_terdekat = 0;
            for(int k = 1; k < K_Means ; k++){
                double jarak = jarak_euclidean(data_mhs[i],centroid[k]);
                if(jarak < jarak_terdekat){
                    jarak_terdekat = jarak;
                    cluster_terdekat = k;
                }
            }
            cluster[i] = cluster_terdekat;
        }

        //Geser pusat kelompok berdasarkan rata2 nilai anggotanya
        for(int k = 0; k < K_Means;k++){
            double total[jumlah_soal];
            int anggota = 0;
            for(int i = 0; i < jumlah_data; i++){
                if(cluster[i] == k){
                    anggota++;
                    for(int s = 0; s < jumlah_soal; s++)
                        total[s] += data_mhs[i][s];
                }
            }
            if(anggota > 0){
                for(int s = 0; s < jumlah_soal; s++)
                    centroid[k][s] = total[s]/anggota;
            }
        }

        // validasi untuk posisi mahasiswa di dalam cluster
        perubahan = 0;
        for(int i = 0; i < jumlah_data; i++){
            if(cluster[i] != cluster_lama[i]){
                perubahan = 1;
                break;
            }
        }

        printf("\nIterasi %d\n", iterasi);
        printf("\n========================================\n");
        printf("          ITERASI KE-%d\n", iterasi);
        printf("========================================\n");

        for(int k = 0; k < K_Means; k++){

            int first = 1;
            int anggota_cluster = 0;

             printf("Cluster %d\n", k + 1);
             printf("Anggota : ");

             for(int i = 0; i < jumlah_data; i++){
                 if(cluster[i] == k){
                 anggota_cluster++;
                 if(!first)
                     printf(", ");
                     printf("%s", nama[i]);
                 first = 0;
        }
    }

    printf("\nJumlah anggota : %d mahasiswa\n", anggota_cluster);
    printf("----------------------------------------\n");
}
printf("\n");
printf("========================================\n");
printf("       HASIL K-MEANS TELAH SELESAI\n");
printf("========================================\n");
printf("Total Iterasi : %d\n", iterasi);
printf("Jumlah Cluster: %d\n", K_Means);
printf("Total Data    : %d Mahasiswa\n", jumlah_data);
printf("========================================\n");

for(int k = 0; k < K_Means; k++){

    int jumlah = 0;

    for(int i = 0; i < jumlah_data; i++){
        if(cluster[i] == k)
            jumlah++;
    }

    printf("Cluster %d -> %2d Mahasiswa\n", k + 1, jumlah);
}

printf("========================================\n");
printf("Program selesai.\n");
    }

    printf("Selesai! Total iterasi: %d\n",iterasi);
    return 0;
} 
