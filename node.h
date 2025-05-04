#pragma once

enum Color { RED = 0, BLACK = 1};

struct node{
    int elem;
    node* parent;
    node* left;
    node* right;
    Color color;

    node() {
        elem = 0;
        parent = this;
        left = this;
        right = this;
        color = BLACK;
    }

    node(int num) {
        elem = num;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        color = RED;
    }
};