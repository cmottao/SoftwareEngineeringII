#include <bits/stdc++.h>
using namespace std;

void bubble_sort(vector<int> &a) {
    for(int i = 0; i < a.size(); i++) {
        bool swapped = false;

        for(int j = 0; j + 1 < a.size() - i; j++) {
            if(a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if(!swapped) break;
    }
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);

    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    bubble_sort(a);

    for(int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    solve();
}