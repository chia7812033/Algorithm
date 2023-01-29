#include <climits>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

long **createTable(long n, long m);
void deleteTable(long **table, long n, long m);

int main(int argc, char **argv)
{
    ifstream inFile;
    inFile.open(argv[1]);

    long N, A, B;
    inFile >> N >> A >> B;

    long *penaltyArr = new long[N];

    for (long i = 0; i < N; i++)
    {
        inFile >> penaltyArr[i];
    }
    inFile.close();

    long **table = createTable(N, N + 1);
    long **fromTable = createTable(N - 1, N + 1);

    table[0][0] = -penaltyArr[0];
    table[0][1] = A - B;
    for (long i = 1; i < N; i++)
    {
        for (long j = 0; j < N + 1; j++)
        {
            if (i + 1 < j)
            {
                continue;
            }

            if (j == 0)
            {
                long maxP = LONG_MIN;
                long maxIndex;
                for (long k = 0; k < i + 1; k++)
                {
                    if (table[i - 1][k] > maxP)
                    {
                        maxP = table[i - 1][k];
                        maxIndex = k;
                    }
                }
                table[i][j] = maxP - penaltyArr[i];
                fromTable[i - 1][j] = maxIndex;
            }
            else
            {
                table[i][j] = table[i - 1][j - 1] + A - j * j * B;
                fromTable[i - 1][j] = j - 1;
            }
        }
    }

    long maxP = LONG_MIN;
    long maxIndex;
    for (long k = 0; k < N + 1; k++)
    {
        if (table[N - 1][k] > maxP)
        {
            maxP = table[N - 1][k];
            maxIndex = k;
        }
    }

    string path = maxIndex == 0 ? "0" : "1";

    long jPrev = maxIndex;
    for (long i = N - 2; i >= 0; i--)
    {
        jPrev = fromTable[i][jPrev];
        if (jPrev > 0)
        {
            path += " 1";
        }
        else
        {
            path += " 0";
        }
    }

    reverse(begin(path), end(path));

    ofstream outFile;
    outFile.open(argv[2]);
    outFile << maxP << endl;
    outFile << path;
    outFile.close();
    deleteTable(table, N, N + 1);
}

long **createTable(long n, long m)
{
    long **rows = new long *[n];
    for (long i = 0; i < n; i++)
    {
        long *col = new long[m];
        rows[i] = col;
    }
    return rows;
}

void deleteTable(long **table, long n, long m)
{
    for (long i = 0; i < n; i++)
    {
        delete table[i];
    }
    delete table;
}