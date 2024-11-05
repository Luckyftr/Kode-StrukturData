#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

void tambahAwal(node **head);
void tambahTengah(node **head);
void tambahAkhir(node **head);
void hapusAwal(node **head);
void hapusTengah(node **head);
void hapusAkhir(node **head);
void cariData(node *head);
void tampilkanJumlah(node *head);
void tampilkanJumlahan(node *head);
void tranverse(node *head);

int main() {
    node *head = NULL;
    int pilih;

    do {
        system("cls");
        printf("Daftar pilihan :\n");
        printf("1. Tambah data di awal\n");
        printf("2. Tambah data di tengah\n");
        printf("3. Tambah data di akhir list\n");
        printf("4. Hapus data di awal list\n");
        printf("5. Hapus data di tengah list\n");
        printf("6. Hapus data di akhir list\n");
        printf("7. Cari data dalam list\n");
        printf("8. Tampilkan jumlah data di list\n");
        printf("9. Tampilkan hasil penjumlahan dari semua data di list\n");
        printf("10. Cetak isi list\n");
        printf("MASUKKAN PILIHAN (tekan 11 untuk keluar) : ");
        fflush(stdin);
        scanf("%d", &pilih);

        if (pilih == 1)
            tambahAwal(&head);
        else if (pilih == 2)
            tambahTengah(&head);
        else if (pilih == 3)
            tambahAkhir(&head);
        else if (pilih == 4)
            hapusAwal(&head);
        else if (pilih == 5)
            hapusTengah(&head);
        else if (pilih == 6)
            hapusAkhir(&head);
        else if (pilih == 7)
            cariData(head);
        else if (pilih == 8)
            tampilkanJumlah(head);
        else if (pilih == 9)
            tampilkanJumlahan(head);
        else if (pilih == 10) {
            tranverse(head);
            getch();
        }
    } while (pilih != 11);

    return 0;
}

void tambahAwal(node **head) {
    int bil;
    node *pNew, *tail;

    system("cls");
    printf("Masukkan bilangan : ");
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));
    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL;

        if (*head == NULL) {
            *head = pNew;
            pNew->next = *head;
        } else {
            tail = *head;
            while (tail->next != *head)
                tail = tail->next;

            pNew->next = *head;
            *head = pNew;
            tail->next = *head;
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

void tambahTengah(node **head) {
    int sebelum, sesudah, bil;
    node *pNew, *pCur, *pPrev;

    system("cls");
    tranverse(*head);
    printf("\nMasukkan nilai node sebelumnya : ");
    fflush(stdin);
    scanf("%d", &sebelum);
    printf("\nMasukkan nilai node sesudahnya : ");
    fflush(stdin);
    scanf("%d", &sesudah);
    printf("\nMasukkan bilangan yang ingin ditambahkan : ");
    fflush(stdin);
    scanf("%d", &bil);

    pCur = *head;
    pPrev = NULL;
    while (pCur->next != *head && pCur->data != sebelum) {
        pPrev = pCur;
        pCur = pCur->next;
    }

    if (pCur == NULL) {
        printf("\nNode sebelumnya tidak ditemukan");
        getch();
    } else {
        pNew = (node *)malloc(sizeof(node));
        pNew->data = bil;
        pNew->next = pCur->next;
        pCur->next = pNew;
        if (pNew->next == *head) {
            pNew->next = pNew; // Node terakhir menunjuk ke node awal
        }
    }
}

void tambahAkhir(node **head) {
    int bil;
    node *pNew, *tail;

 system("cls");
    printf("Masukkan bilangan : ");
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));
    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL;

        if (*head == NULL) {
            *head = pNew;
            pNew->next = *head;
        } else {
            tail = *head;
            while (tail->next != *head)
                tail = tail->next;

            tail->next = pNew;
            pNew->next = *head;
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

void hapusAwal(node **head) {
    node *pDel, *tail;

    if (*head == NULL) {
        printf("List kosong");
        getch();
    } else {
        pDel = *head;

        if (pDel->next == *head) {
            *head = NULL;
            free(pDel);
        } else {
            tail = *head;
            while (tail->next != *head)
                tail = tail->next;

            *head = pDel->next;
            tail->next = *head;
            free(pDel);
        }
    }
}

void hapusTengah(node **head) {
    int bil;
    node *pCur, *pDel;

    system("cls");
    printf("Masukkan bilangan yang ingin dihapus : ");
    scanf("%d", &bil);

    if (*head == NULL) {
        printf("List kosong");
        getch();
    } else {
        pCur = *head;
        while (pCur->next != *head) {
            if (pCur->next->data == bil) {
                pDel = pCur->next;
                pCur->next = pDel->next;
                free(pDel);
                return;
            }
            pCur = pCur->next;
        }
        printf("Data tidak ditemukan");
        getch();
    }
}

void hapusAkhir(node **head) {
    node *pCur, *pDel;

    if (*head == NULL) {
        printf("List kosong");
        getch();
    } else if ((*head)->next == *head) {
        pDel = *head;
        *head = NULL;
        free(pDel);
    } else {
        pCur = *head;
        while (pCur->next->next != *head) {
            pCur = pCur->next;
        }
        pDel = pCur->next;
        pCur->next = *head;
        free(pDel);
    }
}

void cariData(node *head) {
    int bil;
    int index = 0;
    node *pWalker;

    system("cls");
    printf("Masukkan bilangan yang ingin dicari : ");
    scanf("%d", &bil);

    if (head == NULL) {
        printf("List kosong");
        getch();
    } else {
        pWalker = head;
        do {
            if (pWalker->data == bil) {
                printf("Data %d ditemukan pada index ke-%d", bil, index);
                getch();
                return;
            }
            pWalker = pWalker->next;
            index++;
        } while (pWalker != head);
        printf("Data tidak ditemukan");
        getch();
    }
}

void tampilkanJumlah(node *head) {
    int jumlah = 0;
    node *pWalker;

    if (head == NULL) {
        printf("List kosong\n");
        return;
    }

    pWalker = head;
    do {
        jumlah++;
        pWalker = pWalker->next;
    } while (pWalker != head);

    printf("Jumlah data di list: %d\n", jumlah);
    getch();
}

void tampilkanJumlahan(node *head) {
    int jumlahan = 0;
    node *pWalker;

    if (head == NULL) {
        printf("List kosong\n");
        return;
    }

    pWalker = head;
    do {
        jumlahan += pWalker->data;
        pWalker = pWalker->next;
    } while (pWalker != head);

    printf("Jumlahan data di list: %d\n", jumlahan);
    getch();
}

void tranverse(node *head) {
    node *pWalker;

    if (head == NULL) {
        printf("List kosong\n");
        return;
    }

    pWalker = head;
    do {
        printf("%d -> ", pWalker->data);
        pWalker = pWalker->next;
    } while (pWalker != head);

    printf("(Kembali ke head)\n");
    getch();
}
