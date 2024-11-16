#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the BST
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node in the BST
struct Node* insert(struct Node* node, int data) {
    if (node == NULL) return createNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);

    return node;
}

// Function to find the minimum value node in the BST (used for delete operation)
struct Node* findMin(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node from the BST
struct Node* deleteNode(struct Node* root, int data) {
    if (root == NULL) return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
int getHeight(struct Node* node) {
    if (node == NULL) return 0;

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Helper function to print nodes at the current level
void printCurrentLevel(struct Node* root, int level) {
    if (root == NULL) return;
    if (level == 1)
        printf("%d ", root->data);
    else if (level > 1) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}

// Function to display the tree level-wise (BFS)
void printLevelOrder(struct Node* root) {
    if (root == NULL) return;

    int height = getHeight(root);
    for (int i = 1; i <= height; i++) {
        printCurrentLevel(root, i);
        printf("\n");
    }
}



// Function to calculate the height of the tree

// Function to print leaf nodes
void printLeafNodes(struct Node* node) {
    if (node == NULL) return;

    if (node->left == NULL && node->right == NULL) {
        printf("%d ", node->data);
    }

    printLeafNodes(node->left);
    printLeafNodes(node->right);
}

// Function to create the mirror image of the tree
struct Node* mirror(struct Node* root) {
    if (root == NULL) return NULL;

    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    mirror(root->left);
    mirror(root->right);

    return root;
}

// Main function
int main() {
    struct Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Mirror Image\n");
        printf("4. Level wise Display\n");
        printf("5. Height of Tree\n");
        printf("6. Display Leaf Nodes\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            root = insert(root, value);
            break;
        case 2:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            root = deleteNode(root, value);
            break;
        case 3:
            root = mirror(root);
            printf("Tree is mirrored!\n");
            break;
        case 4:
            printf("Level-wise display of tree:\n");
            printLevelOrder(root);
            break;
        case 5:
            printf("Height of the tree: %d\n", getHeight(root));
            break;
        case 6:
            printf("Leaf nodes of the tree: ");
            printLeafNodes(root);
            printf("\n");
            break;
        case 7:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}