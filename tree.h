#pragma once

#include "node.h"
#include <iostream>
using namespace std;


class RBTree {
    node* root;
    node* NIL;
    int size;

    node* create_node(int num, node* parent) {
        node* n = new node(num); 
        n->parent = parent;
        n->left = NIL;
        n->right = NIL;
        return n;
    }

    bool search(node* curr, int num) {
        if (curr == NIL) {
            return false;
        }
        if (num == curr->elem) {
            return true;
        }
        if (num < curr->elem) {
            return search(curr->left, num);
        }
        return search(curr->right, num);
    }

    node* search_node(node* curr, int num){
        while (curr != NIL && curr->elem != num) {
            if (num < curr->elem) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return curr;
    }

    void zigleft(node* x) {
        node* y = x->parent;
        if (y == NIL || y == nullptr) return;

        node* g = y->parent;

        y->right = x->left;
        if (x->left != NIL) x->left->parent = y;

        x->left = y;
        y->parent = x;

        x->parent = g;
        if (g != NIL) {
            if (g->left == y) g->left = x;
            else g->right = x;
        }
        if(x->parent == NIL) root=x;
    }


    void zigright(node* x) {
        node* y = x->parent;
        if (y == NIL || y == nullptr) return;

        node* g = y->parent;

        y->left = x->right;
        if (x->right != NIL) x->right->parent = y;

        x->right = y;
        y->parent = x;

        x->parent = g;
        if (g != NIL) {
            if (g->left == y) g->left = x;
            else g->right = x;
        }
        if(x->parent == NIL) root=x;
    }


    void transplant(node* u, node* v) {
        if (u->parent == NIL) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

     void restructure_insert(node* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                node* y = z->parent->parent->right;

                if (y->color == RED) { //case 1 - uncle is red
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    //case 2 - uncle is black
                    //triangle
                    if (z == z->parent->right) {
                        z = z->parent;
                        zigleft(z);
                    }
                    //line
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    zigright(z->parent->parent);
                }
            } else {
                node* y = z->parent->parent->left;

                if (y->color == RED) { //case 1 - uncle is red
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    //case 2 - uncle is black
                    //triangle
                    if (z == z->parent->left) {
                        z = z->parent;
                        zigright(z);
                    }
                    //line
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    zigleft(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void restructure_delete(node* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                node* w = x->parent->right;
                //case 1 - sibling is red
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    zigleft(x->parent);
                    w = x->parent->right;
                }
                //case 2 - w is black and has both black children
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    //case 3 - w is black has left red child, right black child
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        zigright(w);
                        w = x->parent->right;
                    }
                    //case 4 - w is black, right red child
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->right != NIL) w->right->color = BLACK;
                    zigleft(x->parent);
                    x = root;
                }
            } else {
                node* w = x->parent->left;
                //case 1 - sibling is red
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    zigright(x->parent);
                    w = x->parent->left;
                }
                //case 2 - w is black and has both black children
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    //case 3 - w is black has left red child, right black child
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        zigleft(w);
                        w = x->parent->left;
                    }
                    //case 4 - w is black, right red child
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                     if (w->left != NIL) w->left->color = BLACK;
                    zigright(x->parent);
                    x = root;
                }
            }
        }
        if (x != NIL) x->color = BLACK;
    }


    node* minimum(node* n) {
        while (n != NIL && n->left != NIL) {
            n = n->left;
        }
        return n;
    }


public:
    RBTree(){
        root = nullptr;
        NIL = nullptr;
        size = 0;
        NIL = new node();
        root = NIL;
    }

    bool search(int num){
        return search(root, num);
    }

    bool insert(int num) {
        node* current = root;
        node* parent = NIL;
        while (current != NIL) {
             parent = current;
             if (num == current->elem) {
                 return false;
             } else if (num < current->elem) {
                 current = current->left;
             } else {
                 current = current->right;
             }
        }
         node* z = create_node(num, parent);
         z->color = RED;

         if (parent == NIL) {
             root = z;
         } else if (z->elem < parent->elem) {
             parent->left = z;
         } else {
             parent->right = z;
         }

        restructure_insert(z);
        size++;
        return true;
    }

    bool remove(int num) {
        node* z = search_node(root, num);
        if (z == NIL) {
            return false;
        }

        node* y = z;
        node* x;
        Color y_original_color = y->color;

        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;

            if (y->parent == z) {
                if (x != NIL) {
                     x->parent = y;
                 }
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }


        if (y_original_color == BLACK) {
            restructure_delete(x);
        }

        delete z;
        size--;
        return true;
    }

    void getRoot()  {
        if (root != NIL) {
            cout << root->elem << endl;
        } else {
            cout << "Tree is empty" << endl;
        }
    }

    bool isEmpty() {
        return size == 0;
    }

    void print() {
        if (isEmpty()) {
            cout << "EMPTY" << endl;
            return;
        }
        cout << "PRE-ORDER: ";
        print_preorder(root);
        cout << endl << "IN-ORDER: ";
        print_inorder(root);
        cout << endl << "POST-ORDER: ";
        print_postorder(root);
        cout << endl;
    }

    void print_preorder(node* curr) {
        if (curr == NIL) return;
        cout << curr->elem << "(" << (curr->color == RED ? "R" : "B") << ") ";
        print_preorder(curr->left);
        print_preorder(curr->right);
    }

    void print_inorder(node* curr) {
        if (curr == NIL) return;
        print_inorder(curr->left);
        cout << curr->elem << "(" << (curr->color == RED ? "R" : "B") << ") ";
        print_inorder(curr->right);
    }

    void print_postorder(node* curr) {
        if (curr == NIL) return;
        print_postorder(curr->left);
        print_postorder(curr->right);
        cout << curr->elem << "(" << (curr->color == RED ? "R" : "B") << ") ";
    }
};