#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//========================================================

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

//membuat node
void tambahAwal(node **head);
void tambahData(node **head);
void tambahAkhir(node **head);
void hapusAwal(node **head);
void hapusTengah(node **head);
void hapusAkhir(node **head);
void cariData(node *head);
void tampilkanJumlah(node *head);
void tampilkanJumlahan(node *head);
void tranverse(node *head);

//========================================================

int main()
{
    node *head;
    int pilih;

    head = NULL;
    do {
        system("cls");
        printf("masukkan pilihan\n");
        printf("1. tambah data di awal\n");
        printf("2. tambah data di tengah list\n");
        printf("3. tambah data di akhir list\n");
        printf("4. hapus data di awal list\n");
        printf("5. hapus data di tengah list\n");
        printf("6. hapus data di akhir list\n");
        printf("7. cari data dalam list\n");
        printf("8. tampilkan jumlah data di list\n");
        printf("9. tampilkan hasil penjumlahan dari semua data di list\n");
        printf("10. cetak isi list\n");
        printf("MASUKKAN PILIHAN (tekan 11 untuk keluar) : ");
        fflush(stdin);
        scanf("%d", &pilih);
        if (pilih == 1)
            tambahAwal(&head);
        else if (pilih == 2)
            tambahData(&head);
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

//========================================================

void tambahAwal(node **head) {
    int bil;
    node *pNew;

    system("cls");
    fflush(stdin);
    printf("masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL;
        //add before first logical node or to an empty list
        pNew->next = *head;
        *head = pNew;
    }
    else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void tambahData(node **head) {
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*head);
    printf("\nposisi penyisipan setelah data bernilai : ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nbilangan : ");
    fflush(stdin);
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
    }

    pNew = (node *)malloc(sizeof(node));

    if (pCur == NULL) {
        printf("\nnode tidak ditemukan");
        getch();
    }
    else if (pNew == NULL) {
        printf("\nalokasi memeori gagal");
        getch();
    }
    else {
        pNew->data = bil;
        pNew->next = NULL;
        pNew->next = pCur->next;
        pCur->next = pNew;
    }
}

//========================================================

void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    fflush(stdin);
    printf("masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL ;

        if (*head == NULL) {
            *head = pNew;
        }
        else {
            pCur = *head;
            while (pCur->next != NULL) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
        }
    }
    else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void hapusAwal(node **head) {
    node *pDel;

    if (*head == NULL) {
        printf("List kosong");
        getch();
    }
    else {
        pDel = *head;
        *head = (*head)->next;
        free(pDel);
    }
}

//========================================================

void hapusTengah(node **head) {
    int pos;
    node *pCur, *pDel;

    system("cls");
    tranverse(*head);
    printf("\nposisi penghapusan data bernilai : ");
    fflush(stdin);
    scanf("%d", &pos);

    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
    }

    if (pCur == NULL) {
        printf("\nnode tidak ditemukan");
        getch();
    }
    else {
        pDel = pCur;
        pCur = *head;
        while (pCur->next != pDel) {
            pCur = pCur->next;
        }
        pCur->next = pDel->next;
        free(pDel);
    }
}

//========================================================

void hapusAkhir(node **head) {
    node *pCur, *pDel;

    if (*head == NULL) {
        printf("List kosong");
        getch();
    }
    else if ((*head)->next == NULL) {
        pDel = *head;
        *head = NULL;
        free(pDel);
    }
    else {
        pCur = *head;
        while (pCur->next->next != NULL) {
            pCur = pCur->next;
        }
        pDel = pCur->next;
        pCur->next = NULL;
        free(pDel);
    }
}

//========================================================

void cariData(node *head) {
    int bil;
    node *pCur;

    system("cls");
    fflush(stdin);
    printf("masukkan bilangan yang ingin dicari : ");
    fflush(stdin);
    scanf("%d", &bil);

    pCur = head;
    while (pCur != NULL && pCur->data != bil) {
        pCur = pCur->next;
    }

    if (pCur == NULL) {
        printf("\ndata tidak ditemukan");
        getch();
    }
    else {
        printf("\ndata ditemukan");
        getch();
    }
}

//========================================================

void tampilkanJumlah(node *head) {
    int jumlah = 0;
    node *pCur;

    pCur = head;
    while (pCur != NULL) {
        jumlah++;
        pCur = pCur->next;
    }

    printf("Jumlah data : %d", jumlah);
    getch();
}

//========================================================

void tampilkanJumlahan(node *head) {
    int jumlahan = 0;
    node *pCur;

    pCur = head;
    while (pCur != NULL) {
        jumlahan += pCur->data;
        pCur = pCur->next;
    }

    printf("Jumlahan data : %d", jumlahan);
    getch();
}

//========================================================

void tranverse(node *head) {
    //traverse a linked list
    node *pWalker;

    system("cls");
    pWalker = head;
    while (pWalker != NULL) {
        printf("%d\t", pWalker->data);
        pWalker = pWalker->next;
        printf(" -> ");
    }
    printf("NULL");
}
