#include <stdio.h>
#include <string.h>

struct Student {
    char name[20];
    int roll_no;
    float marks;
};

void insertion_sort(struct Student stu[], int n) {
    for (int i = 1; i < n; i++) {
        struct Student temp = stu[i];
        int j = i - 1;
        while (j >= 0 && stu[j].roll_no > temp.roll_no) {
            stu[j + 1] = stu[j];
            j--;
        }
        stu[j + 1] = temp;
    }
}

int main() {
    int siz;
    struct Student stu[10];
    
    printf("Enter the number of students: ");
    scanf("%d", &siz);

    for(int i=0; i < siz; i++)
    {
        printf("Enter student %d name, roll_no and marks: ", i+1);
        scanf("%s %d %f", stu[i].name, &stu[i].roll_no, stu[i].marks);
    }

    insertion_sort(stu, siz);

    printf("\nThe sorted list by roll number is:\n");
    for (int i = 0; i < siz; i++) {
        printf("%s %d %.2f\n", stu[i].name, stu[i].roll_no, stu[i].marks);
    }

    return 0;
}