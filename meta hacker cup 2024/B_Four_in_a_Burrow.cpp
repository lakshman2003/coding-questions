#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int ROWS = 6;
const int COLS = 7;

int dx[] = {0, 1, 1, 1};
int dy[] = {1, 0, 1, -1};

bool in_bounds(int x, int y)
{
    return x >= 0 && x < ROWS && y >= 0 && y < COLS;
}

vector<pair<int, int>> valid_sequence(vector<string> &grid, char player, int x, int y, int dir)
{
    vector<pair<int, int>> sequence;
    for (int k = 0; k < 4; ++k)
    {
        int nx = x + k * dx[dir];
        int ny = y + k * dy[dir];
        if (!in_bounds(nx, ny) || grid[nx][ny] != player)
        {
            return {}; // Return an empty vector if the sequence is invalid
        }
        sequence.push_back({nx, ny}); // Add the coordinates of the sequence
    }
    return sequence;
}

// Function to find all winning sequences for a given player
vector<vector<pair<int, int>>> find_sequences(vector<string> &grid, char player)
{
    vector<vector<pair<int, int>>> sequences;

    // Check each cell as a potential starting point
    for (int r = 0; r < ROWS; ++r)
    {
        for (int c = 0; c < COLS; ++c)
        {
            if (grid[r][c] == player)
            {
                // Check all 4 directions (horizontal, vertical, two diagonals)
                for (int dir = 0; dir < 4; ++dir)
                {
                    vector<pair<int, int>> seq = valid_sequence(grid, player, r, c, dir);
                    if (!seq.empty())
                    {
                        sequences.push_back(seq); // Store the 4 coordinates of the valid sequence
                    }
                }
            }
        }
    }
    return sequences;
}

// Function to simulate filling the grid and check if the sequence is the first valid one
bool is_first_winning_sequence(vector<string> &grid, char player, vector<pair<int, int>> &sequence)
{
    // Create a copy of the grid up to the current sequence
    vector<string> simulated_grid = grid;

    // Fill all plots up to the current winning sequence (without filling above the sequence)
    for (int r = 0; r <= sequence[0].first; ++r)
    {
        for (int c = 0; c < COLS; ++c)
        {
            if (simulated_grid[r][c] == '.')
            {
                simulated_grid[r][c] = (r + c) % 2 == 0 ? 'C' : 'F'; // Simulate alternating turns
            }
        }
    }

    // Now check if there's any other valid sequence for either player
    for (int r = 0; r < ROWS; ++r)
    {
        for (int c = 0; c < COLS; ++c)
        {
            if (simulated_grid[r][c] == 'C' || simulated_grid[r][c] == 'F')
            {
                for (int d = 0; d < 4; ++d)
                {
                    vector<pair<int, int>> other_seq = valid_sequence(simulated_grid, simulated_grid[r][c], r, c, d);
                    if (!other_seq.empty())
                    {
                        if (other_seq != sequence)
                        { // If this is a different sequence
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true; // No other sequence found, this must be the first
}

void fill_grid_except(vector<string> &grid, const vector<pair<int, int>> &sequence)
{
    vector<string> old = grid;

    for (int r = 0; r < ROWS; ++r)
    {
        for (int c = 0; c < COLS; ++c)
        {
            grid[r][c] = '.';
            // Skip filling cells directly above the sequence
            bool skip = false;
            for (const auto &point : sequence)
            {
                int seq_x = point.first;
                int seq_y = point.second;
                // Leave the cells directly above the sequence untouched
                if (c == seq_y && r >= seq_x)
                {
                    grid[r][c] = old[r][c];
                }
            }
        }
    }
}

// Function to solve for each test case
void solve_case(int case_num, vector<string> &grid)
{
    bool c_wins = false, f_wins = false;

    // Find all winning sequences for Connie (C) and Forrest (F)
    vector<vector<pair<int, int>>> c_sequences = find_sequences(grid, 'C');
    vector<vector<pair<int, int>>> f_sequences = find_sequences(grid, 'F');

    // for(auto it: c_sequences)
    // {
    //     for(auto it2: it)
    //     {
    //         cout << it2.first << " " << it2.second << endl;
    //     }
    //     cout << endl;
    // }

    // Check if Connie wins and if it's a valid first sequence
    for (auto &seq : c_sequences)
    {
        vector<string> ngrid = grid;
        fill_grid_except(ngrid, seq);
        // for (auto it : seq)
        // {
        //     cout << it.first << " " << it.second << endl;
        // }
        // for (auto it : ngrid)
        // {
        //     cout << it << endl;
        // }
        vector<vector<pair<int, int>>> f_sequences_ = find_sequences(ngrid, 'F');
        if (f_sequences_.size() == 0)
        {
            // cout << "hehe" << endl;
            c_wins = 1;
        }
    }

    // Check if Forrest wins and if it's a valid first sequence
    for (auto &seq : f_sequences)
    {
        vector<string> ngrid = grid;
        fill_grid_except(ngrid, seq);
        // for (auto it : seq)
        // {
        //     cout << it.first << " " << it.second << endl;
        // }
        // for (auto it : ngrid)
        // {
        //     cout << it << endl;
        // }
        vector<vector<pair<int, int>>> c_sequences_ = find_sequences(ngrid, 'C');
        // for (auto it2 : c_sequences_)
        // {
        //     for (auto it : it2)
        //         cout << it.first << " " << it.second << endl;
        // }
        if (c_sequences_.size() == 0)
        {
            // cout << "hehe" << endl;
            f_wins = 1;
        }
    }

    // Determine the result for this test case
    cout << "Case #" << case_num << ": ";
    if (c_wins && !f_wins)
    {
        cout << "C\n";
    }
    else if (f_wins && !c_wins)
    {
        cout << "F\n";
    }
    else if (c_sequences.size() && f_sequences.size())
    {
        cout << "?\n";
    }
    else
    {
        cout << "0\n";
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t)
    {
        vector<string> grid(ROWS);
        for (int r = 0; r < ROWS; ++r)
        {
            cin >> grid[r];
        }
        solve_case(t, grid);
    }
    return 0;
}