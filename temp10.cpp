#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minCarsToAdd(int n, vector<int> &carLengths)
{
    sort(carLengths.begin(), carLengths.end());
    long long miss = 1;
    int i = 0, added_cars = 0;
    int m = carLengths.size();

    while (miss <= n)
    {
        if (i < m && carLengths[i] <= miss)
        {
            miss+=carLengths[i];
            i++;
        }
        else
        {
            miss += miss;
            added_cars++;
        }
    }

    return added_cars;
}

int main()
{
    int m, n;
    cin >> m >> n;
    vector<int> carLengths(m);
    for (int i = 0; i < m; ++i)
    {
        cin >> carLengths[i];
    }
    cout << minCarsToAdd(n, carLengths) << endl;
    return 0;
}
