#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* right, *left;
};

struct stack_node {
    struct node* point;
    struct stack_node* next;
};

int is_empty(struct stack_node* top) {
    return top == NULL;
}

struct stack_node* create_stack_node(struct node* root) {
    struct stack_node* new_node = (struct stack_node*)malloc(sizeof(struct stack_node));
    new_node->point = root;
    new_node->next = NULL;
    return new_node;
}

void push(struct stack_node** top, struct node* root) {
    struct stack_node* new_stack_node = create_stack_node(root);
    new_stack_node->next = *top;
    *top = new_stack_node;
}

struct node* pop(struct stack_node** top) {
    if (is_empty(*top)) {
        return NULL;
    }
    struct stack_node* temp = *top;
    *top = (*top)->next;
    struct node* pop_node = temp->point;
    free(temp);
    return pop_node;
}

void iterative_preorder(struct node* root) {
    if (root == NULL) {
        return;
    }

    struct stack_node* stack = NULL;
    push(&stack, root);

    while (!is_empty(stack)) {
        struct node* current = pop(&stack);
        printf("%d ", current->data);

        if (current->right != NULL) {
            push(&stack, current->right);
        }
        if (current->left != NULL) {
            push(&stack, current->left);
        }
    }
}

void iterative_inorder(struct node* root) {
    if (root == NULL) {
        return;
    }

    struct node* current = root;
    struct stack_node* stack = NULL;

    while (!is_empty(stack) || current != NULL) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }
        current = pop(&stack);
        printf("%d ", current->data);
        current = current->right;
    }
}

void iterative_postorder(struct node* root) {
    if (root == NULL) {
        return;
    }

    struct stack_node* stack = NULL;
    struct node* current = root;
    struct node* prev = NULL;

    while (!is_empty(stack) || current != NULL) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }
        current = stack->point;

        if (current->right != NULL && current->right != prev) {
            current = current->right;
        } else {
            printf("%d ", current->data);
            pop(&stack);
            prev = current;
            current = NULL;
        }
    }
}

void postorder(struct node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(struct node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

struct node* create_node(int value) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = value;
    temp->left = temp->right = NULL;
    return temp;
}

struct node* insert_new_node(struct node* root, int value) {
    if (root == NULL) {
        return create_node(value);
    }

    struct node* ptr = root;
    struct node* parent = NULL;

    while (ptr != NULL) {
        parent = ptr;
        if (ptr->data > value) {
            ptr = ptr->left;
        } else {
            ptr = ptr->right;
        }
    }

    struct node* temp = create_node(value);
    if (parent->data > value) {
        parent->left = temp;
    } else {
        parent->right = temp;
    }

    return root;
}

void main() {
    int value, choice;
    printf("Enter the value for the head: ");
    scanf("%d", &value);
    struct node* root = create_node(value);

    while (1) {
        printf("Enter 1 for insertion: ");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Enter the value: ");
            scanf("%d", &value);
            root = insert_new_node(root, value);
        } else {
            printf("End\n");
            break;
        }
    }

    printf("\nPreorder traversal (recursive): (P L R) ");
    preorder(root);
    printf("\nPreorder traversal (iterative): (P L R) ");
    iterative_preorder(root);

    printf("\nInorder traversal (recursive): (L P R) ");
    inorder(root);
    printf("\nInorder traversal (iterative): (L P R) ");
    iterative_inorder(root);

    printf("\nPostorder traversal (recursive): (L R P) ");
    postorder(root);
    printf("\nPostorder traversal (iterative): (L R P) ");
    iterative_postorder(root);
}