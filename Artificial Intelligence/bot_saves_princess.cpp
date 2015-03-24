/*
 * https://www.hackerrank.com/challenges/saveprincess
 */

#include <iostream>
#include <vector>
using namespace std;
void getBotPrincessPos(const vector<string>& grid, int& sx, int& sy, int& ex, int& ey);

void displayPathtoPrincess(int n, vector <string> grid){
    int sx,sy,ex,ey;
    getBotPrincessPos(grid, sx, sy, ex, ey);
    
    int vertical_moves = sy-ey;
    int horizontal_moves = sx-ex;
    
    string vertical_step("UP");
    if(vertical_moves<0) {
        vertical_step="DOWN";
        vertical_moves *= -1;
    }
    string horizontal_step("LEFT");
    if(horizontal_moves<0) {
        horizontal_step="RIGHT";
        horizontal_moves *= -1;
    }
    
    while(vertical_moves--) {
        cout<<vertical_step<<endl;
    }
    while(horizontal_moves--) {
        cout<<horizontal_step<<endl;
    }
}

void getBotPrincessPos(const vector<string>& grid, int& sx, int& sy, int& ex, int& ey) {
    for(int i=0;i<grid.size();++i) {
        for(int j=0;j<grid[i].size();++j) {
            if(grid[i][j] == 'm') {
                sy=i;sx=j;
            } else if(grid[i][j] == 'p') {
                ey=i;ex=j;
            }
        }
    }
}
int main(void) {

    int m;
    vector <string> grid;

    cin >> m;

    for(int i=0; i<m; i++) {
        string s; cin >> s;
        grid.push_back(s);
    }

    displayPathtoPrincess(m,grid);

    return 0;
}