#pragma once
#include <stdio.h>
#include "Railway.h"
#pragma warning(disable : 4996)

class Node {
public:
    Railway obj;

    unsigned char height;

    Node* parent = nullptr;
    Node* left_child = nullptr;
    Node* right_child = nullptr;

public:
    Node() {};
    Node(Railway rg) {
        this->obj = rg;
        left_child = right_child = 0;
        height = 1;
    }
    Node(Node* nd) {
        this->obj = nd->obj;

        this->parent = nd->parent;
        this->left_child = nd->left_child;
        this->right_child = nd->right_child;
    }

    //bool operator < (const Node& str) const {
    //    return (num_lic < str.num_lic);
    //}
};