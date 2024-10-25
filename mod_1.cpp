#include <iostream>

using namespace std;

int find_a_dash(int a, int m, int x){
    int copy_m = m;
    bool change = false;
    if(a < m){
        int temp = a;
        a = m;
        m = temp;
        change = true;
        copy_m = a;
    }
    cout << copy_m << "\n";
    int aux_1[] = {0, 1};
    int aux_2[] = {1, 0};
    int ans[] = {1, 0};
    int quotient = -1 * (a / m);
    ans[1] = quotient;
    aux_2[1] = quotient;
    int temp = m;
    m = a % m;
    a = temp;
    while(m > 1){
        quotient = -1 * (a / m);
        ans[0] = ans[0] * quotient + aux_1[0];
        ans[1] = ans[1] * quotient + aux_1[1];
        aux_1[0] = aux_2[0];
        aux_1[1] = aux_2[1];
        aux_2[0] = ans[0];
        aux_2[1] = ans[1];
        temp = m;
        m = a % m;
        a = temp;
    }
    if (change){
        if(ans[1] < 0)
            return copy_m + ans[1];
        return ans[1];
    } else {
        if(ans[0] < 0)
            return copy_m + ans[0];
        return ans[0];
    }
}

int main(){
    int a, m, x;
    cout << "Enter a : ";
    cin >> a;
    cout << "Enter m : ";
    cin >> m;
    cout << "Enter x : ";
    cin >> x;
    int a_dash = find_a_dash(a, m, x);
    cout << "a' : " << a_dash << "\n" << "(a * a') % m : " << (a * a_dash) % m;
    return 0;
}