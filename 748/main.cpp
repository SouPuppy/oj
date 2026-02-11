#include <iostream>
#include <cstring>
#include <string>

using namespace std;

#define BLACK  (1 << 1)
#define WHITE  (1 << 2)
#define MIXED  (BLACK | WHITE)

#define sub_node(id, i) (id * 4 + i - 3)

struct Node {
    int sum;
    int color;
} nodes[2000000];

int board[1050][1050];

void update(int id) {
    int s1 = sub_node(id, 1);
    int s2 = sub_node(id, 2);
    int s3 = sub_node(id, 3);
    int s4 = sub_node(id, 4);

    nodes[id].color = nodes[s1].color | nodes[s2].color | nodes[s3].color | nodes[s4].color;

    if (nodes[id].color == BLACK || nodes[id].color == WHITE) {
        nodes[id].sum = 1;
    } else {
        nodes[id].sum = nodes[s1].sum + nodes[s2].sum + nodes[s3].sum + nodes[s4].sum + 1;
    }
}

void build(int id, int k, int x, int y) {
    if (k == 0) {
        nodes[id].sum = 1;
        nodes[id].color = board[x][y];
        return;
    }
    int half = (1 << (k - 1));
    build(sub_node(id, 1), k - 1, x, y);
    build(sub_node(id, 2), k - 1, x + half, y);
    build(sub_node(id, 3), k - 1, x, y + half);
    build(sub_node(id, 4), k - 1, x + half, y + half);
    update(id);
}

void flip(int id, int k, int tr, int tc, int x, int y) {
    if (k == 0) {
        nodes[id].color = (nodes[id].color == BLACK) ? WHITE : BLACK;
        nodes[id].sum = 1;
        return;
    }

    int half = (1 << (k - 1));
    if (tr < x + half) {
        if (tc < y + half) flip(sub_node(id, 1), k - 1, tr, tc, x, y);
        else flip(sub_node(id, 3), k - 1, tr, tc, x, y + half);
    } else {
        if (tc < y + half) flip(sub_node(id, 2), k - 1, tr, tc, x + half, y);
        else flip(sub_node(id, 4), k - 1, tr, tc, x + half, y + half);
    }
    update(id);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (!(cin >> t)) return 0;

    while (t--) {
        int k;
        cin >> k;
        int n = (1 << k);

        for (int i = 0; i < n; i++) {
            string line;
            cin >> line;
            for (int j = 0; j < n; j++) {
                board[i][j] = (line[j] == '0') ? BLACK : WHITE;
            }
        }

        build(1, k, 0, 0);

        int m, r, c;
        cin >> m;
        while (m--) {
            cin >> r >> c;
            flip(1, k, r - 1, c - 1, 0, 0);
            cout << nodes[1].sum << "\n";
        }
    }
    return 0;
}