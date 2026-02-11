#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    while (cin >> n >> m) {
        int rows[105] = {0};

        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < m; j++) {
                if (s[j] == '1') rows[i] |= (1 << j);
            }
        }

        int max_heads = 0;
        int limit = (1 << m);

        for (int mask = 0; mask < limit; mask++) {
            int current_total = 0;
            for (int i = 0; i < n; i++) {
                int k = __builtin_popcount(rows[i] ^ mask);
                current_total += max(k, m - k);
            }
            if (current_total > max_heads) max_heads = current_total;
        }

        cout << max_heads << "\n";
    }
    return 0;
}