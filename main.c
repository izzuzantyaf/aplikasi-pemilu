#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////////////////////////////////////////////  DEKLARASI VARIABEL DAN STRUCT
int pilihan, i, jumlahPeserta, jumlahCalon, pass, size, ketemu, indexPilih, jumlahSuara, pilihanFilter;
char temp[32], userLogin[32], passwordLogin[32];

FILE *peserta;
FILE *kahim;
FILE *data;

struct pemilih
{
    char nama[32], nim[32], alamat[32], noHp[15], user[32], password[32], angkatan[32], statusPilih[32];
} psrt[101];

struct cln
{
    char nama[32], visiMisi[32];
    int suara;
    float persentase;
} calon[10];
/////////////////////////////////////////////////  DEKLARASI VARIABEL DAN STRUCT

/////////////////////////////////////////////////  REGISTRASI PESERTA
void regis()
{
    int j;
    i = 1;
    peserta = fopen("peserta.txt", "a+");
    rewind(peserta);
    while (fscanf(peserta, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", &jumlahPeserta, psrt[i].nama, psrt[i].nim, psrt[i].angkatan, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password, psrt[i].statusPilih) != EOF)
    {
        i++;
    }
    if (jumlahPeserta <= 101)
    {

        printf("Masukkan nama       : ");
        fflush(stdin);
        fgets(psrt[i].nama, 32, stdin);
        strtok(psrt[i].nama, "\n");

        printf("Masukkan NIM        : ");
        scanf("%s", &psrt[i].nim);

        printf("Masukkan angkatan   : ");
        scanf("%s", &psrt[i].angkatan);

        printf("Masukkan alamat     : ");
        fflush(stdin);
        fgets(psrt[i].alamat, 32, stdin);
        strtok(psrt[i].alamat, "\n");

        printf("Masukkan nomor HP   : ");
        scanf("%s", &psrt[i].noHp);

        printf("\nMasukkan username   : ");
        scanf("%s", &psrt[i].user);

        for (j = 1; j <= jumlahPeserta; j++)
        {
            if (strcmp(psrt[i].user, psrt[j].user) == 0)
            {
                while (strcmp(psrt[i].user, psrt[j].user) == 0)
                {
                    system("cls");
                    printf("\nMaaf username telah digunakan, silakan gunakan username yang berbeda\n");
                    printf("\nMasukkan nama       : %s", psrt[i].nama);
                    printf("\nMasukkan NIM        : %s", psrt[i].nim);
                    printf("\nMasukkan angkatan   : %s", psrt[i].angkatan);
                    printf("\nMasukkan alamat     : %s", psrt[i].alamat);
                    printf("\nMasukkan nomor HP   : %s", psrt[i].noHp);
                    printf("\nMasukkan username   : ");
                    scanf("%s", &psrt[i].user);
                }
            }
        }

        printf("Masukkan password   : ");
        scanf("%s", &psrt[i].password);

        strcpy(psrt[i].statusPilih, "belum_memilih");

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

                    strcpy(temp, psrt[i].angkatan);
                    strcpy(psrt[i].angkatan, psrt[i + 1].angkatan);
                    strcpy(psrt[i + 1].angkatan, temp);

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

                    strcpy(temp, psrt[i].statusPilih);
                    strcpy(psrt[i].statusPilih, psrt[i + 1].statusPilih);
                    strcpy(psrt[i + 1].statusPilih, temp);
                }
            }
        }
    }
    fclose(peserta);

    peserta = fopen("peserta.txt", "w+");

    for (i = 1; i <= jumlahPeserta; i++)
    {
        if (i == 1)
        {
            fprintf(peserta, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", i, psrt[i].nama, psrt[i].nim, psrt[i].angkatan, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password, psrt[i].statusPilih);
        }
        else
        {
            fprintf(peserta, "\n%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", i, psrt[i].nama, psrt[i].nim, psrt[i].angkatan, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password, psrt[i].statusPilih);
        }
    }
    fclose(peserta);
    system("cls");
    printf("Registrasi berhasil\n\n");
    system("pause");
}
/////////////////////////////////////////////////  REGISTRASI PESERTA

/////////////////////////////////////////////////  LOGIN
void login()
{
    peserta = fopen("peserta.txt", "r");
    ketemu = 0;
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
        while (fscanf(peserta, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", &jumlahPeserta, psrt[i].nama, psrt[i].nim, psrt[i].angkatan, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password, psrt[i].statusPilih) != EOF)
        {
            if (strcmp(userLogin, psrt[i].user) == 0 && strcmp(passwordLogin, psrt[i].password) == 0)
            {
                ketemu = 1;
                if (strcmp(psrt[i].statusPilih, "belum_memilih") == 0)
                {
                    ketemu = 2;
                    indexPilih = i;
                    printf("Login berhasil\n");
                }
                else
                {
                    printf("\nAnda telah menggunakan hak pilih anda\n\n");
                }
            }
            i++;
        }
        if (ketemu == 0)
        {
            printf("\nusername / password anda mungkin salah atau belum terdaftar sebagai pemilih\n\n");
        }
    }
    fclose(peserta);
}
/////////////////////////////////////////////////  LOGIN

/////////////////////////////////////////////////  TAMBAH CALON
void tambahCalon()
{
    kahim = fopen("calon.txt", "a+");
    i = 1;
    rewind(kahim);
    while (fscanf(kahim, "%d\n%s\t%d\n%s", &jumlahCalon, calon[i].nama, &calon[i].suara, calon[i].visiMisi) != EOF)
    {
        i++;
    }

    printf("Masukkan nama calon  : ");
    fflush(stdin);
    fgets(calon[i].nama, 32, stdin);
    strtok(calon[i].nama, "\n");

    printf("Masukkan visi & misi : ");
    fflush(stdin);
    fgets(calon[i].visiMisi, 32, stdin);
    strtok(calon[i].visiMisi, "\n");

    calon[i].suara = 0;

    if (i == 1)
    {
        fprintf(kahim, "%d\n%s\t%d\n%s", i, calon[i].nama, calon[i].suara, calon[i].visiMisi);
    }
    else
    {
        fprintf(kahim, "\n%d\n%s\t%d\n%s", i, calon[i].nama, calon[i].suara, calon[i].visiMisi);
    }

    fclose(kahim);

    printf("\nCalon berhasil ditambahkan\n\n");
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

    while (fscanf(kahim, "%d\n%s\t%d\n%s", &jumlahCalon, calon[i].nama, &calon[i].suara, calon[i].visiMisi) != EOF)
    {
        printf("%s\n", calon[i].nama);
        i++;
    }

    printf("Masukkan nama calon yang akan diubah : ");
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

    printf("\nMasukkan data yang baru\n");

    printf("Masukkan nama calon baru : ");
    scanf("%s", &calon[i].nama);

    printf("Masukkan visi & misi baru : ");
    scanf("%s", &calon[i].visiMisi);
    fclose(kahim);

    kahim = fopen("calon.txt", "w+");
    for (i = 1; i <= jumlahCalon; i++)
    {
        if (i == 1)
        {
            fprintf(kahim, "%d\n%s\t%d\n%s", jumlahCalon, calon[i].nama, calon[i].suara, calon[i].visiMisi);
        }
        else
        {
            fprintf(kahim, "\n%d\n%s\t%d\n%s", &jumlahCalon, calon[i].nama, calon[i].suara, calon[i].visiMisi);
        }
    }
    fclose(kahim);
    printf("Calon berhasil diedit\n\n");
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

    printf("Masukkan nama calon yang akan dihapus : ");
    scanf("%s", &namaCalonDihapus);

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
    while (fscanf(peserta, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", &jumlahPeserta, psrt[i].nama, psrt[i].nim, psrt[i].angkatan, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password, psrt[i].statusPilih) != EOF)
    {
        printf("%s\n", psrt[i].nama);
        i++;
    }
    printf("Masukkan nama peserta yang akan diubah : ");
    scanf("%s", &namaPesertaDiubah);
    for (i = 1; i <= jumlahPeserta; i++)
    {
        if (strcmp(namaPesertaDiubah, psrt[i].nama) == 0)
        {
            break;
        }
    }
    printf("\n1. Nama : %s\n2. NIM : %s\n3. Angkatan  : %s\n4. Alamat : %s\n5. No HP : %s\n6. Username : %s\n7. Password : %s", psrt[i].nama, psrt[i].nim, psrt[i].angkatan, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password);
    printf("\n\nMasukkan pilihan ubah : ");
    scanf("%d", &pilihanUbah);
    switch (pilihanUbah)
    {
    case 1:
        printf("Masukkan nama baru     : ");
        scanf("%s", &dataBaru);
        strcpy(psrt[i].nama, dataBaru);
        break;
    case 2:
        printf("Masukkan NIM baru      : ");
        scanf("%s", &dataBaru);
        strcpy(psrt[i].nim, dataBaru);
        break;
    case 3:
        printf("Masukkan angaktan baru : ");
        scanf("%s", &dataBaru);
        strcpy(psrt[i].angkatan, dataBaru);
        break;
    case 4:
        printf("Masukkan alamat baru   : ");
        scanf("%s", &dataBaru);
        strcpy(psrt[i].alamat, dataBaru);
        break;
    case 5:
        printf("Masukkan nomor hp baru : ");
        scanf("%s", &dataBaru);
        strcpy(psrt[i].noHp, dataBaru);
        break;
    case 6:
        printf("Masukkan username baru : ");
        scanf("%s", &dataBaru);
        strcpy(psrt[i].user, dataBaru);
        break;
    case 7:
        printf("Masukkan password baru : ");
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
            fprintf(peserta, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", i, psrt[i].nama, psrt[i].nim, psrt[i].angkatan, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password, psrt[i].statusPilih);
        }
        else
        {
            fprintf(peserta, "\n%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", i, psrt[i].nama, psrt[i].nim, psrt[i].angkatan, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password, psrt[i].statusPilih);
        }
    }
    fclose(peserta);
}
/////////////////////////////////////////////////  EDIT PESERTA

/////////////////////////////////////////////////  HAPUS PESERTA
void hapusPeserta()
{
    char namaPesertaDihapus[32];
    int j;
    i = 1;
    peserta = fopen("peserta.txt", "a+");
    while (fscanf(peserta, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", &jumlahPeserta, psrt[i].nama, psrt[i].nim, psrt[i].angkatan, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password, psrt[i].statusPilih) != EOF)
    {
        printf("%s\n", psrt[i].nama);
        i++;
    }
    printf("\nMasukkan nama peserta yang ingin dihapus : ");
    scanf("%s", &namaPesertaDihapus);
    for (i = 1; i <= jumlahPeserta; i++)
    {
        if (strcmp(namaPesertaDihapus, psrt[i].nama) == 0)
        {
            for (j = i; j < jumlahPeserta; j++)
            {
                strcpy(psrt[j].nama, psrt[j + 1].nama);
                strcpy(psrt[j].nim, psrt[j + 1].nim);
                strcpy(psrt[j].angkatan, psrt[j + 1].angkatan);
                strcpy(psrt[j].alamat, psrt[j + 1].alamat);
                strcpy(psrt[j].noHp, psrt[j + 1].noHp);
                strcpy(psrt[j].user, psrt[j + 1].user);
                strcpy(psrt[j].password, psrt[j + 1].password);
                strcpy(psrt[j].statusPilih, psrt[j + 1].statusPilih);
            }
        }
    }
    fclose(peserta);
    peserta = fopen("peserta.txt", "w+");
    for (i = 1; i < jumlahPeserta; i++)
    {
        if (i == 1)
        {
            fprintf(peserta, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", i, psrt[i].nama, psrt[i].nim, psrt[i].angkatan, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password, psrt[i].statusPilih);
        }
        else
        {
            fprintf(peserta, "\n%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", i, psrt[i].nama, psrt[i].nim, psrt[i].angkatan, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password, psrt[i].statusPilih);
        }
    }
    fclose(peserta);
}
/////////////////////////////////////////////////  HAPUS PESERTA

/////////////////////////////////////////////////  VOTE
void vote()
{
    int j = 1, pilihCalon, k;
    i = 1;

    kahim = fopen("calon.txt", "a+");
    rewind(kahim);
    while (fscanf(kahim, "%d\n%s\t%d\n%s", &jumlahCalon, calon[i].nama, &calon[i].suara, calon[i].visiMisi) != EOF)
    {
        printf("\n%d\n%s\n%s\n", jumlahCalon, calon[i].nama, calon[i].visiMisi);
        i++;
    }

    printf("\nMasukkan nomor urut calon untuk vote : ");
    scanf("%d", &pilihCalon);

    for (i = 1; i <= jumlahCalon; i++)
    {
        if (i == pilihCalon)
        {
            strcpy(psrt[indexPilih].statusPilih, "sudah_memilih");
            calon[i].suara++;
        }
    }

    if (strcmp(psrt[indexPilih].statusPilih, "belum_memilih") == 0)
    {
        printf("\nError...\n\n");
    }
    fclose(kahim);

    kahim = fopen("calon.txt", "w+");
    for (i = 1; i <= jumlahCalon; i++)
    {
        if (i == 1)
        {
            fprintf(kahim, "%d\n%s\t%d\n%s", i, calon[i].nama, calon[i].suara, calon[i].visiMisi);
        }
        else
        {
            fprintf(kahim, "\n%d\n%s\t%d\n%s", i, calon[i].nama, calon[i].suara, calon[i].visiMisi);
        }
    }
    fclose(kahim);

    peserta = fopen("peserta.txt", "w+");
    for (i = 1; i <= jumlahPeserta; i++)
    {
        if (i == 1)
        {
            fprintf(peserta, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", i, psrt[i].nama, psrt[i].nim, psrt[i].angkatan, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password, psrt[i].statusPilih);
        }
        else
        {
            fprintf(peserta, "\n%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", i, psrt[i].nama, psrt[i].nim, psrt[i].angkatan, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password, psrt[i].statusPilih);
        }
    }
    fclose(peserta);
    system("cls");
    printf("Terima kasih telah menggunakan hak pilih anda\n\n");
}
/////////////////////////////////////////////////  VOTE

/////////////////////////////////////////////////  STATISTIK
void statistik()
{
    i = 1;
    jumlahSuara = 0;
    kahim = fopen("calon.txt", "a+");
    while (fscanf(kahim, "%d\n%s\t%d\n%s", &jumlahCalon, calon[i].nama, &calon[i].suara, calon[i].visiMisi) != EOF)
    {
        jumlahSuara += calon[i].suara;
        i++;
    }
    for (i = 1; i <= jumlahCalon; i++)
    {
        if (jumlahSuara == 0)
        {
            printf("\n%s\t0.00 %%", calon[i].nama);
        }
        else
        {
            calon[i].persentase = ((float)calon[i].suara / jumlahSuara) * 100;
            printf("\n%s\t%.2f %%", calon[i].nama, calon[i].persentase);
        }
    }
    fclose(kahim);
    printf("\n\n");
}
/////////////////////////////////////////////////  STATISTIK

/////////////////////////////////////////////////  FILTER PESERTA
void filter()
{
    i = 1;
    peserta = fopen("peserta.txt", "a+");
    printf("\nFilter berdasarkan\n1. Angkatan 2016\n2. Angkatan 2017\n3. Angkatan 2018");
    printf("\n\nMasukkan pilihan : ");
    scanf("%d", &pilihanFilter);

    switch (pilihanFilter)
    {
    case 1:
        while (fscanf(peserta, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", &jumlahPeserta, psrt[i].nama, psrt[i].nim, psrt[i].angkatan, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password, psrt[i].statusPilih) != EOF)
        {
            if (strcmp(psrt[i].angkatan, "2016") == 0)
            {
                printf("\nNama     : %s\n", psrt[i].nama);
                printf("NIM      : %s\n", psrt[i].nim);
                printf("Angkatan : %s\n", psrt[i].angkatan);
                printf("Alamat   : %s\n", psrt[i].alamat);
                printf("Nomor Hp : %s\n", psrt[i].noHp);
                printf("Username : %s\n", psrt[i].user);
                printf("Password : %s\n", psrt[i].password);
            }
            i++;
        }
        break;
    case 2:
        while (fscanf(peserta, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", &jumlahPeserta, psrt[i].nama, psrt[i].nim, psrt[i].angkatan, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password, psrt[i].statusPilih) != EOF)
        {
            if (strcmp(psrt[i].angkatan, "2017") == 0)
            {
                printf("\nNama     : %s\n", psrt[i].nama);
                printf("NIM      : %s\n", psrt[i].nim);
                printf("Angkatan : %s\n", psrt[i].angkatan);
                printf("Alamat   : %s\n", psrt[i].alamat);
                printf("Nomor Hp : %s\n", psrt[i].noHp);
                printf("Username : %s\n", psrt[i].user);
                printf("Password : %s\n", psrt[i].password);
            }
            i++;
        }
        break;
    case 3:
        while (fscanf(peserta, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", &jumlahPeserta, psrt[i].nama, psrt[i].nim, psrt[i].angkatan, psrt[i].alamat, psrt[i].noHp, psrt[i].user, psrt[i].password, psrt[i].statusPilih) != EOF)
        {
            if (strcmp(psrt[i].angkatan, "2018") == 0)
            {
                printf("\nNama     : %s\n", psrt[i].nama);
                printf("NIM      : %s\n", psrt[i].nim);
                printf("Angkatan : %s\n", psrt[i].angkatan);
                printf("Alamat   : %s\n", psrt[i].alamat);
                printf("Nomor Hp : %s\n", psrt[i].noHp);
                printf("Username : %s\n", psrt[i].user);
                printf("Password : %s\n", psrt[i].password);
            }
            i++;
        }
        break;
    default:
        printf("\nMaaf pilihan anda salah\n");
        break;
    }
    fclose(peserta);
}
/////////////////////////////////////////////////  FILTER PESERTA

/////////////////////////////////////////////////  MENU ADMIN
void menuAdmin()
{
    int pilihanAdmin;
    system("cls");
    printf("Menu Admin\n");
    printf("1. Tambah calon\n2. Edit calon\n3. Hapus calon\n4. Tambah peserta\n5. Edit peserta\n6. Hapus peserta\n7. Statistik\n8. Filter suara\n9. Beranda\n\n");
    printf("Masukkan pilihan : ");
    scanf("%d", &pilihanAdmin);
    switch (pilihanAdmin)
    {
    case 1:
        tambahCalon();
        system("pause");
        menuAdmin();
        break;
    case 2:
        editCalon();
        system("pause");
        menuAdmin();
        break;
    case 3:
        hapusCalon();
        system("pause");
        menuAdmin();
        break;
    case 4:
        regis();
        system("pause");
        menuAdmin();
        break;
    case 5:
        editPeserta();
        system("pause");
        menuAdmin();
        break;
    case 6:
        hapusPeserta();
        system("pause");
        menuAdmin();
        break;
    case 7:
        statistik();
        system("pause");
        menuAdmin();
        break;
    case 8:
        filter();
        system("pause");
        menuAdmin();
        break;
    case 9:
        main();
        break;
    default:
        printf("\nError...\n\n");
        system("pause");
        menuAdmin();
    }
}
/////////////////////////////////////////////////  MENU ADMIN

/////////////////////////////////////////////////  PROGRAM UTAMA
int main()
{
    system("cls");
    printf("////////////////////////   PEMILIHAN UMUM KETUA HIMPUNAN   ////////////////////////");
    printf("\n1. Register\n2. Login");
    printf("\n\nMasukkan pilihan : ");
    scanf("%d", &pilihan);
    printf("\n");
    switch (pilihan)
    {
    case 1:
        regis();
        main();
        break;
    case 2:
        system("cls");
        login();
        if (ketemu == 2)
        {
            vote();
        }
        system("pause");
        main();
        break;
    default:
        printf("Pilihan salah\n\n");
        system("pause");
        main();
        break;
    }
    return 0;
}
/////////////////////////////////////////////////  PROGRAM UTAMA
