#include <iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

vector<vector<bool>> field;

void initializeField(vector<vector<bool>> &field, size_t height=8, size_t width=16)
{
    vector<bool> row;

    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            row.push_back(0);
        }
        field.push_back(row);
        row.clear();
    }
}

void clearField(vector<vector<bool>> &field, size_t height, size_t width)
{
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            field[i][j] = 0;
        }
    }
}

void printField(vector<vector<bool>>& field, size_t height, size_t width)
{
    cout << "Current field:" << endl;
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if (field[i][j] == 1) cout << "@";
            else cout << "-";
        }
        cout << endl;
    }
}

int countNeighbours(vector<vector<bool>> field, size_t height, size_t width, size_t coordinateX, size_t coordinateY)
{
    int countN = 0;

    if (coordinateX > 0 && coordinateX < height - 1)
    {
        if (coordinateY > 0 && coordinateY < width - 1)
        {
            for (int i = coordinateX - 1; i <= coordinateX + 1; i++)
            {
                for (int j = coordinateY - 1; j <= coordinateY + 1; j++)
                {
                    if (field[i][j] == true && !(i == coordinateX && j == coordinateY))countN++;
                }
            }
        }
        else if (coordinateY == 0)
        {
            for (int i = coordinateX - 1; i <= coordinateX + 1; i++)
            {
                for (int j = coordinateY; j <= coordinateY + 1; j++)
                {
                    if (field[i][j] == true && !(i == coordinateX && j == coordinateY))countN++;
                }
            }
        }
        else
        {
            for (int i = coordinateX - 1; i <= coordinateX + 1; i++)
            {
                for (int j = coordinateY - 1; j <= coordinateY; j++)
                {
                    if (field[i][j] == true && !(i == coordinateX && j == coordinateY))countN++;
                }
            }
        }
    }
    else if (coordinateX == 0)
    {
        if (coordinateY > 0 && coordinateY < width - 1)
        {
            for (int i = coordinateX ; i <= coordinateX + 1; i++)
            {
                for (int j = coordinateY - 1; j <= coordinateY + 1; j++)
                {
                    if (field[i][j] == true && !(i == coordinateX && j == coordinateY))countN++;
                }
            }
        }
        else if (coordinateY == 0)
        {
            for (int i = coordinateX; i <= coordinateX + 1; i++)
            {
                for (int j = coordinateY; j <= coordinateY + 1; j++)
                {
                    if (field[i][j] == true && !(i == coordinateX && j == coordinateY))countN++;
                }
            }

        }
        else
        {
            for (int i = coordinateX; i <= coordinateX + 1; i++)
            {
                for (int j = coordinateY - 1; j <= coordinateY; j++)
                {
                    if (field[i][j] == true && !(i == coordinateX && j == coordinateY))countN++;
                }
            }

        }
    }
    else
    {
        if (coordinateY > 0 && coordinateY < width - 1)
        {
            for (int i = coordinateX-1; i <= coordinateX; i++)
            {
                for (int j = coordinateY - 1; j <= coordinateY + 1; j++)
                {
                    if (field[i][j] == true && !(i == coordinateX && j == coordinateY))countN++;
                }
            }
        }
        else if (coordinateY == 0)
        {
            for (int i = coordinateX-1; i <= coordinateX; i++)
            {
                for (int j = coordinateY; j <= coordinateY + 1; j++)
                {
                    if (field[i][j] == true && !(i == coordinateX && j == coordinateY))countN++;
                }
            }

        }
        else
        {
            for (int i = coordinateX-1; i <= coordinateX; i++)
            {
                for (int j = coordinateY - 1; j <= coordinateY; j++)
                {
                    if (field[i][j] == true && !(i == coordinateX && j == coordinateY))countN++;
                }
            }

        }
    }
    return countN;
}

void keepNeighboursCount(int** fieldCountN, vector<vector<bool>>& field, size_t height, size_t width)
{
    for (size_t i = 0; i < height; i++)
    {
        fieldCountN[i] = new int[width];
        for (size_t j = 0; j < width; j++)
        {
            fieldCountN[i][j] = countNeighbours(field, height, width, i, j);
            cout << fieldCountN[i][j];
        }
        cout << endl;
    }
}

void stepForward(int** countNeighbours, vector<vector<bool>>& field, size_t height, size_t width)
{
    keepNeighboursCount(countNeighbours, field, height, width);

    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if (field[i][j] == 1 && (countNeighbours[i][j] < 2 || countNeighbours[i][j] > 3))
            {
                field[i][j] = 0;
            }
            else if (field[i][j] == 0 && countNeighbours[i][j] == 3)
            {
                field[i][j] = 1;
            }

        }
    }
}

void widenUpOrDown(vector<vector<bool>> &field, size_t &height, size_t &width, int shiftStep, bool isDirectionUp)
{
    vector<bool> row;

    int insertStep = 0;

    for (int i = 0; i < width; i++)
    {
        row.push_back(0);
    }
    if (isDirectionUp == 0) insertStep += field.size();

    for (int i = 0; i < shiftStep; i++)
    {
        field.insert(field.begin() + insertStep, row);
    }
    
    height += shiftStep;
}

void widenLeftOrRight(vector<vector<bool>> &field, size_t &height, size_t &width, int shiftStep, bool isDirectionLeft)
{
    vector<bool> col;

    int insertStep = 0;

    if (isDirectionLeft == 0) insertStep += field[0].size();

    for (int i = 0; i < height; i++)
    {
        field[i].insert(field[i].begin() + insertStep, 0);
    }

    width += shiftStep;
}

void resizeField(vector<vector<bool>> &field, size_t &oldHeight, size_t &oldWidth, size_t newHeight, size_t newWidth)
{
    if (oldHeight > newHeight)
    {
        for (size_t i = newHeight; i < oldHeight; i++)
        {
            field[i].clear();
        }
    }
    else
    {
        for (size_t i = oldHeight; i < newHeight; i++)
        {
            field.push_back({0});
            for (size_t j = 0; j < oldWidth; j++)
            {
                field[i].push_back(0);
            }
        }
    }
    oldHeight = newHeight;
    if (oldWidth > newWidth)
    {
        for (size_t i = 0; i < newHeight; i++)
        {
            for (size_t j = newWidth; j < oldWidth; j++)
            {
                field[i].pop_back();
            }
        }
    }
    else
    {
        for (size_t i = 0; i < oldHeight; i++)
        {
            for (size_t j = oldWidth; j < newWidth; j++)
            {
                field[i].push_back(0);
            }
        }
    }
    oldWidth = newWidth;
}

void toggleCell(vector<vector<bool>> &field, size_t &height, size_t &width, int coordinateX, int coordinateY)
{
    coordinateX--;
    coordinateY--;

    bool doWidenUp, doWidenLeft;

    if (coordinateX < 0) doWidenUp = 1;
    else if (coordinateX >= height) doWidenUp = 0;

    if(coordinateX< 0 || coordinateX >= height) widenUpOrDown(field, height, width, coordinateX, doWidenUp);

    if (coordinateY < 0) doWidenLeft = 1;
    else if (coordinateY >= width) doWidenLeft = 0;

    if (coordinateY<0 || coordinateX >= height) widenLeftOrRight(field, height, width, coordinateX, doWidenLeft);

    field[coordinateX][coordinateY] = !(field[coordinateX][coordinateY]);
}

void saveToFile(vector<vector<bool>> field)
{

}

void randomizeField()
{

}

bool translateFieldCharToBool(string row, int index)
{
    if (row[index] == '@')return 1;
    else return 0;
}

void readFile()
{
    std::ifstream file("C:\C++\GameOfLife\x64\Debug\gay.txt");

    if (!file.is_open()) {
        std::cerr << "Unable to open file\n";

    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
}

void loadFile(vector<vector<bool>>& field, string nameOfFile, size_t& height, size_t& width)
{
    ifstream inputFile(nameOfFile);

    string row;

    int indRow = 0, indCol = 0;


    if (inputFile.is_open())
    {
        while (getline(inputFile, row))
        {
            field.push_back({});
            for (int i = 0; i < row.length(); i++)
            {
                cout << translateFieldCharToBool(row, i);
                field[indRow].push_back(translateFieldCharToBool(row, i));
            }
            cout << endl;
            indRow++;
        }
        inputFile.close();
    }
    cout << indRow << endl;
    height = indRow;
    width = field[0].size();

}

int main()
{
    int begin, step = 0;

    size_t h = 8, w = 16;
    size_t newH, newW, coordinateX, coordinateY;

    string fileName, row;

    int** neighboursCount = new int* [h];
    cout << "Welcome to the Game of Life! Please choose an option:" << endl;
    cout << "For \"New game\" please enter 1...\nFor \"Load game\" please enter 2...\nFor \"Exit\" please enter 3..." << endl;
    cin >> begin;
    if (begin == 1)initializeField(field);
    else if (begin == 2)
    {
        /*cout << "Enter filename: " << endl;
        cin >> fileName;*/
        //loadFile(field, "C:\C++\GameOfLife\\x64\Debug\gay.txt", h, w);
        readFile();
    }
    else if (begin==3) return 0;

    while (step != 10)
    {
        printField(field, h, w);

        cout << "Please choose an option:" << endl;
        cout << "For \"Step forward\" please enter 4...\nFor \"Resize\" please enter 5...\nFor \"Toggle cell\" please enter 6..." << endl;
        cout << "For \"Clear\" please enter 7...\nFor \"Randomize\" please enter 8...\nFor \"Save to file\" please enter 9..." << endl;
        cout << "For \"End\" please enter 10" << endl;

        cin >> step;

        switch (step)
        {
        case 4: stepForward(neighboursCount, field, h, w); break;
        case 5: 
        {
            cout << "PLease input new height: ";
            cin >> newH;
            cout << "PLease input new width: ";
            cin >> newW;
            resizeField(field, h, w, newH, newW);
        }; break;
        case 6:
        {
            cout << "PLease input coordinate X: ";
            cin >> coordinateX;
            cout << "PLease input coordinate Y: ";
            cin >> coordinateY;
            toggleCell(field, h, w, coordinateX, coordinateY);
            cout << field[coordinateX][coordinateY] << endl;

        }; break;
        case 7:
        {
            clearField(field, h, w);
        } break;
        case 8:; break;
        case 9:; break;
        }
    }

    for (int i = 0; i < h; ++i) 
    {
        delete[] neighboursCount[h];
    }

    delete neighboursCount;

}
