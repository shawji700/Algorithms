#include <iostream>

using namespace std;

int n = -1;
bool answer = true;

int gcd(int a, int b)
{
  if (a == 0)
    return b;
  return gcd(b % a, a);
}

int findGCD_array(int arr[], int n)
{
  int result = arr[0];
  for (int i = 1; i < n; i++)
  {
    result = gcd(arr[i], result);

    if(result == 1)
    {
    return 1;
    }
  }
  if (result < 0)
    return result;
  return result;
}

void degree_increase(int g[], int aux[], int diff){
    int i = n - 1;
    while(i - diff >= 0){
        aux[i] = g[i - diff];
        i--;
    }
    while(i >= 0){
        aux[i] = 0;
        i--;
    }
    return;
}

void constant_multiple(int arr[], int c){
    int i = n - 1;
    for(; i >= 0; i--){
        arr[i] *= c;
    }
    return;
}

void constant_divide(int arr[], int c){
    int i = n - 1;
    for(; i >= 0; i--){
        arr[i] /= c;
    }
    return;
}

int minus_polynomials(int arr[], int aux[], int f_p){
    bool check = true;
    int i = f_p;
    for(; i >= 0; i--){
        int x = arr[i] - aux[i];
        if(x == 0 && check)
            f_p--;
        else 
            check = false;
        arr[i] = x;
    }
    return f_p;
}

void foo(int f[], int g[], int f_p, int g_p, int aux[]){
    // cout << "f_p : " << f_p << "|| g_p : " << g_p << "|| n : " << n << "\n";
    if(g_p <= -1){
        return;
    }
    if(f_p < g_p){
        answer = !answer;
        foo(g, f, g_p, f_p, aux);
    } else {
        int diff = f_p - g_p;
        // cout << "f_p - g_p = " << diff << "\n";
        degree_increase(g, aux, diff);
        // for(int i = 0; i < n; i++)
        //     cout << f[i] << " ";
        // cout << "\n";
        // for(int i = 0; i < n; i++)
        //     cout << aux[i] << " ";
        // cout << "\n";
        int lcm = (f[f_p] * aux[f_p]) / gcd(f[f_p], aux[f_p]);
        int f_d = lcm / f[f_p];
        int g_d = lcm / aux[f_p];
        // cout << "f : " << f[f_p] << " | g : " << g[g_p] << "\n";
        // cout << "lcm : " << lcm << " | f_d : " << f_d << " | g_d : " << g_d << "\n";
        if(f_d != 1)
            constant_multiple(f, f_d);
        if(g_d != 1)
            constant_multiple(aux, g_d);
        f_p = minus_polynomials(f, aux, f_p);
        // for(int i = 0; i < n; i++)
        //     cout << f[i] << " ";
        // cout << "\n\n";
        if(f_p < g_p){
            // cout << "swap\n";
            if(f_p > -1)
                f_d = findGCD_array(f, f_p + 1);
                if(f_d != 1)
                    constant_divide(f, f_d);
            answer = !answer;
            foo(g, f, g_p, f_p, aux);
        }
        else{
            // cout << "not swap\n";
            foo(f, g, f_p, g_p, aux);
        }
    }
    return;
}

void polynomial_gcd(int f[], int g[], int f_p, int g_p){
    int f_dual = f_p, g_dual = g_p;
    if(f_p >= g_p){
        n = f_p + 1;
    } else {
        n = g_p + 1;
    }
    int dual[n];
    int aux[n];
    if(f_p >=g_p){
        int i = 0;
        for(; i < g_p + 1; i++)
            dual[i] = g[i];
        for(; i < n; i++)
            dual[i] = 0;
    } else {
        int i = 0;
        for(; i < f_p + 1; i++)
            dual[i] = f[i];
        for(; i < n; i++)
            dual[i] = 0;
    }
    for(int i = 0; i < n; i++)
            aux[i] = 0;
    if(f_p >= g_p){
        foo(f, dual, f_p, g_p, aux);
    } else {
        answer = !answer;
        foo(g, dual, g_p, f_p, aux);
    }
    if(f_dual >= g_dual){
        if(answer){
            int final_gcd = findGCD_array(f, n);
            if (final_gcd != 1)
                constant_divide(f, final_gcd);
            for(int i = 0; i < n; i++){
                cout << f[i] << " ";
            }
        }
        else {
            int final_gcd = findGCD_array(dual, n);
            if (final_gcd != 1)
                constant_divide(dual, final_gcd);
            for(int i = 0; i < n; i++){
                cout << dual[i] << " ";
            }
        }
    } else {
        if(answer){
            int final_gcd = findGCD_array(dual, n);
            if (final_gcd != 1)
                constant_divide(dual, final_gcd);
            for(int i = 0; i < n; i++){
                cout << dual[i] << " ";
            }
        }
        else {
            int final_gcd = findGCD_array(g, n);
            if (final_gcd != 1)
                constant_divide(g, final_gcd);
            for(int i = 0; i < n; i++){
                cout << g[i] << " ";
            }
        }
    }
    return;
}

int main(){
    int f[] = {-3, -13, 7, 2};
    int g[] = {-3, 2};
    int f_p = sizeof(f)/sizeof(int) - 1;
    int g_p = sizeof(g)/sizeof(int) - 1;
    polynomial_gcd(f, g, f_p, g_p);
    return 0;
}