#include <cstdio>
#include <vector>
#include <set>
#include <cstdlib>

#define N 110
#define E 310

using namespace std;

int  parent[N];
int  subtree_size[N];

void  init(int n) {
    for (int i = 0; i  <= n; i++) {
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

int main() {
    int t = 1;
    int n, e;
    scanf("%d", &n);

    while (n != 0) {
        bool cat = true;

        //printf("sets\n");
        vector<set<int> > al;
        for (int i = 0; i < N; i++) {
            set<int> t;
            al.push_back(t);
        }

        init(N);
        scanf("%d", &e);
        //printf("getting input for n=%d, e=%d\n", n, e);
        for (int i = 0; i < e; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            //printf("i %d, a %d -> b %d, n %d\n", i, a, b, n);

            // Add to UF to check for cycles
            //printf("uf\n");
            if (root(a) == root(b)) {
                cat = false;
                //printf("cycle\n");
            }
            //printf("join\n");
            join(a, b);

            // Add to graph
            //printf("insert\n");
            al[a].insert(b);
            al[b].insert(a);
        }

        // Check graph is connected
        if (cat) {
            //printf("check graph connected\n");
            int x = root(1);
            for (int i = 2; i < n + 1; i++) {
                if (x != root(i)) {
                    //printf("graph not connected\n");
                    cat = false;
                    break;
                }
            }
        }

        if (cat) {
            //printf("find nodes one edge\n");
            // Find nodes with one edge
            set<int> one_edge;
            for (int i = 0; i < n + 1; i++) {
                if (al[i].size() == 1) {
                    one_edge.insert(i);
                }
            }

            //printf("remove nodes one edge\n");
            // remove nodes with one edge
            for (int i = 0; i < one_edge.size(); i++) {
                al[i].clear();
                for (int j = 0; j < n + 1; j++) {
                    for (set<int>::iterator it = al[j].begin();
                            it != al[j].end();) {
                        if (*it == i) {
                            al[j].erase(it++);
                        } else {
                            ++it;
                        }
                    }
                }
            }
            
            // Check remaining nodes have 1 or 2 edges
            //printf("check remaining\n");
            int one_edge_nodes_rem = 0;
            for (int i = 0; i < n + 1; i++) {
                if (one_edge.find(i) != one_edge.end()) {
                    continue;
                } else if (al[i].size() == 1) {
                    one_edge_nodes_rem++;
                    if (one_edge_nodes_rem > 2) {
                        cat = false;
                        break;
                    }
                } else if (al[i].size() > 2) {
                    cat = false;
                    break;
                }
            }
        }

        // Print results and get ready for next case
        if (cat) {
            printf("Graph %d is a caterpillar.\n", t);
        } else {
            printf("Graph %d is not a caterpillar.\n", t);
        }
        scanf("%d", &n);
        t++;
    }
}

