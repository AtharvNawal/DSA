/*
Implement a Polynomial addition and multiplication using Singly Linked Lists (SLL). */
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;   
    int pow;   
    struct Node* next;
};

struct Node* createNode(int coeff, int pow) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->pow = pow;
    newNode->next = NULL;
    return newNode;
}

// Add a new node at the end
void addNode(struct Node** poly, int coeff, int pow) {
    struct Node* newNode = createNode(coeff, pow);
    if (*poly == NULL) {
        *poly = newNode;
    } else {
        struct Node* temp = *poly;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Display a polynomial
void display(struct Node* poly) {
    while (poly != NULL) {
        printf("%dx^%d", poly->coeff, poly->pow);
        poly = poly->next;
        if (poly != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

// Add two polynomials
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->pow > poly2->pow) {
            addNode(&result, poly1->coeff, poly1->pow);
            poly1 = poly1->next;
        } else if (poly1->pow < poly2->pow) {
            addNode(&result, poly2->coeff, poly2->pow);
            poly2 = poly2->next;
        } else {
            addNode(&result, poly1->coeff + poly2->coeff, poly1->pow);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    while (poly1 != NULL) {
        addNode(&result, poly1->coeff, poly1->pow);
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        addNode(&result, poly2->coeff, poly2->pow);
        poly2 = poly2->next;
    }

    return result;
}

// Multiply two polynomials
struct Node* multiplyPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node* temp2 = poly2;
    struct Node* tempResult = NULL;

    while (poly1 != NULL) {
        temp2 = poly2;
        while (temp2 != NULL) {
            addNode(&tempResult, poly1->coeff * temp2->coeff, poly1->pow + temp2->pow);
            temp2 = temp2->next;
        }

        result = addPolynomials(result, tempResult);    // Add tempResult to the final result

        tempResult = NULL;    // Reset tempResult for the next iteration

        poly1 = poly1->next;
    }

    return result;
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;

    // 1st polynomial: 5x^2 + 4x^1 + 2
    addNode(&poly1, 5, 2);
    addNode(&poly1, 4, 1);
    addNode(&poly1, 2, 0);

    // 2nd polynomial: 5x^1 + 5
    addNode(&poly2, 5, 1);
    addNode(&poly2, 5, 0);

    printf("First Polynomial: ");
    display(poly1);

    printf("Second Polynomial: ");
    display(poly2);

    struct Node* sum = addPolynomials(poly1, poly2);
    printf("Sum of Polynomials: ");
    display(sum);

    struct Node* product = multiplyPolynomials(poly1, poly2);
    printf("Product of Polynomials: ");
    display(product);

    return 0;
}