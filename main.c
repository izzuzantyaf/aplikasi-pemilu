#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/////////////////////////////////////////////////  DEKLARASI VARIABEL DAN STRUCT
int pilihan, i, jumlahPeserta, jumlahCalon, pass, iTemp, size;
char temp[32], userLogin[32], passwordLogin[32];
FILE *peserta;
FILE *kahim;
FILE *data;

struct pemilih
{
    char nama[32], nim[32], alamat[32], noHp[15], user[32], password[32];
    bool statusPilih;
} psrt[100];

struct cln
{
    char nama[32], visiMisi[32];
} calon[10];
/////////////////////////////////////////////////  DEKLARASI VARIABEL DAN STRUCT

/////////////////////////////////////////////////  REGISTRASI PESERTA
void regis()
{
    peserta = fopen("peserta.txt", "a+");
    i = 1;
    rewind(peserta);
    while (fscanf(peserta, "%d\n%s\n%s\n%s\n%s\n%s\n%s", &jumlahPeserta, psrt[i].nama, psrt[i].nim, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password) != EOF)
    {
        i++;
    }
    if (jumlahPeserta <= 100)
    {

        printf("Masukkan nama       : ");
        fflush(stdin);
        fgets(psrt[i].nama, 32, stdin);
        strtok(psrt[i].nama, "\n");

        printf("Masukkan NIM        : ");
        scanf("%s", &psrt[i].nim);

        printf("Masukkan alamat     : ");
        fflush(stdin);
        fgets(psrt[i].alamat, 32, stdin);
        strtok(psrt[i].alamat, "\n");

        printf("Masukkan nomor HP   : ");
        scanf("%s", &psrt[i].noHp);

        printf("Masukkan username   : ");
        scanf("%s", &psrt[i].user);

        printf("Masukkan password   : ");
        scanf("%s", &psrt[i].password);

        //psrt[i].statusPilih = false;

        jumlahPeserta++;
    }

    if (jumlahPeserta >= 2)
    {
        for (pass = 1; pass < jumlahPeserta; pass++)
        {
            for (i = 1; i <= jumlahPeserta - pass; i++)
            {
                if (strcmp(psrt[i].nama, psrt[i + 1].nama) > 0)
                {
                    strcpy(temp, psrt[i].nama);
                    strcpy(psrt[i].nama, psrt[i + 1].nama);
                    strcpy(psrt[i + 1].nama, temp);

                    strcpy(temp, psrt[i].nim);
                    strcpy(psrt[i].nim, psrt[i + 1].nim);
                    strcpy(psrt[i + 1].nim, temp);

                    strcpy(temp, psrt[i].alamat);
                    strcpy(psrt[i].alamat, psrt[i + 1].alamat);
                    strcpy(psrt[i + 1].alamat, temp);

                    strcpy(temp, psrt[i].noHp);
                    strcpy(psrt[i].noHp, psrt[i + 1].noHp);
                    strcpy(psrt[i + 1].noHp, temp);

                    strcpy(temp, psrt[i].user);
                    strcpy(psrt[i].user, psrt[i + 1].user);
                    strcpy(psrt[i + 1].user, temp);

                    strcpy(temp, psrt[i].password);
                    strcpy(psrt[i].password, psrt[i + 1].password);
                    strcpy(psrt[i + 1].password, temp);
                }
            }
        }
    }
    fclose(peserta);

    peserta = fopen("peserta.txt", "w+");

    for (i = 1; i <= jumlahPeserta; i++)
    {
        if (i > 1)
        {
            fprintf(peserta, "\n%d\n%s\n%s\n%s\n%s\n%s\n%s", i, psrt[i].nama, psrt[i].nim, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password);
        }
        else
        {
            fprintf(peserta, "%d\n%s\n%s\n%s\n%s\n%s\n%s", i, psrt[i].nama, psrt[i].nim, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password);
        }
    }
    fclose(peserta);
}
/////////////////////////////////////////////////  REGISTRASI PESERTA

/////////////////////////////////////////////////  LOGIN
int login()
{
    peserta = fopen("peserta.txt", "r");
    bool ketemu = false;
    i = 1;
    printf("Masukkan username : ");
    scanf("%s", &userLogin);
    printf("Masukkan password : ");
    scanf("%s", &passwordLogin);
    if (strcmp(userLogin, "admin") == 0 && strcmp(passwordLogin, "1234") == 0)
    {
        menuAdmin();
    }
    else
    {
        while (fscanf(peserta, "%d\n%s\n%s\n%s\n%s\n%s\n%s", &jumlahPeserta, psrt[i].nama, psrt[i].nim, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password) != EOF)
        {
            if (strcmp(userLogin, psrt[i].user) == 0 && strcmp(passwordLogin, psrt[i].password) == 0)
            {
                ketemu = true;
                printf("login berhasil");
                //main();
                break;
            }
            i++;
        }
        if (ketemu == false)
        {
            printf("\nusername / password anda mungkin salah atau belum terdaftar sebagai pemilih");
            main();
        }
    }
    fclose(peserta);
    return 0;
}
/////////////////////////////////////////////////  LOGIN

/////////////////////////////////////////////////  TAMBAH CALON
void tambahCalon()
{
    kahim = fopen("calon.txt", "a+");
    i = 1;
    rewind(kahim);
    while (fscanf(kahim, "%d\n%s\n%s", &jumlahCalon, calon[i].nama, calon[i].visiMisi) != EOF)
    {
        //printf("%s", calon[i].nama);
        i++;
    }
    //i--;
    printf("masukkan nama calon  : ");
    fflush(stdin);
    fgets(calon[i].nama, 32, stdin);
    strtok(calon[i].nama, "\n");
    printf("masukkan visi & misi : ");
    fflush(stdin);
    fgets(calon[i].visiMisi, 32, stdin);
    strtok(calon[i].visiMisi, "\n");
    if (i == 1)
    {
        fprintf(kahim, "%d\n%s\n%s", i, calon[i].nama, calon[i].visiMisi);
    }
    else
    {
        fprintf(kahim, "\n%d\n%s\n%s", i, calon[i].nama, calon[i].visiMisi);
    }
    fclose(kahim);
}
/////////////////////////////////////////////////  TAMBAH CALON

/////////////////////////////////////////////////  EDIT CALON
void editCalon()
{
    int i;
    char namaCalonDiubah[32];
    kahim = fopen("calon.txt", "a+");
    i = 1;

    rewind(kahim);

    while (fscanf(kahim, "%d\n%s\n%s", &jumlahCalon, calon[i].nama, calon[i].visiMisi) != EOF)
    {
        printf("%s\n", calon[i].nama);
        printf("%d", jumlahCalon);
        i++;
    }

    printf("masukkan nama calon yang akan diubah : ");
    scanf("%s", &namaCalonDiubah);

    for (i = 1; i <= jumlahCalon; i++)
    {
        if (strcmp(namaCalonDiubah, calon[i].nama) == 0)
        {
            printf("%d", i);
            printf("%s\n%s", calon[i].nama, calon[i].visiMisi);
            break;
        }
    }

    printf("masukkan data yang baru\n");

    printf("masukkan nama calon baru : ");
    scanf("%s", &calon[i].nama);

    printf("masukkan visi & misi baru : ");
    scanf("%s", &calon[i].visiMisi);
    fclose(kahim);

    kahim = fopen("calon.txt", "w+");
    for (i = 1; i <= jumlahCalon; i++)
    {
        if (i == 1)
        {
            fprintf(kahim, "%d\n%s\n%s", i, calon[i].nama, calon[i].visiMisi);
        }
        else
        {
            fprintf(kahim, "\n%d\n%s\n%s", i, calon[i].nama, calon[i].visiMisi);
        }
    }
    fclose(kahim);
}
/////////////////////////////////////////////////  EDIT CALON

/////////////////////////////////////////////////  HAPUS CALON
void hapusCalon()
{
    int j;
    i = 1;
    kahim = fopen("calon.txt", "a+");
    char namaCalonDihapus[32];
    while (fscanf(kahim, "%d\n%s\n%s", &jumlahCalon, calon[i].nama, calon[i].visiMisi) != EOF)
    {
        printf("%s\n", calon[i].nama);
        i++;
    }
    printf("masukkan nama calon yang akan dihapus : ");
    scanf("%s", &namaCalonDihapus);
    //jumlahCalon--;
    for (i = 1; i <= jumlahCalon; i++)
    {
        if (strcmp(namaCalonDihapus, calon[i].nama) == 0)
        {
            for (j = i; j < jumlahCalon; j++)
            {
                strcpy(calon[j].nama, calon[j + 1].nama);
                strcpy(calon[j].visiMisi, calon[j + 1].visiMisi);
            }
            break;
        }
    }
    fclose(kahim);
    kahim = fopen("calon.txt", "w+");
    for (i = 1; i < jumlahCalon; i++)
    {
        if (i == 1)
        {
            fprintf(kahim, "%d\n%s\n%s", i, calon[i].nama, calon[i].visiMisi);
        }
        else
        {
            fprintf(kahim, "\n%d\n%s\n%s", i, calon[i].nama, calon[i].visiMisi);
        }
    }
    fclose(kahim);
}
/////////////////////////////////////////////////  HAPUS CALON

/////////////////////////////////////////////////  EDIT PESERTA
void editPeserta()
{
    int i, pilihanUbah;
    char namaPesertaDiubah[32], dataBaru[32];
    peserta = fopen("peserta.txt", "a+");
    i = 1;
    rewind(peserta);
    while (fscanf(peserta, "%d\n%s\n%s\n%s\n%s\n%s\n%s", &jumlahPeserta, psrt[i].nama, psrt[i].nim, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password) != EOF)
    {
        printf("%s\n", psrt[i].nama);
        //printf("%d", jumlahCalon);
        i++;
    }
    printf("masukkan nama peserta yang akan diubah : ");
    scanf("%s", &namaPesertaDiubah);
    for (i = 1; i <= jumlahPeserta; i++)
    {
        if (strcmp(namaPesertaDiubah, psrt[i].nama) == 0)
        {
            break;
        }
    }
    printf("\n1 Nama : %s\n2 NIM : %s\n3 Alamat : %s\n4 Nomor HP : %s\n5 Username : %s\n6 Password : %s", psrt[i].nama, psrt[i].nim, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password);
    printf("\n\nmasukkan pilihan ubah : ");
    scanf("%d", &pilihanUbah);
    switch (pilihanUbah)
    {
    case 1:
        printf("masukkan nama baru : ");
        scanf("%s", &dataBaru);
        strcpy(psrt[i].nama, dataBaru);
        break;
    case 2:
        printf("masukkan NIM baru : ");
        scanf("%s", &dataBaru);
        strcpy(psrt[i].nim, dataBaru);
        break;
    case 3:
        printf("masukkan alamat baru : ");
        scanf("%s", &dataBaru);
        strcpy(psrt[i].alamat, dataBaru);
        break;
    case 4:
        printf("masukkan nomor hp baru : ");
        scanf("%s", &dataBaru);
        strcpy(psrt[i].noHp, dataBaru);
        break;
    case 5:
        printf("masukkan username baru : ");
        scanf("%s", &dataBaru);
        strcpy(psrt[i].user, dataBaru);
        break;
    case 6:
        printf("masukkan password baru : ");
        scanf("%s", &dataBaru);
        strcpy(psrt[i].password, dataBaru);
        break;
    default:
        printf("pilihan salah\n");
        break;
    }
    fclose(peserta);
    peserta = fopen("peserta.txt", "w+");
    for (i = 1; i <= jumlahPeserta; i++)
    {

        if (i == 1)
        {
            fprintf(peserta, "%d\n%s\n%s\n%s\n%s\n%s\n%s", i, psrt[i].nama, psrt[i].nim, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password);
        }
        else
        {
            fprintf(peserta, "\n%d\n%s\n%s\n%s\n%s\n%s\n%s", i, psrt[i].nama, psrt[i].nim, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password);
        }
    }
    fclose(peserta);
}
/////////////////////////////////////////////////  EDIT PESERTA

/////////////////////////////////////////////////  HAPUS PESERTA
void hapusPeserta()
{
}
/////////////////////////////////////////////////  HAPUS PESERTA
void menuAdmin()
{
    int pilihanAdmin;
    printf("Menu Admin\n");
    printf("1. Tambah calon\n2. Edit calon\n3. Hapus calon\n4. Tambah peserta\n5. Edit peserta\n6. Hapus peserta\n7. Statistik\n8. Filter suara\n9. Beranda\n\n");
    printf("masukkan pilihan : ");
    scanf("%d", &pilihanAdmin);
    switch (pilihanAdmin)
    {
    case 1:
        tambahCalon();
        //system("cls");
        menuAdmin();
        break;
    case 2:
        editCalon();
        //system("cls");
        menuAdmin();
        break;
    case 3:
        hapusCalon();
        //system("cls");
        menuAdmin();
        break;
    case 4:
        regis();
        break;
    case 5:
        editPeserta();
        menuAdmin();
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        main();
        break;
    default:
        printf("pilihan salah\n");
    }
}

int main()
{
    printf("\n////////////////////////   PEMILIHAN UMUM KETUA HIMPUNAN   ////////////////////////");
    printf("\n1. Register\n2. Login");
    printf("\n\nMasukkan pilihan : ");
    scanf("%d", &pilihan);
    printf("\n");
    switch (pilihan)
    {
    case 1:
        regis();
        system("cls");
        main();
        break;
    case 2:
        login();
        break;
    default:
        printf("Pilihan salah\n");
        break;
    }

    return 0;
}
