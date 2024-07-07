/* CSC14111 - 21KHMT - Lab 2: Backtracking algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q3. The maze problem.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

const std::string inPath = "inputs/";
const int numSpacesBetweenSquares = 1;

std::pair<int,int> operator+(const std::pair<int, int>& x, const std::pair<int, int>& y) {
    return std::make_pair(x.first + y.first, x.second + y.second);
}

bool getValidPath
(char** maze, std::pair<int, int> mzDim, std::pair<int, int> currPos) {
    const static std::pair<int, int> moves[4] =
        {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    if (currPos.first < 0 || currPos.first >= mzDim.first
        || currPos.second < 0 || currPos.second >= mzDim.second
        || maze[currPos.first][currPos.second] == '#'
        || maze[currPos.first][currPos.second] == 'X') return false;
    
    if (maze[currPos.first][currPos.second] == 'G') return true;
    maze[currPos.first][currPos.second] = 'X';

    for (int i = 0; i < 4; i++)
        if (getValidPath(maze, mzDim, currPos + moves[i])) return true;
    
    maze[currPos.first][currPos.second] = ' ';
    return false;
}

int main() {
    std::ifstream inFile(inPath + "3.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    std::stringstream sline(line);
    std::pair<int, int> mzDim; // (height, width)
    sline >> mzDim.second >> mzDim.first;

    std::getline(inFile, line);
    sline.clear(); sline.str(line);
    std::pair<int, int> start; // (y, x) or (row, col)
    sline >> start.second >> start.first;    

    std::getline(inFile, line);
    sline.clear(); sline.str(line);
    std::pair<int, int> goal; // (y, x) or (row, col)
    sline >> goal.second >> goal.first;

    char** maze = new char*[mzDim.first];
    for (int i = 0; i < mzDim.first; i++) {
        maze[i] = new char[mzDim.second];

        std::getline(inFile, line);
        const int splitLen = numSpacesBetweenSquares + 1;
        for (int j = 0; j < mzDim.second; j++)
            maze[i][j] = line.substr(j * splitLen, splitLen)[0];
    }
    inFile.close();

    if (!getValidPath(maze, mzDim, start))
        std::cout << "No solution\n";
    else {
        maze[start.first][start.second] = 'S';
        for (int i = 0; i < mzDim.first; i++) {
            for (int j = 0; j < mzDim.second; j++)
                std::cout << maze[i][j] << " ";
            std::cout << "\n";
        }
    }

    std::cout << std::flush;
    for (int i = 0; i < mzDim.first; i++) delete[] maze[i];
    delete[] maze;
    return 0;
}