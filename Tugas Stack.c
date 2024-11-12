#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
//Menambahkan batas maksimum untuk stack
#define MAX_SIZE 50


// Struktur untuk head dalam stack
struct Stack {
    int count;
    struct StackNode* top;
};

// Struktur untuk node dalam stack
struct StackNode {
    int data;
    struct StackNode* next;
};

// Fungsi untuk membuat stack baru
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    stack->count = 0;
    return stack;
}

// Fungsi untuk mengecek apakah stack kosong
int isEmpty(struct Stack* stack){
    int result;
    if (stack->top != NULL) {
        result = FALSE;
    } else {
        result = TRUE;
    }
    return result;
}

// Fungsi untuk mengecek apakah stack penuh
int isFull(struct Stack* stack){
    int result;
    if (stack->count < MAX_SIZE){
        result = FALSE;
    } else {
        result = TRUE;
    }
    return result;
}

// Fungsi untuk menambahkan elemen ke stack (push)
void push(struct Stack* stack, int data) {
    int canPush;
    if (isFull(stack)){
        canPush = FALSE;
    } else {
        canPush = TRUE;
    }

    if (canPush = TRUE){
        struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
        if (newNode != NULL){
            newNode->data = data;
            newNode->next = stack->top;
            stack->top = newNode;
            stack->count++;
            printf("%d telah di push ke dalam stack\n", data);
        } else {
            printf("Alokasi memori gagal.\n");
        }
    } else {
        printf("Stack overflow\n");
    }
    getch();
}

// Fungsi untuk menghapus elemen dari stack (pop)
int pop(struct Stack* stack) {
    int result = -1;
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
    } else {
        struct StackNode* temp = stack->top;
        result = temp->data;
        stack->top = stack->top->next;
        free(temp);
        stack->count--;
    }
    return result;
}

// Fungsi untuk melihat elemen teratas stack tanpa menghapusnya
int stackTop(struct Stack* stack) {
    int result = -1;
    if (isEmpty(stack)){
        printf("Stack kosong\n");
    } else {
        result = stack->top->data;
    }
    return result;
}

// Fungsi untuk menghitung jumlah elemen dalam stack
int stackCount(struct Stack* stack) {
    return stack->count;
}

// Fungsi untuk menghancurkan stack
void destroyStack(struct Stack* stack) {
    struct StackNode* temp;
    while (stack->top != NULL){
        temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }

    stack->count = 0;
    free(stack);
}

// Fungsi untuk mencetak isi stack
void printStack(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack kosong\n");
    } else {
        struct StackNode* temp = stack->top;
        printf("Stack: ");
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    struct Stack* stack = createStack();
    int pilihan, data;

    do {
        system("cls");
        printf("Daftar pilihan program :\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Stack Top\n");
        printf("4. Is Empty\n");
        printf("5. Is Full\n");
        printf("6. Stack Count\n");
        printf("7. Print Stack\n");
        printf("8. Destroy Stack dan Keluar\n");
        printf("Masukkan pilihan Anda : ");
        fflush(stdin);
        scanf("%d", &pilihan);

        if (pilihan == 1) {
            printf("\nMasukkan data untuk di push: ");
            fflush(stdin);
            scanf("%d", &data);
            push(stack, data);
        }
        else if (pilihan == 2) {
            data = pop(stack);
            if (data != -1) {
                printf("Stack berhasil di pop!\n");
            }
            getch();
        }
        else if (pilihan == 3) {
            data = stackTop(stack);
            if (data != -1) {
                printf("Top stack: %d\n", data);
            }
            getch();
        }
        else if (pilihan == 4) {
            if (isEmpty(stack)) {
                printf("Stack kosong\n");
            } else {
                printf("Stack tidak kosong\n");
            }
            getch();
        }
        else if (pilihan == 5) {
            if (isFull(stack)) {
                printf("Stack penuh\n");
            } else {
                printf("Stack belum penuh\n");
            }
            getch();
        }
        else if (pilihan == 6) {
            printf("Stack count: %d\n", stackCount(stack));
            getch();
        }
        else if (pilihan == 7) {
            printStack(stack);
            getch();
        }
        else if (pilihan == 8) {
            destroyStack(stack);
            printf("Stack destroyed. Keluar...\n");
            getch();
        }
        else {
            printf("Pilihan tidak valid!\n");
            getch();
        }
    } while (pilihan != 8);

    return 0;
}
