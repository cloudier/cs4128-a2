#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>

#define N 210
#define M 210

int gr[N][M];
int n, m;
int sn[N][M];
int head_i, head_j;
int tail_i, tail_j;

using namespace std;

int  parent[N*M];
int  subtree_size[N*M];

void  init(int n) {
    for (int i = 0; i <= n; i++) {
        parent[i] = i; subtree_size[i] = 1;
    }
}
int  root(int x) {
    //  only  roots  are  their  own  parents
    //  otherwise  apply  path  compression
    return  parent[x] == x ? x : parent[x] = root(parent[x]);
}
void  join(int x, int y) {
    //  size  heuristic
    //  hang  smaller  subtree  under  root  of  larger  subtree
    x = root(x); y = root(y);
    if (x == y) return;
    if (subtree_size[x] < subtree_size[y]) {
        parent[x] = y;
        subtree_size[y] +=  subtree_size[x];
    } else {
        parent[y] = x;
        subtree_size[x] +=  subtree_size[y];
    }
}

int index(int i, int j) {
    return i * m + j;
}

int cntones(int i, int j) {
    int ones = 0;
    if (i + 1 < n && gr[i + 1][j] == 1) {
        ones++;
    }
    if (i - 1 >= 0 && gr[i - 1][j] == 1) {
        ones++;
    }
    if (j + 1 < m && gr[i][j + 1] == 1) {
        ones++;
    }
    if (j - 1 >= 0 && gr[i][j - 1] == 1) {
        ones++;
    }
    return ones;
}

bool lengthen(int i, int j) {
    if (i < 0 || i >= n || j < 0 || j >= n) {
        return false;
    }
    if (gr[i][j] == 1) {
        return false;
    }
    /*
    if (cntones(i, j) == 1) {
        printf("length %d %d\n", i, j);
    }
    */
    return cntones(i, j) == 1;
}

void find_head() {
    sn[head_i][head_j] = 1;
    if (cntones(head_i, head_j) == 1) {
        return;
    }

    if (head_i + 1 < n && gr[head_i + 1][head_j] == 1 &&
            sn[head_i + 1][head_j] == 0) {
        head_i++;
        find_head();
    } else if (head_i - 1 >= 0 && gr[head_i - 1][head_j] == 1 &&
            sn[head_i - 1][head_j] == 0) {
        head_i--;
        find_head();
    } else if (head_j + 1 < m && gr[head_i][head_j + 1] == 1 &&
            sn[head_i][head_j + 1] == 0) {
        head_j++;
        find_head();
    } else if (head_j - 1 >= 0 && gr[head_i][head_j - 1] == 1 &&
            sn[head_i][head_j - 1] == 0) {
        head_j--;
        find_head();
    }
}

void find_tail() {
    sn[tail_i][tail_j] = 1;
    if (tail_i + 1 < n && gr[tail_i + 1][tail_j] == 1 &&
            sn[tail_i + 1][tail_j] == 0) {
        tail_i++;
        find_tail();
    } else if (tail_i - 1 >= 0 && gr[tail_i - 1][tail_j] == 1 &&
            sn[tail_i - 1][tail_j] == 0) {
        tail_i--;
        find_tail();
    } else if (tail_j + 1 < m && gr[tail_i][tail_j + 1] == 1 &&
            sn[tail_i][tail_j + 1] == 0) {
        tail_j++;
        find_tail();
    } else if (tail_j - 1 >= 0 && gr[tail_i][tail_j - 1] == 1 &&
            sn[tail_i][tail_j - 1] == 0) {
        tail_j--;
        find_tail();
    }
}

int main() {
    scanf("%d %d", &n, &m);

    while (n != 0 && m != 0) {
        //printf("scan in\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%1d", &gr[i][j]);
            }
        }

        //printf("init\n");
        init(n * m);

        // connect any 1s to N/S/E/W 1s
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (gr[i][j] == 1 && i + 1 < n &&
                        gr[i + 1][j] == 1) {
                    join(index(i, j), index(i + 1, j));
                }
                if (gr[i][j] == 1 && i - 1 >= 0 &&
                        gr[i - 1][j] == 1) {
                    join(index(i, j), index(i - 1, j));
                }
                if (gr[i][j] == 1 && j + 1 < m &&
                        gr[i][j + 1] == 1) {
                    join(index(i, j), index(i, j + 1));
                }
                if (gr[i][j] == 1 && j - 1 >= 0 &&
                        gr[i][j - 1] == 1) {
                    join(index(i, j), index(i, j - 1));
                }
            }
        }

        /*
        // debug
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d", gr[i][j]);
            }
        printf("\n");
        }
        printf("\n");
        */

        // find roots
        int max_snakes = 0;
        set<int> seen;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (gr[i][j] == 1 &&
                        seen.find(root(index(i, j))) == seen.end()) {
                    bool snake = true;

                    // find heads/tails of snakes
                    for (int i = 0; i < n; i++) {
                        memset(sn[i], 0, sizeof(sn[i]));
                    }
                    head_i = i;
                    head_j = j;
                    find_head();
                    tail_i = i;
                    tail_j = j;
                    find_tail();
                    /*
                    printf("head i %d j %d tail i %d j %d i %d j %d t %d\n",
                            head_i, head_j, tail_i, tail_j, i, j,
                            root(index(i, j)));
                            */

                    // lengthening heads
                    if (lengthen(head_i + 1, head_j) ||
                            lengthen(head_i - 1, head_j) ||
                            lengthen(head_i, head_j + 1) ||
                            lengthen(head_i, head_j - 1)) {
                        snake = false;
                    }
                    if (snake && head_i != tail_i && head_j != tail_j) {
                        // try to lengthen tail
                        if (lengthen(tail_i + 1, tail_j) ||
                                lengthen(tail_i - 1, tail_j) ||
                                lengthen(tail_i, tail_j + 1) ||
                                lengthen(tail_i, tail_j - 1)) {
                            //printf("tail can length\n");
                            snake = false;
                        }
                    }

                    seen.insert(root(index(i, j)));
                    if (snake) {
                        //printf("inc\n");
                        max_snakes++;
                    }
                }
            }
        }


        printf("%d\n", max_snakes);
        scanf("%d %d", &n, &m);
    }
}

