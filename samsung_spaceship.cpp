#include <bits/stdc++.h>
using namespace std;

int a[10][5];
int ans;
int n;

void dfs(int row, int col, int coins, bool bomb)
{
    if (row < 0)
    {
        ans = max(ans, coins);
        return;
    }

    for (int dc = -1; dc <= 1; dc++)
    {
        int nc = col + dc;

        if (nc < 0 || nc >= 5)
            continue;

        /*
         * Option 1:
         * Move normally.
         */
        if (a[row][nc] != 2)
        {
            int add = (a[row][nc] == 1);

            dfs(row - 1,
                nc,
                coins + add,
                bomb);
        }

        /*
         * Option 2:
         * Use bomb now.
         *
         * Bomb clears enemies in the current
         * 5 x 5 region.
         */
        if (!bomb)
        {
            int temp[10][5];

            // Copy grid
            for (int i = 0; i < n; i++)
                for (int j = 0; j < 5; j++)
                    temp[i][j] = a[i][j];

            // Destroy enemies in current 5 rows
            for (int i = row; i >= max(0, row - 4); i--)
            {
                for (int j = 0; j < 5; j++)
                {
                    if (a[i][j] == 2)
                        a[i][j] = 0;
                }
            }

            // Now move into the cell
            int add = (a[row][nc] == 1);

            dfs(row - 1,
                nc,
                coins + add,
                true);

            // Restore grid
            for (int i = 0; i < n; i++)
                for (int j = 0; j < 5; j++)
                    a[i][j] = temp[i][j];
        }
    }
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                cin >> a[i][j];
            }
        }

        ans = 0;

        // Spaceship starts in middle column
        dfs(n - 1, 2, 0, false);

        cout << ans << '\n';
    }

    return 0;
}
