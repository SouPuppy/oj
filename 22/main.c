#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 10000  // primes < 10000
#define MAXP 1300   // number of primes below 10000

bool is_prime[MAXN];
int primes[MAXP], prime_count = 0;

/** Data Structures */

int head[MAXN], edge_count = 0;

struct Edge {
    int to;
    int next; // link list
} edges[MAXP * 40];

/** add edge from -> to */
void add_edge(int from, int to) {
    edges[++edge_count] = (struct Edge) {to, head[from]};
    head[from] = edge_count;
}

/** get prime numbers from 1 to 10000 using Eurlar's method */
void get_primes() {
    memset(is_prime, true, sizeof is_prime);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i < MAXN; i++) {
        if (is_prime[i]) {
            primes[prime_count++] = i;
        }

        for (int j = 0; j < prime_count && i * primes[j] < MAXN; j++) {
            is_prime[i * primes[j]] = false;
            if (i % primes[j] == 0) break;
        }
    }
}

/** generate graph between 4-digits primes using dfs */

bool dfs_visited[MAXN];

void _gen_graph(int p) {
    // dfs_visited
    if (dfs_visited[p]) return ;
    dfs_visited[p] = true;
    
    // first digit
    for (int i = 1; i + p / 1000 < 10; i++) {
        int x = p + 1000 * i;
        if (is_prime[x]) {
            add_edge(p, x);
            add_edge(x, p);
            _gen_graph(x);
        }
    }

    // second digit
    for (int i = 1; i + (p / 100) % 10 < 10; i++) {
        int x = p + 100 * i;
        if (is_prime[x]) {
            add_edge(p, x);
            add_edge(x, p);
            _gen_graph(x);
        }
    }

    // third digit
    for (int i = 1; i + (p / 10) % 10 < 10; i++) {
        int x = p + 10 * i;
        if (is_prime[x]) {
            add_edge(p, x);
            add_edge(x, p);
            _gen_graph(x);
        }
    }

    // last digit
    for (int i = 1; i + p % 10 < 10; i++) {
        int x = p + i;
        if (is_prime[x]) {
            add_edge(p, x);
            add_edge(x, p);
            _gen_graph(x);
        }
    }
}

void gen_graph() {
    // initialize graph
    memset(head, 0, sizeof head);

    // initialize dfs graph
    memset(dfs_visited, false, sizeof dfs_visited);

    // build graph using dfs
    for (int i = 1000; i < MAXN; i++) {
        if (is_prime[i]) {
            _gen_graph(i);
        }
    }
}

/** calculare shortest distance using bfs */
int bfs_visited[MAXN];
int dist[MAXN];

#define MAXQ MAXP

struct Queue {
    int _data[MAXQ];
    int head, tail;
};

void init_queue(struct Queue *q) {
    q->head = q->tail = 0;
}

void push(struct Queue *q, int x) {
    q->_data[q->tail] = x;
    q->tail = (q->tail + 1) % MAXQ;
}

int pop(struct Queue *q) {
    int ret = q->_data[q->head];
    q->head = (q->head + 1) % MAXQ;
    return ret;
}

bool is_empty(struct Queue *q) {
    return q->head == q->tail;
}

int bfs(int ts, int source, int dest) {
    if (source == dest) return 0;

    // initialize dist
    memset(dist, 0, sizeof dist);

    struct Queue q;
    init_queue(&q);

    // push source
    bfs_visited[source] = ts;
    dist[source] = 0;
    push(&q, source);
    
    while (!is_empty(&q)) {
        int x = pop(&q);
        for (int i = head[x]; i; i = edges[i].next) {
            int j = edges[i].to;

            // not dfs_visited
            if (bfs_visited[j] < ts) {
                bfs_visited[j] = ts;
                dist[j] = dist[x] + 1;
                if (j == dest) {
                    return dist[j];
                }
                push(&q, j);
            }
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    get_primes();
    gen_graph();
    
    // main logic
    memset(bfs_visited, 0, sizeof bfs_visited);

    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    for(int i = 1; i <= n; i++) {
        int from, to;
        if (scanf("%d %d", &from, &to) != 2) break;
        else printf("%d\n", bfs(i, from, to));
    }
    return 0;
}