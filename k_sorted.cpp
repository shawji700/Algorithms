#include <iostream>

using namespace std;

struct node
{
    int val;
    node* l, * m, * r;
    node(int key){
        val = key;
        l = nullptr;
        m = nullptr;
        r = nullptr;
    }
};

int aux[30];
int n = -1;
node *head = nullptr;

node* swap_node(node* node_1, node* node_2, int i){
    node* l = node_1->l;
    node* m = node_1->m;
    node* r = node_1->r;
    node_1->l = node_2->l;
    node_1->m = node_2->m;
    node_1->r = node_2->r;
    node_2->l = l;
    node_2->m = m;
    node_2->r = r;
    if(i == 1)
        node_2->l = node_1;
    else if (i == 2)
        node_2->m = node_1;
    else if (i == 0)
        node_2->r = node_1;
    return node_2;
}

node* correction(node* root, node* temp, int i){
    node* x;
    if(i > 0){
        if(aux[i] == 1){
            root->l = correction(root->l, temp, i - 1);
            x = root->l;
        } else if (aux[i] == 2){
            root->m = correction(root->m, temp, i - 1);
            x = root->m;
        } else if (aux[i] == 0){
            root->r = correction(root->r, temp, i - 1);
            x = root->r;
        }
        if(root->val > x->val){
            int z = aux[i];
            aux[i] = -1;
            return swap_node(root, x, z);
        }
    } else {
        if(root->val > temp->val){
            int z = aux[i];
            aux[i] = -1;
            return swap_node(root, temp, z);
        } else {
            if(aux[i] == 1)
                root->l = temp;
            else if (aux[i] == 2)
                root->m = temp;
            else if (aux[i] == 0)
                root->r = temp;
        }
    }
    aux[i] = -1;
    return root;
}

int find_position(){
    int var = n, i = 0;
    aux[0] = n % 3;
    while(var){
        int parent = (var - 1) / 3;
        i++;
        aux[i] = (parent % 3);
        var = parent;
    }
    aux[i] = -1;
    return i - 1;
}

void insertion(int key){
    node* temp = new node(key);
    n++;
    if(n == 0){
        head = temp;
        return;
    }
    head = correction(head, temp, find_position());
    return;
}

node* foo(node* root, int i){
    int x = aux[i];
    aux[i] = -1;
    if(i > 0){
        if(x == 1)
            return foo(root->l, i - 1);
        else if (x == 2)
            return foo(root->m, i - 1);
        else if (x == 0)
            return foo(root->r, i - 1);  
    }
    return root;
}

node* heapify(node* root){
    int x = -1;
    node* z = root;
    if(root->l && root->val > root->l->val){
        x = 1;
        z = root->l;
    }
    if(root->m && z->val > root->m->val){
        x = 2;
        z = root->m;
    }
    if(root->r && z->val > root->r->val){
        x = 0;
        z = root->r;
    }
    if (x != -1 && z != root){
        node* temp = swap_node(root, z, x);
        if(x == 1)
            temp->l = heapify(root);
        else if(x == 2)
            temp->m = heapify(root);
        else if(x == 0)
            temp->r = heapify(root);
        return temp;
    }
    return root;
}

void deletion(){
    if(n < 0){
        cout << "No element";
        return;
    }
    if(n == 0){
        head = nullptr;
        n--;
        return;
    }
    int index = find_position();
    int cell = aux[0];
    node* last_parent_level = foo(head, index);
    node* leave_node;
    if(cell == 1){
        leave_node = last_parent_level->l;
        last_parent_level->l = nullptr;
    } else if(cell == 2){
        leave_node = last_parent_level->m;
        last_parent_level->m = nullptr;
    } else if(cell == 0){
        leave_node = last_parent_level->r;
        last_parent_level->r = nullptr;
    }
    leave_node->l = head->l;
    leave_node->m = head->m;
    leave_node->r = head->r;
    head->l = nullptr;
    head->m = nullptr;
    head->r = nullptr;
    if(index == 0){
        if(cell == 1)
            leave_node->l = nullptr;
        else if (cell == 2)
            leave_node->m = nullptr;
        else if (cell == 0)
            leave_node->r = nullptr;
    }
    head = leave_node;
    head = heapify(head);
    n--;
    return;
}

void k_sorted(int a[], int k, int l){
    if(k > l)
        k = l;
    for(int i = 0; i < l; i++){
        aux[i] = -1;
    }
    int window = 0;
    while(window < k && window < l){
        insertion(a[window]);
        window++;
    }
    for(; window < l; window++){
        insertion(a[window]);
        a[window - k] = head->val;
        deletion();
    }
    while(head && window - k < l){
        a[window - k] = head->val;
        deletion();
        window++;
    }
    return;
}

int main()
{
    int a[] = { 3, 3, 2, 1, 6, 4, 4, 5, 9, 7, 8, 11, 12 };
    int k = 14;
    int arr_size = sizeof(a)/sizeof(int);
    k_sorted(a, k, arr_size);
    for(int i = 0; i < arr_size; i++){
        cout << a[i] << " ";
    }
    return 0;
}