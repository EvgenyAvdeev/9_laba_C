#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char name[10];
    char surname[10];
    char otch[10];
    char title[30];
    char house[30];
    int year;
    int pages;
} Book;


void gen_str(char* word, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < length - 1; i++) {
        word[i] = charset[rand() % 26];
    }
    word[length - 1] = '\0';
}

void arr_out(Book* array, int len) {

    puts("\n--------------------------------------------------------------------------------------------------------------------------");
    puts("#    |\t          FIO\t      \t        |\t   Title\t\t  |\t Publishing house           | Year | Pages");
    puts("--------------------------------------------------------------------------------------------------------------------------");
    
    for (int i = 0; i < len; i++) {
        printf("%4d | %-10s %-10s %-10s |  %-30s |  %-30s | %4d | %4d\n", i+1, array[i].name, array[i].surname, array[i].otch, array[i].title, array[i].house, array[i].year, array[i].pages);
    }
}



void reverse_arr(Book* array, int end) {
    Book temp;
    int start = 0;
    while (start < end) {
        temp = array[start];
        array[start] = array[end];
        array[end] = temp;
        start++;
        end--;
    }
}

int struct_compare(Book struct_1, Book struct_2) {
    int flag = -1;

    int cmp = strcmp(struct_1.name, struct_2.name);
    if (cmp > 0) {
        flag = 1;
    }

    else if (cmp == 0) {

        cmp = strcmp(struct_1.surname, struct_2.surname);
        if (cmp > 0) {
            flag = 1;
        }

        else if (cmp == 0) {

            cmp = strcmp(struct_1.otch, struct_2.otch);
            if (cmp > 0) {
                flag = 1;
            }

            else if (cmp == 0) {

                cmp = strcmp(struct_1.title, struct_2.title);
                if (cmp > 0) {
                    flag = 1;
                }

                else if (cmp == 0) {

                    cmp = strcmp(struct_1.house, struct_2.house);
                    if (cmp > 0) {
                        flag = 1;
                    }

                    else if (cmp == 0) {

                        if (struct_1.year > struct_2.year) {
                            flag = 1;
                        }

                        else if (struct_1.year == struct_2.year) {
                            if (struct_1.pages > struct_2.pages) {
                                flag = 1;
                            }
                            else {
                                flag = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    return flag;
}

void shakerSort(Book* a, long size)
{
    long j, k = size - 1;
    long lb = 1, ub = size - 1;
    Book x;

    do
    {
        for (j = ub; j > 0; j--)
        {
            if (struct_compare(a[j - 1], a[j]) == 1)
            {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
                k = j;
            }
        }

        lb = k + 1;
        for (j = 1; j <= ub; j++)
        {
            if (struct_compare(a[j - 1], a[j]) == 1)
            {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
                k = j;
            }
        }

        ub = k - 1;
    } while (lb < ub);
}

void quickSort(Book* array, int first, int last) {
    if (first < last) {
        int left = first, right = last;
        Book middle = array[(left + right) / 2];
        do {
            while (struct_compare(array[left], middle) == -1) left++;
            while (struct_compare(array[right], middle) == 1) right--;
            if (left <= right) {
                Book tmp = array[left];
                array[left] = array[right];
                array[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        quickSort(array, first, right);
        quickSort(array, left, last);
    }
}

void downHeap(Book* array, long k, long n) {
    long child;
    Book new_elem = array[k];

    while (k <= n / 2) {
        child = 2 * k;
        if (child < n && struct_compare(array[child], array[child + 1]) == -1) {
            child++;
        }
        if (struct_compare(new_elem, array[child]) != -1) {
            break;
        }

        array[k] = array[child];
        k = child;
    }
    array[k] = new_elem;
}


void pyramidSort(Book* array, long size) {
    long i;
    Book tmp;

    for (i = size / 2; i >= 0; i--) { 
        downHeap(array, i, size - 1); 
    }

    for (i = size - 1; i > 0; i--) {
        tmp = array[i];
        array[i] = array[0];
        array[0] = tmp;
        downHeap(array, 0, i - 1);
    }
}

int main() {
    while (1) {
        int flag, value;
        printf("Choise number of record:\n1) 100\n2) 1000\n3) 5000\n4) 10000\n5) 20000\n6) 50000\n7) 100000\n");
        scanf("%d", &flag);
        switch (flag) {
        case 1:
            value = 100; 
            break; 
        case 2: 
            value = 1000; 
            break;
        case 3:
            value = 5000;
            break;
        case 4:
            value = 10000;
            break;
        case 5:
            value = 20000;
            break;
        case 6:
            value = 50000;
            break;
        case 7:
            value = 100000;
            break;
        }
        Book* array = (Book*)malloc(sizeof(Book)*(value));
        for (int i = 0; i < value; i++) {
            gen_str(array[i].name, 5 + rand() % 5);
            gen_str(array[i].surname, 5 + rand() % 5);
            gen_str(array[i].otch, 5 + rand() % 5);
            gen_str(array[i].title, 10 + rand() % 20);
            gen_str(array[i].house, 10 + rand() % 20);
            array[i].year = rand() % 1000;
            array[i].pages = rand() % 1000;
        }
        int choice, flag1, up_down_sort;
        clock_t fTimeStart, fTimeStop;


        puts("Choice action:\n1) Shaker sort \n2) Quick sort \n3) Heap sort\n4) Exit");
        scanf("%d", &choice);
        if (choice == 4) {
            exit(0);
        }
        puts("Type of sort:\n1) UP\n2) DOWN");
        scanf("%d", &up_down_sort);

        switch (choice) {
        case 1:
            fTimeStart = clock() * 1000 / CLOCKS_PER_SEC;

            shakerSort(array, value);

            fTimeStop = clock() * 1000 / CLOCKS_PER_SEC;
            if (up_down_sort == 2) {
                reverse_arr(array, value - 1);
            }

            printf("\nReal time for sorting %i(ms)\n", fTimeStop - fTimeStart);
            break;

        case 2:
            fTimeStart = clock() * 1000 / CLOCKS_PER_SEC;

            quickSort(array, 0, value);

            fTimeStop = clock() * 1000 / CLOCKS_PER_SEC;

            if (up_down_sort == 2) {
                reverse_arr(array, value - 1);
            }

            printf("\nReal time for sorting %i(ms)\n", fTimeStop - fTimeStart);
            break;

        case 3:

            fTimeStart = clock() * 1000 / CLOCKS_PER_SEC;

            pyramidSort(array, value);

            fTimeStop = clock() * 1000 / CLOCKS_PER_SEC;

            if (up_down_sort == 2) {
                reverse_arr(array, value - 1);
            }
            printf("\nReal time for sorting %i(ms)\n", fTimeStop - fTimeStart);
            break;
        case 4:
            exit(0);
        default:
            puts("Not exist");
            break;
        }
        puts("Open data ?:\n1) Yes;\n2) No");
        scanf("%d", &flag1);
        if (flag1 == 1) {
            arr_out(array, value);
            printf("\n");
        }
        free(array);
    }
    return 0;
}
