#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <assert.h>


enum color_t {BLACK, RED};

typedef struct donation {
    unsigned long amount;
    char* description;
    char* name;
    struct donation* left;
    struct donation* right;
    struct donation* parent;
    enum color_t color;
    unsigned int id;
} Node;

Node* root = NULL;
Node* null;
unsigned int cid = 1;

static void handler(int signum) {
    puts("So long, and thanks for all the trees");
    exit(0);
}

void print_node_compact(Node* n) {
    printf("%c%u>%uL%uR%u\n", (n->color == RED) ? 'R' : 'B', n->id,
    (n->parent == NULL) ? 0 : n->parent->id, (n->left == NULL) ? 0 : n->left->id, (n->right == NULL) ? 0 : n->right->id);
}

void read_str(char *ptr, int len) {
    int i = 0;
    while (read(0, &ptr[i], 1) == 1) {
        i++;
        if (i == len || ptr[i-1] == '\n') {
            ptr[i-1] = '\0';
            break;
        }
    }
    return;
}

void read_ulong(unsigned long *ptr) {
    char buf[24];
    putchar('>'); putchar(' ');
    read_str(buf, 24);
    *ptr = strtoul(buf, NULL, 10);
    return;
}

Node* sibling(Node* node) {
    if (node == NULL) return NULL;
    if (node->parent == NULL) return NULL;
    if (node == node->parent->left) return node->parent->right;
    else return node->parent->left;
}

Node* in_order_successor(Node* node) {
    Node* ret = node->right;
    if (ret == NULL) return ret;
    while (ret->left != NULL) ret = ret->left;
    return ret;
}

Node* in_order_predecessor(Node* node) {
    Node* ret = node->left;
    if (ret == NULL) return ret;
    while (ret->right != NULL) ret = ret->right;
    return ret;
}

Node* find_node(unsigned long id) {
    Node* current = root;
    if (current == NULL) return NULL;
    while (current->id != id) {
        if (current->right != NULL && current->id < id) {
            current = current->right;
        } else if (current->left != NULL && current->id > id) {
            current = current->left;
        } else {
            return NULL;
        }
    }
    return current;
}

void rot_left(Node* node) {
    //printf("Rotating node %u left\n", node->id);
    Node* rep = node->right;
    Node* parent = node->parent;
    assert(rep != NULL);

    // r o t a t e
    node->right = rep->left;
    rep->left = node;
    node->parent = rep;

    // fix parents
    if (node->right != NULL) node->right->parent = node;
    if (parent != NULL) {
        if (node == parent->left) {
            parent->left = rep;
        } else {
            parent->right = rep;
        }
    }
    rep->parent = parent;
}

void rot_right(Node* node) {
    //printf("Rotating node %u right\n", node->id);
    Node* rep = node->left;
    Node* parent = node->parent;
    assert(rep != NULL);

    // r o t a t e
    node->left = rep->right;
    rep->right = node;
    node->parent = rep;

    // fix parents
    if (node->left != NULL) node->left->parent = node;
    if (parent != NULL) {
        if (node == parent->left) {
            parent->left = rep;
        } else {
            parent->right = rep;
        }
    }
    rep->parent = parent;
}

void insert_leaf(Node* sroot, Node* node) {
    if (root == NULL) {
        root = node;
        node->parent = NULL;
        node->left = NULL;
        node->right = NULL;
        node->color = BLACK;
        return;
    }
    //printf("Inserting node %u into subtree %u\n", node->id, sroot->id);
    if (node->id < sroot->id) {
        if (sroot->left != NULL) {
            insert_leaf(sroot->left, node);
            return;
        }
        sroot->left = node;
    } else {
        if (sroot->right != NULL) {
            insert_leaf(sroot->right, node);
            return;
        }
        else sroot->right = node;
    }

    node->parent = sroot;
    node->left = NULL;
    node->right = NULL;
    node->color = RED;
}

void repair_insert(Node* node) {
    if (node->parent == NULL) {
        //puts("Running insert repair case 1");
        node->color = BLACK; // node was root
    } else if (node->parent->color == BLACK) {
        //puts("Running insert repair case 2");
        return; // nothing to be done
    } else if (sibling(node->parent) != NULL && sibling(node->parent)->color == RED) {
        //puts("Running insert repair case 3");
        sibling(node->parent)->color = BLACK;
        node->parent->color = BLACK;
        node->parent->parent->color = RED;
        repair_insert(node->parent->parent);
    } else {
        //puts("Running insert repair case 4");
        Node* p = node->parent;
        Node* gp = p->parent;
        if (node == p->right && p == gp->left) {
            rot_left(p);
            node = node->left;
        } else if (node == p->left && p == gp->right) {
            rot_right(p);
            node = node->right;
        }
        p = node->parent;
        gp = p->parent;
        if (node == p->left) {
            rot_right(gp);
        } else {
            rot_left(gp);
        }
        p->color = BLACK;
        gp->color = RED;
    }
}

void unlink_node(Node* node, Node* child) {
    assert(child->parent == node);
    Node* rep = child;
    rep->parent = node->parent;
    if (node->parent != NULL) {
        if (node == node->parent->left) {
            node->parent->left = rep;
        } else {
            node->parent->right = rep;
        }
    }
}

void repair_dblack(Node* node) {
    //printf("Repairing %u\n", node->id);
    if (node->color == BLACK) {
        Node* p = node->parent;
        if (p == NULL) {
            // repairing root
            return;
        }
        //printf("Parent is %u\n", p->id);
        if (p->left == node) {
            assert(p->right != NULL);
            //puts("Right is sibling");
            if (p->right->color == BLACK) {
                //puts("Right is black");
                if (p->right->right != NULL && p->right->right->color == RED) {
                    //puts("Exterior red");
                    rot_left(p);
                    p->parent->color = p->color;
                    p->color = BLACK;
                    p->parent->right->color = BLACK;
                } else if (p->right->left != NULL && p->right->left->color == RED) {
                    //puts("Interior red");
                    rot_right(p->right);
                    rot_left(p);
                    p->parent->color = p->color;
                    p->color = BLACK;
                } else {
                    //puts("No red children");
                    p->right->color = RED;
                    repair_dblack(p);
                }
            } else {
                //puts("Right is red");
                rot_left(p);
                p->color = RED;
                p->parent->color = BLACK;
                repair_dblack(node);
            }
        } else {
            assert(p->left != NULL);
            //puts("Left is sibling");
            if (p->left->color == BLACK) {
                //puts("Left is black");
                if (p->left->left != NULL && p->left->left->color == RED) {
                    //puts("Exterior red");
                    rot_right(p);
                    p->parent->color = p->color;
                    p->color = BLACK;
                    p->parent->left->color = BLACK;
                } else if (p->left->right != NULL && p->left->right->color == RED) {
                    //puts("Interior red");
                    rot_left(p->left);
                    rot_right(p);
                    p->parent->color = p->color;
                    p->color = BLACK;
                } else {
                    //puts("No red children");
                    p->left->color = RED;
                    repair_dblack(p);
                }
            } else {
                //puts("Left is red");
                rot_right(p);
                p->color = RED;
                p->parent->color = BLACK;
                repair_dblack(node);
            }
        }
    } else {
        //puts("Node is red");
        node->color = BLACK;
    }
    //printf("Finished repairing %u\n", node->id);
}

void update_root(Node* node) {
    //printf("Updating root from %u\n", node->id);
    while (node->parent != NULL) node = node->parent;
    root = node;
    //printf("Found root at %u\n", root->id);
}

void delete(Node* node) {
    free(node->name);
    free(node->description);
    if (node->left != NULL && node->right != NULL) {
        // two-child
        Node* rep = in_order_successor(node);
        //printf("Deleting %u instead of %u\n", rep->id, node->id);
        node->name = rep->name;
        node->id = rep->id;
        node->description = rep->description;
        node->amount = rep->amount;
        delete(rep);

    } else {
        // one-child or no-children
        Node* child;
        if (node->left != NULL) {
            child = node->left;
        } else if (node->right != NULL) {
            child = node->right;
        } else {
            //printf("Deleting leaf node %u\n", node->id);
            null->parent = node;
            node->left = null;
            child = null; // use temp child
        }

        unlink_node(node, child);
        if (node->color == BLACK) {
            repair_dblack(child);
        }
        update_root(child);
        if (child == null) {
            //puts("Removing placeholder null");
            if (child->parent != NULL) {
                //printf("Parent is %u\n", child->parent->id);
                if (child->parent->left == null) {
                    //puts("Left");
                    child->parent->left = NULL;
                }
                if (child->parent->right == null) {
                    //puts("Right");
                    child->parent->right = NULL;
                }
            }
            //puts("Remove parent");
            child->parent = NULL;
        }
        //puts("Free node");
        free(node);
    }
}

void create_donation() {
    Node* node = malloc(sizeof(Node));
    node->name = malloc(16);
    node->description = NULL;
    node->id = cid++;
    printf("Your donation has ID %d, please keep this if you want to revoke or edit your donation.\n", node->id);
    puts("To put in information for your donation, please use the edit utility.");
    insert_leaf(root, node);
    repair_insert(node);
    update_root(node);
}

void revoke_donation() {
    unsigned long id;
    puts("Enter the ID of the entry you wish to revoke.");
    read_ulong(&id);
    Node* a = find_node(id);
    if (a == NULL) {
        puts("No such entry.");
        return;
    }
    delete(a);
}

void edit_donation() {
    unsigned long id, len_desc;
    char* desc;
    puts("Enter the ID of the entry you wish to edit.");
    read_ulong(&id);
    Node* a = find_node(id);
    if (a == NULL) {
        puts("No such entry.");
        return;
    }
    puts("Enter new name.");
    read_str(a->name, 16);
    puts("Enter length of new description.");
    read_ulong(&len_desc);
    if (len_desc > 0x400) {
        puts("Too long!");
        return;
    }
    free(a->description);
    desc = malloc(len_desc);
    puts("Enter new description.");
    read_str(desc, len_desc);
    a->description = desc;
    puts("Enter new amount.");
    read_ulong(&a->amount);
    printf("Edited entry %lu.\n", id);
}


void print_donation() {
    unsigned long id;
    puts("Enter the ID of the entry you wish to print.");
    read_ulong(&id);
    Node* a = find_node(id);
    if (a == NULL) {
        puts("No such entry.");
        return;
    }
    printf("%lu trees\n", a->amount);
    printf("Donator: %s\n", a->name);
    printf("Description: %s\n", a->description);
}

void print_tree(Node* n) {
    print_node_compact(n);
    if (n->left != NULL) {
        print_tree(n->left);
    }
    if (n->right != NULL) {
        print_tree(n->right);
    }
}

unsigned int black_depth(Node* node) {
    unsigned int ret = 0;
    while (node->parent != NULL) {
        if (node->color == BLACK) ret++;
        node = node->parent;
    }
    return ret;
}

void print_depth() {
    puts("Enter node ID.");
    unsigned long id;
    read_ulong(&id);
    Node* a = find_node(id);
    if (a == NULL) {
        puts("No such entry.");
        return;
    }
    if (a->left != NULL || a->right != NULL) {
        puts("Warning! Node is not leaf!");
    }
    printf("Black depth: %u\n", black_depth(a));
}

void verify_bdepth() {
    int bd = -1;
    for (unsigned int i = 1; i < cid; i++) {
        Node *a = find_node(i);
        if (a != NULL && a->left == NULL && a->right == NULL) {
            if (bd == -1) bd = (int) black_depth(a);
            assert(bd == (int) black_depth(a));
        }
    }
}

void menu() {
    puts("Select an option:");
    puts("1) Make a donation");
    puts("2) Revoke a prior donation");
    puts("3) Edit a prior donation");
    puts("4) Print a prior donation");
    puts("5) Exit");
}

int main(void) {
    puts("Welcome to the #TeamRBTrees donation utility");
    puts("https://en.wikipedia.org/wiki/Red%E2%80%93black_tree");
    setvbuf(stdin, NULL, _IONBF, NULL);
    setvbuf(stdout, NULL, _IONBF, NULL);
    signal(0xe, handler);
    null = calloc(sizeof(Node), 1);
    alarm(30);
    while (1) {
        unsigned long choice;
        menu();
        read_ulong(&choice);
        switch (choice) {
            case 1:
                create_donation();
                break;
            case 2:
                revoke_donation();
                break;
            case 3:
                edit_donation();
                break;
            case 4:
                print_donation();
                break;
            case 5:
                puts("Thanks for donating!");
                exit(0);
            /*
            case 6:
                print_tree(root);
                break;
            case 7:
                print_depth();
                break;
            */
            default:
                puts("I couldn't understand that.");
        }
    }
}
