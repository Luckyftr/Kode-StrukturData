#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char nama[50];
    char jenisKelamin;
    struct Node* pNext;
} Node;

Node* buatNode(char* nama, char jenisKelamin) {
    Node* pNew = (Node*)malloc(sizeof(Node));
    strcpy(pNew->nama, nama);
    pNew->jenisKelamin = jenisKelamin;
    pNew->pNext = NULL;
    return pNew;
}

int jumlahMahasiswa(Node* head) {
    int count = 0;
    if (head == NULL) return count;
    Node* pCur = head;
    do {
        count++;
        pCur = pCur->pNext;
    } while (pCur != head);
    return count;
}

void tambahMahasiswa(Node** head, char* nama, char jenisKelamin) {
    if (jumlahMahasiswa(*head) >= 20) {
        printf("Jumlah mahasiswa sudah mencapai batas maksimum (20).\n");
        return;
    }

    Node* pNew = buatNode(nama, jenisKelamin);
    if (*head == NULL) {
        *head = pNew;
        pNew->pNext = *head;
    } else {
        Node* pCur = *head;
        while (pCur->pNext != *head) {
            pCur = pCur->pNext;
        }
        pCur->pNext = pNew;
        pNew->pNext = *head;
    }
}

void hapusMahasiswa(Node** head, char* nama) {
    if (*head == NULL) {
        printf("Lingkaran kosong!\n");
        return;
    }

    Node* pCur = *head;
    Node* pPrev = NULL;

    if (strcmp(pCur->nama, nama) == 0 && pCur->pNext == *head) {
        free(pCur);
        *head = NULL;
        return;
    }

    while (strcmp(pCur->nama, nama) != 0) {
        pPrev = pCur;
        pCur = pCur->pNext;
        if (pCur == *head) {
            printf("%s tidak ditemukan di lingkaran.\n", nama);
            return;
        }
    }

    if (pCur == *head) {
        Node* terakhir = *head;
        while (terakhir->pNext != *head) {
            terakhir = terakhir->pNext;
        }
        *head = pCur->pNext;
        terakhir->pNext = *head;
    } else {
        pPrev->pNext = pCur->pNext;
    }

    free(pCur);
    printf("%s keluar dari lingkaran.\n", nama);
}

void tampilkan(Node* head) {
    if (head == NULL) {
        printf("Lingkaran kosong!\n");
        return;
    }

    Node* pCur = head;
    do {
        printf("%s(%c) -> ", pCur->nama, pCur->jenisKelamin);
        pCur = pCur->pNext;
    } while (pCur != head);
}

void siapaBernyanyi(Node* head, int langkah) {
    if (head == NULL) {
        printf("Lingkaran kosong!\n");
        return;
    }

    Node* pCur = head;
    for (int i = 0; i < langkah; i++) {
        pCur = pCur->pNext;
    }
    printf("Saat ini yang bernyanyi: %s\n", pCur->nama);
}

void pisahkanLingkaran(Node* head, Node** lingkaranMahasiswa, Node** lingkaranMahasiswi) {
    if (head == NULL) {
        printf("Lingkaran kosong!\n");
        return;
    }

    Node* pCur = head;
    do {
        if (pCur->jenisKelamin == 'L') {
            tambahMahasiswa(lingkaranMahasiswa, pCur->nama, pCur->jenisKelamin);
        } else {
            tambahMahasiswa(lingkaranMahasiswi, pCur->nama, pCur->jenisKelamin);
        }
        pCur = pCur->pNext;
    } while (pCur != head);
}


int cekPosisiCindy(Node* head) {
    if (head == NULL) {
        return 1;
    }

    Node* pCur = head;
    do {
        if (strcmp(pCur->nama, "Cindy") == 0) {
            return 0;
        }

        if (pCur->jenisKelamin == 'L' || pCur->pNext->jenisKelamin == 'L') {
            pCur = pCur->pNext;
            continue;
        }
        return 1;
    } while (pCur != head);

    return 0;
}


int cekCindyDiLingkaran(Node* head) {
    if (head == NULL) {
        return 0;
    }

    Node* pCur = head;
    do {
        if (strcmp(pCur->nama, "Cindy") == 0) {
            return 1;
        }
        pCur = pCur->pNext;
    } while (pCur != head);

    return 0;
}


int cekIrsyadArsyid(Node* head) {
    if (head == NULL) return 0;

    Node* pCur = head;
    int foundIrsyad = 0;
    int foundArsyid = 0;

    do {
        if (strcmp(pCur->nama, "Irsyad") == 0) foundIrsyad = 1;
        if (strcmp(pCur->nama, "Arsyid") == 0) foundArsyid = 1;
        pCur = pCur->pNext;
    } while (pCur != head);

    return foundIrsyad && foundArsyid;
}

int cekPosisiIrsyadArsyid(Node* head) {
    if (head == NULL) return 1;

    Node* pCur = head;
    do {
        if (strcmp(pCur->nama, "Irsyad") == 0) {
            if (strcmp(pCur->pNext->nama, "Arsyid") != 0) {
                return 0;
            }
        }
        pCur = pCur->pNext;
    } while (pCur != head);

    return 1;
}

void tambahDenganAturanCindy(Node** head, char* nama, char jenisKelamin) {
    if (strcmp(nama, "Cindy") == 0 && jenisKelamin == 'P') {
        if (cekPosisiCindy(*head)) {
            printf("Cindy aman untuk bergabung ke lingkaran.\n");
            tambahMahasiswa(head, nama, jenisKelamin);
        } else {
            printf("Tidak ada posisi yang aman untuk Cindy (di antara dua mahasiswi).\n");
        }
    } else if (strcmp(nama, "Irsyad") == 0) {
        tambahMahasiswa(head, nama, jenisKelamin);
        char arsyidNama[50];
        printf("Masukkan nama untuk Arsyid: ");
        scanf("%s", arsyidNama);
        tambahMahasiswa(head, arsyidNama, 'L');
    } else {
        tambahMahasiswa(head, nama, jenisKelamin);
    }
}

int main() {
    Node* lingkaran = NULL;
    Node* lingkaranMahasiswa = NULL;
    Node* lingkaranMahasiswi = NULL;
    int pilihan;
    char nama[50], jenisKelamin;
    int langkah;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Tambah mahasiswa/i ke lingkaran\n");
        printf("2. Hapus mahasiswa/i dari lingkaran\n");
        printf("3. Lihat siapa yang bernyanyi\n");
        printf("4. Tampilkan lingkaran\n");
        printf("5. Pisahkan lingkaran menjadi mahasiswa dan mahasiswi\n");
        printf("6. Cek apakah Cindy ada di lingkaran\n");
        printf("7. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &pilihan);

        if (pilihan == 1) {
            printf("Masukkan nama: ");
            scanf("%s", nama);
            printf("Masukkan jenis kelamin (L/P): ");
            scanf(" %c", &jenisKelamin);  // space before %c to ignore whitespace
            tambahDenganAturanCindy(&lingkaran, nama, jenisKelamin);

        } else if (pilihan == 2) {
            printf("Masukkan nama yang akan dihapus: ");
            scanf("%s", nama);
            hapusMahasiswa(&lingkaran, nama);

        } else if (pilihan == 3) {
            printf("Masukkan langkah untuk melihat siapa yang bernyanyi: ");
            scanf("%d", &langkah);
            siapaBernyanyi(lingkaran, langkah);

        } else if (pilihan == 4) {
            printf("\nLingkaran saat ini:\n");
            tampilkan(lingkaran);

        } else if (pilihan == 5) {
            pisahkanLingkaran(lingkaran, &lingkaranMahasiswa, &lingkaranMahasiswi);
            printf("\nLingkaran Mahasiswa:\n");
            tampilkan(lingkaranMahasiswa);
            printf("\nLingkaran Mahasiswi:\n");
            tampilkan(lingkaranMahasiswi);

        } else if (pilihan == 6) {
            if (cekCindyDiLingkaran(lingkaran)) {
                printf("Cindy ada di lingkaran.\n");
            } else {
                printf("Cindy tidak ada di lingkaran.\n");
            }

        } else if (pilihan == 7) {
            printf("Keluar program.\n");
            exit(0);

        } else {
            printf("Pilihan tidak valid.\n");
        }
    }

    return 0;
}
