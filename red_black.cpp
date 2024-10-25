#include <iostream>
#include <struct.h>

using namespace std;

struct Node {
    int data, argu;
    string color;
    Node *left, *right, *parent;

    Node(int data)
        : data(data)
        , color("RED")
        , argu(0)
        , left(nullptr)
        , right(nullptr)
        , parent(nullptr)
    {
    }
};

class RedBlackTree {
public:
    Node* root;
    Node* NIL;

    RedBlackTree(){
        NIL = new Node(0);
        NIL->color = "BLACK";
        NIL->left = NIL->right = NIL;
        root = NIL;
    }

    void leftRotate(Node* x){
        x->right->argu += x->argu + 1;
        Node* y = x->right;
        x->right = y->left;
        if (y->left != NIL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* x){
        if(x->left->right != NIL)
            x->argu = x->left->right->argu + 1;
        else
            x->argu = x->left->right->argu;
        Node* y = x->left;
        x->left = y->right;
        if (y->right != NIL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node* k){
        while (k != root && k->parent->color == "RED") {
            if (k->parent == k->parent->parent->left) {
                Node* u = k->parent->parent->right; // uncle
                if (u->color == "RED") {
                    k->parent->color = "BLACK";
                    u->color = "BLACK";
                    k->parent->parent->color = "RED";
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = "BLACK";
                    k->parent->parent->color = "RED";
                    rightRotate(k->parent->parent);
                }
            }
            else {
                Node* u = k->parent->parent->left; // uncle
                if (u->color == "RED") {
                    k->parent->color = "BLACK";
                    u->color = "BLACK";
                    k->parent->parent->color = "RED";
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = "BLACK";
                    k->parent->parent->color = "RED";
                    leftRotate(k->parent->parent);
                }
            }
        }
        root->color = "BLACK";
    }

    void insert(int data){
        Node* new_node = new Node(data);
        new_node->left = NIL;
        new_node->right = NIL;

        Node* parent = nullptr;
        Node* current = root;

        while (current != NIL) {
            parent = current;
            if (new_node->data < current->data) {
                current->argu += 1;
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        new_node->parent = parent;

        if (parent == nullptr) {
            root = new_node;
        }
        else if (new_node->data < parent->data) {
            parent->left = new_node;
        }
        else {
            parent->right = new_node;
        }

        if (new_node->parent == nullptr) {
            new_node->color = "BLACK";
            return;
        }

        if (new_node->parent->parent == nullptr) {
            return;
        }

        fixInsert(new_node);
    }

    void inorder(Node* node){
        if (node != NIL) {
            inorder(node->left);
            cout << node->argu << " " << node->color<< " ";
            inorder(node->right);
        }
    }

    int rank(Node* node, int data, int index){
        if (node == NIL) {
            return -1;
        }
        if (data == node->data)
            return (node->argu + index + 1);
        if (data < node->data) {
            return rank(node->left, data, index);
        }
        return rank(node->right, data, index + node->argu + 1);
    }

    int select(Node* node, int index){
        if (node == NIL) {
            return -1;
        }
        if (index == node->argu + 1)  
            return node->data;
        if (index < (node->argu + 1)) {
            return select(node->left, index);
        }
        return select(node->right, index - node->argu - 1);
    }
};

int main(){
    bool check = true;
    RedBlackTree tree;
    while(check){
        int n;
        cout << "Press 1 for insert(x), 2 for rank(x), 3 for select(i), 4 for inorder view & press any other number for exit:- \n";
        cin >> n;
        if(n == 1){
            cout << "Enter the number of insertion:- ";
            int x;
            cin >> x;
            // int x[] = {5, 10, 20, 25, 30, 35, 40, 45};
            for(int i = 0; i < x; i++){ //
                int y;
                cin >> y;
                tree.insert(y);
            }
        } else if (n == 2){
            cout << "Enter the number:- ";
            int x;
            cin >> x;
            cout << tree.rank(tree.root, x, 0) << "\n";
        } else if (n == 3){
            cout << "Enter the index:-";
            int x;
            cin >> x;
            cout << tree.select(tree.root, x) << "\n";
        } else if (n == 4){
            tree.inorder(tree.root);
            cout << "\n";
        }
        else{
            check = false;
            break;
        }
    }
    return 0;
}
