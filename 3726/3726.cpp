#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>

int record[85];
char string[82];
int gr[10];

int main() {
    int t = 0;

    int n, k;
    scanf("%d %d", &n, &k);
    while (n != 0 && k != 0) {
        if (t > 0) {
            printf("\n");
        }
        memset(record, 0, sizeof(record));

        // Get input
        for (int i = 0; i < n; i++) {
            scanf("%s", string);
            int s = strlen(string);
            //printf("string is %s and len is %d\n", string, s);
            assert(s > 0 && s <= 80);
            record[s]++;
        }

        // Check we can make groups
        bool group = true;
        int r = 0;
        for (int i = 0; i < (n / k); i++) {
            memset(gr, 0, sizeof(gr));
            int g = 0;
            int a = 0;
            for (int j = 0; j < k; j++) {
                while (record[r] == 0) {
                    r++;
                }
                a += r;
                record[r]--;
                gr[g++] = r;
                //printf("record %d\n", r);
            }
            a = a / k;
            //printf("a %d k %d \n", a, k);
            for (int j = 0; j < g; j++) {
                if (abs(gr[j] - a) > 2) {
                    group = false;
                    break;
                }
            }
            if (!group) {
                break;
            }
        }

        // Print out result
        if (!group) {
            printf("Case %d: no\n", t + 1);
        } else {
            printf("Case %d: yes\n", t + 1);
        }

        // Get ready for next test case
        t++;
        scanf("%d %d", &n, &k);
    }
}
