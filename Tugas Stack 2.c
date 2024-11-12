#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack untuk menyimpan tanda kurung dan elemen
char stack[MAX];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

// 1. Matching Balancing Parenthesis
int isMatching(char a, char b) {
    return (a == '(' && b == ')') || (a == '{' && b == '}') || (a == '[' && b == ']');
}

int isBalanced(char *exp) {
    for (int i = 0; i < strlen(exp); i++) {
        if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[') {
            push(exp[i]);
        } else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']') {
            if (top == -1 || !isMatching(pop(), exp[i])) {
                return 0; // false
            }
        }
    }
    return top == -1; // true if stack is empty
}

// 2. Evaluasi Ekspresi Postfix
int intStack[MAX];
int intTop = -1;

void intPush(int num) {
    intStack[++intTop] = num;
}

int intPop() {
    return intStack[intTop--];
}

int evaluatePostfix(char *exp) {
    for (int i = 0; exp[i] != '\0'; i++) {
        if (isdigit(exp[i])) {
            intPush(exp[i] - '0');
        } else {
            int val2 = intPop();
            int val1 = intPop();
            switch (exp[i]) {
                case '+': intPush(val1 + val2); break;
                case '-': intPush(val1 - val2); break;
                case '*': intPush(val1 * val2); break;
                case '/': intPush(val1 / val2); break;
            }
        }
    }
    return intPop();
}

// 3. Konversi Infix ke Postfix
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixToPostfix(char *exp) {
    char result[MAX];
    int k = 0;

    for (int i = 0; exp[i]; i++) {
        if (isalnum(exp[i])) {
            result[k++] = exp[i];
        } else if (exp[i] == '(') {
            push(exp[i]);
        } else if (exp[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                result[k++] = pop();
            }
            pop(); // pop '('
        } else {
            while (top != -1 && precedence(stack[top]) >= precedence(exp[i])) {
                result[k++] = pop();
            }
            push(exp[i]);
        }
    }

    while (top != -1) {
        result[k++] = pop();
    }

    result[k] = '\0';
    printf("Postfix: %s\n", result);
}

int main() {
    int pilihan;
    char ekspresi[MAX];

    printf("Pilih operasi:\n");
    printf("1. Cek keseimbangan tanda kurung\n");
    printf("2. Evaluasi ekspresi postfix\n");
    printf("3. Konversi infix ke postfix\n");
    printf("Masukkan pilihan Anda (1/2/3): ");
    scanf("%d", &pilihan);

    printf("Masukkan ekspresi: ");
    scanf("%s", ekspresi);

    if (pilihan == 1) {
        if (isBalanced(ekspresi)) {
            printf("Tanda kurung seimbang\n");
        } else {
            printf("Tanda kurung tidak seimbang\n");
        }
    } else if (pilihan == 2) {
        printf("Hasil evaluasi postfix: %d\n", evaluatePostfix(ekspresi));
    } else if (pilihan == 3) {
        infixToPostfix(ekspresi);
    } else {
        printf("Pilihan tidak valid\n");
    }

    return 0;
}
