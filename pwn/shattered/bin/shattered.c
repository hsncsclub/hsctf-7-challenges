#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 20

typedef struct node {
    char hash[20];
    struct node * left;
    struct node * right;
    unsigned long length;
    char * value;
} Node;

Node * head = NULL;

void read_all(char * buf, int n) {
    puts("Data?");
    printf("> ");
    int sum = 0;
    while (sum < n) {
        int temp = read(0, buf+sum, n-sum);
        if (temp < 0) {
            exit(-1);
        }
        sum += temp;
    }
}

void menu() {
    puts("1. Insert an element");
    puts("2. Delete an element");
    puts("3. View an element");
    puts("4. Exit");
}

void get_feedback() {
    char buf[100];
    puts("Hey, how do you like my code so far?");
    puts("If you want, you can leave some feedback here!");
    printf("> ");
    read(0, buf, sizeof(buf));
}

void insert_recursive(Node * new, Node * current) {
    Node * next;
    if (memcmp(new->hash, current->hash, 20) > 0) {
        // go to right
        if (current->right == NULL) {
            current->right = new;
            return;
        }
        next = current->right;
    } else if (memcmp(new->hash, current->hash, 20) < 0) {
        // go left
        if (current->left == NULL) {
            current->left = new;
            return;
        }
        next = current->left;
    } else if (new->length == current->length && memcmp(new->value, current->value, new->length) == 0) {
        free(new->value);
        free(new);
        puts("No duplicates!");
        return;
    }
    insert_recursive(new, next);
}

void insert() {
    char buf[BUF_SIZE];
    unsigned int i = 0;
    puts("How big?");
    printf("> ");
    read(0, buf, BUF_SIZE);
    i = strtoul(buf, NULL, 10);
    if (i > 500000) {
        puts("Too big!");
        exit(-1);
    }
    Node * new = malloc(sizeof(Node));
    new->left = NULL;
    new->right = NULL;
    new->value = malloc(i);
    new->length = i;
    read_all(new->value, i);
    SHA1(new->value, i, new->hash);
    get_feedback();
    if (head == NULL) {
        head = new;
    } else {
        insert_recursive(new, head);
    }
}

Node * delete_recursive(Node * current, char * hash) {
    if (current == NULL) {
        return NULL;
    }
    if (memcmp(hash, current->hash, 20) > 0) {
        current->right = delete_recursive(current->right, hash);
        return current;
    } else if (memcmp(hash, current->hash, 20) < 0) {
        current->left = delete_recursive(current->left, hash);
        return current;
    }
    free(current->value);
    free(current);
    return NULL;
}

void delete() {
    char buf[BUF_SIZE];
    puts("What do you want to delete?");
    printf("> ");
    read(0, buf, BUF_SIZE);
    head = delete_recursive(head, buf);
    puts("Oops, I shattered everything below it!");
}

void view_recursive(Node * current, char * hash) {
    if (current == NULL) {
        puts("Not found!");
        return;
    }
    if (memcmp(hash, current->hash, 20) > 0) {
        view_recursive(current->right, hash);
        return;
    } else if (memcmp(hash, current->hash, 20) < 0) {
        view_recursive(current->left, hash);
        return;
    }
    puts(current->hash);
    return;
}

void view() {
    char buf[BUF_SIZE];
    puts("What do you want to see?");
    printf("> ");
    read(0, buf, BUF_SIZE);
    view_recursive(head, buf);
}

int main() {
    char buf[BUF_SIZE];
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);

    puts("I wrote a program to learn about pointers!");
    puts("Let's see if you can shatter it :)");

    while (1) {
        menu();
        printf("> ");
        int choice = 0;
        read(0, buf, BUF_SIZE);
        choice = strtoul(buf, NULL, 10);
        switch (choice) {
            case 1:
                insert();
                break;
            case 2:
                delete();
                break;
            case 3:
                view();
                break;
            case 4:
                puts("Nope! Still intact.");
            default:
                exit(0);
        }
    }
}