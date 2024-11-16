#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;     
    int exp;      
    struct Node *next; 
};

struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

void insertNode(struct Node** head, int coeff, int exp) {
    struct Node* newNode = createNode(coeff, exp);
    if (*head == NULL || (*head)->exp < exp) {
        newNode->next = *head;
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL && current->next->exp >= exp) {
            current = current->next;
        }
        if (current->exp == exp) {
            // If the exponent is already present, just add the coefficients
            current->coeff += coeff;
        } else {
            newNode->next = current->next;
            current->next = newNode;
        }
    }
}

// add two polynomials
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node* p1 = poly1;
    struct Node* p2 = poly2;

    while (p1 != NULL && p2 != NULL) {
        if (p1->exp == p2->exp) {
            insertNode(&result, p1->coeff + p2->coeff, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->exp > p2->exp) {
            insertNode(&result, p1->coeff, p1->exp);
            p1 = p1->next;
        } else {
            insertNode(&result, p2->coeff, p2->exp);
            p2 = p2->next;
        }
    }

    // If any terms are left in poly1
    while (p1 != NULL) {
        insertNode(&result, p1->coeff, p1->exp);
        p1 = p1->next;
    }

    // If any terms are left in poly2
    while (p2 != NULL) {
        insertNode(&result, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

void printPolynomial(struct Node* poly) {
    while (poly != NULL) {
        printf("%dx^%d", poly->coeff, poly->exp);
        poly = poly->next;
        if (poly != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

int main() {
    // polynomial 1: 3x^5 + 4x^3 + 2x^1
    struct Node* poly1 = NULL;
    insertNode(&poly1, 3, 5);
    insertNode(&poly1, 4, 3);
    insertNode(&poly1, 2, 1);
    // polynomial 2: 5x^4 + 4x^3 + 3x^1
    struct Node* poly2 = NULL;
    insertNode(&poly2, 5, 4);
    insertNode(&poly2, 4, 3);
    insertNode(&poly2, 3, 1);
    // Add the two polynomials
    struct Node* result = addPolynomials(poly1, poly2);
    printf("Polynomial 1: ");
    printPolynomial(poly1);
    printf("Polynomial 2: ");
    printPolynomial(poly2);
    printf("Sum: ");
    printPolynomial(result);
    return 0;
}