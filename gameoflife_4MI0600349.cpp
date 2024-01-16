#include <iostream>
#include<vector>
#include<string>
#include<fstream>
#include<stdlib.h> 
#include<cmath>
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

void stepForward(int** fieldCountN, vector<vector<bool>>& field, size_t height, size_t width)
{
    keepNeighboursCount(fieldCountN, field, height, width);

    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if (field[i][j] == 1 && (fieldCountN[i][j] < 2 || fieldCountN[i][j] > 3))
            {
                field[i][j] = 0;
            }
            else if (field[i][j] == 0 && fieldCountN[i][j] == 3)
            {
                field[i][j] = 1;
            }

        }
    }
}

void widenUp(vector<vector<bool>> &field, size_t &height, size_t &width, int shiftStep)
{
    int shiftSize = (-1)*shiftStep + 1;

    vector<bool> row = {};

    for (int i = 0; i < width; i++)
    {
        row.push_back(0);
    }

    for (int i = 0; i < shiftSize; i++)
    {
        field.insert(field.begin(), row);
    }    

    height += shiftSize;
}

void widenLeft(vector<vector<bool>> &field, size_t &height, size_t &width, int shiftStep)
{
    int shiftSize = (-1)*shiftStep + 1;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < shiftSize; j++)
        {
            field[i].insert(field[i].begin(), 0);
        }
    }
    width += shiftSize;
}

void resizeField(vector<vector<bool>> &field, size_t &oldHeight, size_t &oldWidth, size_t newHeight, size_t newWidth)
{
    if (oldHeight > newHeight)
    {
        for (size_t i = newHeight; i < oldHeight; i++)
        {
            field.erase(field.end()-1);
        }
    }
    else if(oldHeight < newHeight)
    {
        vector<bool> row = {};

        for (size_t i = 0; i < newWidth; i++)
        {
            row.push_back(0);
        }

        for (size_t i = oldHeight; i < newHeight; i++)
        {
            field.push_back(row);
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
    else if (oldWidth < newWidth)
    {
        for (size_t i = 0; i < newHeight; i++)
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
    bool doWidenUp = 0, doWidenLeft = 0;

    cout << "Check 1" << endl;

    if (coordinateX <= 0)
    {
        widenUp(field, height, width, coordinateX);
        coordinateX = 1;
    }
    else if (coordinateX > height) resizeField(field, height, width, coordinateX, width);

    cout << "Check 2" << endl;

    if (coordinateY <= 0)
    {
        widenLeft(field, height, width, coordinateY);
        coordinateY = 1;
    }
    else if (coordinateY > width) resizeField(field, height, width, height, coordinateY);

    if (field[coordinateX-1][coordinateY-1] == 0) field[coordinateX-1][coordinateY-1] = 1;
    else field[coordinateX-1][coordinateY-1] = 0;

}

void randomizeField(vector<vector<bool>> &field, size_t& height, size_t& width, int n)
{
    int nQuotient;
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            nQuotient = rand() % n + 1;
            if (nQuotient == 1)field[i][j] = 1;
            else field[i][j] = 0;
        }
    }
}

bool translateFieldCharToBool(string row, int index)
{
    if (row[index] == '@')return 1;
    else return 0;
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
                field[indRow].push_back(translateFieldCharToBool(row, i));
            }
            indRow++;
        }
        inputFile.close();
    }
    height = indRow;
    width = field[0].size();
}

void saveToFile(vector<vector<bool>> field)
{

}

int main()
{
    int begin, step = 0, n;

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
        cout << "Enter filename:\nNote: For maximum accuracy, please provide absolute filepath.\nE.g.: C\\C++\\GameOfLife\\example.txt NOT example.txt!" << endl;
        cin >> fileName;
        loadFile(field, fileName, h, w);
    }
    else if (begin == 3) return 0;

    while (step != 10)
    {
        cout << "tuka li bugvash dac ti eba maikara" << endl;
        printField(field, h, w);
        cout << "tuka li bugvash dac ti eba maikara ETOOOOOOOOOOO" << endl;

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
            cout << "Check 5" << endl;
        }; break;
        case 7:
        {
            clearField(field, h, w);
        } break;
        case 8: 
        {
            cout << "Please enter randomization quotient: " << endl;
            cin >> n;
            randomizeField(field, h, w, n);
        };
        break;
        case 9:; break;
        }
    }

    for (int i = 0; i < h; ++i)
    {
        delete[] neighboursCount[i];
    }

    delete[] neighboursCount;

}
