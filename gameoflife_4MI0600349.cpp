#include <iostream>
#include<vector>
#include<string>
#include<fstream>
#include<stdlib.h> 
#include<cmath>
#include<iomanip>

using namespace std;

vector<vector<bool>> field;

void initializeField(vector<vector<bool>>& field, size_t height = 8, size_t width = 16)
{
    vector<bool> row;

    for (size_t j = 0; j < width; j++)
    {
        row.push_back(0);
    }

    for (size_t i = 0; i < height; i++)
    {
        field.push_back(row);
    }
}

void clearField(vector<vector<bool>>& field, size_t height, size_t width)
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

    cout << setw(3) << "1";
    for (int i = 0; i < width - 2; i++)
    {
        cout << " ";
    }
    cout << width << endl;
    for (size_t i = 0; i < height; i++)
    {
        if (i == height - 1 || i==0) cout << setw(2) << i+1;
        else cout << setw(2) << " ";

        for (size_t j = 0; j < width; j++)
        {
            if (field[i][j] == 1) cout << "@";
            else cout << "-";
        }
        cout << endl;
    }
}

unsigned short countNeighbours(vector<vector<bool>> field, size_t height, size_t width, size_t coordinateX, size_t coordinateY)
{
    int countN = 0;

    int beginLoopHeight = coordinateX - 1, endLoopHeight = coordinateX + 1;
    int beginLoopWidth = coordinateY - 1, endLoopWidth = coordinateY + 1;

    if (coordinateX == 0) beginLoopHeight++;
    else if (coordinateX == height - 1) endLoopHeight--;

    if (coordinateY == 0) beginLoopWidth++;
    else if (coordinateY == width - 1) endLoopWidth--;

    for (int i = beginLoopHeight; i <= endLoopHeight; i++)
    {
        for (int j = beginLoopWidth; j <= endLoopWidth; j++)
        {
            if (field[i][j] == true && !(i == coordinateX && j == coordinateY)) countN++;
        }
    }

    return countN;
}

void keepNeighboursCount(unsigned short* fieldCountN, vector<vector<bool>>& field, size_t height, size_t width)
{
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            fieldCountN[i * width + j] = countNeighbours(field, height, width, i, j);
        }
    }
}

void stepForward(unsigned short* fieldCountN, vector<vector<bool>>& field, size_t height, size_t width)
{
    keepNeighboursCount(fieldCountN, field, height, width);

    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if (field[i][j] == 1 && (fieldCountN[i * width + j] < 2 || fieldCountN[i * width + j] > 3))
            {
                field[i][j] = 0;
            }
            else if (field[i][j] == 0 && fieldCountN[i * width + j] == 3)
            {
                field[i][j] = 1;
            }

        }
    }
}

void widenUp(vector<vector<bool>>& field, size_t& height, size_t& width, int shiftStep)
{
    int shiftSize = (-1) * shiftStep + 1;

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

void widenLeft(vector<vector<bool>>& field, size_t& height, size_t& width, int shiftStep)
{
    int shiftSize = (-1) * shiftStep + 1;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < shiftSize; j++)
        {
            field[i].insert(field[i].begin(), 0);
        }
    }
    width += shiftSize;
}

void resizeFieldDownRight(vector<vector<bool>>& field, size_t& oldHeight, size_t& oldWidth, size_t newHeight, size_t newWidth)
{
    if (oldHeight > newHeight)
    {
        for (size_t i = newHeight; i < oldHeight; i++)
        {
            field.erase(field.end() - 1);
        }
    }
    else if (oldHeight < newHeight)
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

void toggleCell(vector<vector<bool>>& field, size_t& height, size_t& width, int coordinateX, int coordinateY)
{
    if (coordinateX <= 0)
    {
        widenUp(field, height, width, coordinateX);
        coordinateX = 1;
    }
    else if (coordinateX > height) resizeFieldDownRight(field, height, width, coordinateX, width);

    if (coordinateY <= 0)
    {
        widenLeft(field, height, width, coordinateY);
        coordinateY = 1;
    }
    else if (coordinateY > width) resizeFieldDownRight(field, height, width, height, coordinateY);

    field[coordinateX - 1][coordinateY - 1] = !(field[coordinateX - 1][coordinateY - 1]);

}

void randomizeField(vector<vector<bool>>& field, size_t& height, size_t& width, int n)
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

char translateFieldBoolToChar(vector<bool> row, int index)
{
    if (row[index] == 1)return '@';
    else return '-';
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
        height = indRow;
        width = field[0].size();
    }
    else
    {
        cout << "Unable to open file for writing." << endl;
    }
}

void saveToFile(vector<vector<bool>> field, string fileName, size_t height, size_t width)
{
    ofstream outFile(fileName);

    if (outFile.is_open())
    {
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                outFile << translateFieldBoolToChar(field[i], j);
            }
            outFile << endl;
        }
        outFile.close();
    }
    else
    {
        cout << "Unable to open file for writing." << endl;
    }
}

void errorMessage()
{
    cout << "Invalid output. Please provide output according to menu rules." << endl;
}

void endMessage()
{
    cout << "Thank you for playing. Please come again!" << endl;
}

int main()
{
    unsigned begin, step = 1, n;
    size_t h = 8, w = 16;
    size_t newH, newW, coordinateX, coordinateY;
    string fileName, row;
    unsigned short neighboursCount[24][80];

    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            neighboursCount[i][j] = 0;
        }
    }

beginningOfGame:

    cout << "Welcome to the Game of Life! Please choose an option:" << endl;
    cout << "For \"New game\" please enter 1...\nFor \"Load game\" please enter 2...\nFor \"Exit\" please enter 3..." << endl;
    cin >> begin;

    if (cin.fail())
    {
        errorMessage();
        goto beginningOfGame;
    }

    if (begin == 1)initializeField(field);

    else if (begin == 2)
    {
        cout << "Enter filename:\nNote: For maximum accuracy, please provide absolute filepath." << endl;
        cout << "E.g.: C:\\C++\\GameOfLife\\example.txt NOT example.txt!" << endl;
        cin >> fileName;
        loadFile(field, fileName, h, w);
    }

    else if (begin == 3)
    {
        endMessage();
        return 0;
    }

    else
    {
        errorMessage();
        goto beginningOfGame;
    }

    while (step)
    {
        printField(field, h, w);

    makeMove:

        cout << "Please choose an option:" << endl;
        cout << "For \"Step forward\" please enter 4..." << endl;
        cout << "For \"Resize\" please enter 5..." << endl;
        cout << "For \"Toggle cell\" please enter 6..." << endl;
        cout << "For \"Clear\" please enter 7..." << endl;
        cout << "For \"Randomize\" please enter 8..." << endl;
        cout << "For \"Save to file\" please enter 9..." << endl;
        cout << "For \"End\" please enter 10" << endl;
        cout << "For more information please enter 0" << endl;

        cin >> step;

        if (cin.fail())
        {
            errorMessage();
            goto makeMove;
        }

        switch (step)
        {
        case 0:
        {
            cout << endl;
            cout << "For \"Step forward\": \nEnacts a \'step forward\' according to John Conway's rules for \'Game of Life\'." << endl;
            cout << "Each living cell with 2 or 3 living cells adjacent to it, will remain.The rest will \'die\'." << endl;
            cout << "All dead cells with exactly 3 living cells adjacent to them will \'come alive\'." << endl << endl;
            cout << "For \"Resize\": Enlarge or shrink the playing field by giving it new dimensions. " << endl << endl;
            cout << "For \"Toggle cell\": Replace a living cell at coordinates of your choice with a dead one, or vice versa." << endl << endl;
            cout << "For \"Clear\": All cells at the playing field will die." << endl << endl;
            cout << "For \"Randomize\": Each cell will be randomly allocated life or death with a possibility 1 in N for being alive" << endl;
            cout << "Note: The number N - or the life probability quotient - will be provided by you." << endl << endl;
            cout << "For \"Save to file\": save your playing field information in a pre-existing .txt file." << endl << endl;
            cout << "For \"End\": Leave game" << endl << endl;
            break;
        }
        case 4:
        {
            stepForward((unsigned short*)neighboursCount, field, h, w);
            break;
        }
        case 5:
        {
            cout << "PLease input new height: ";
            cin >> newH;
            cout << "PLease input new width: ";
            cin >> newW;

            resizeFieldDownRight(field, h, w, newH, newW);

            break;
        }
        case 6:
        {
            cout << "PLease input coordinate X: ";
            cin >> coordinateX;
            cout << "PLease input coordinate Y: ";
            cin >> coordinateY;

            toggleCell(field, h, w, coordinateX, coordinateY);

            break;
        }
        case 7:
        {
            clearField(field, h, w);
            break;
        }
        case 8:
        {
            cout << "Please enter randomization quotient: " << endl;
            cin >> n;
            randomizeField(field, h, w, n);
            break;
        }
        case 9:
        {
            cout << "Please provide a filename for saving your results." << endl;
            cin >> fileName;
            saveToFile(field, fileName, h, w);
            cout << "Results saved to " << fileName << endl;
            break;
        }
        case 10:
        {
            resizeFieldDownRight(field, h, w, 0, 0);
            goto beginningOfGame;
        }
        default:
        {
            errorMessage();
        }
        }
    }

    return 0;

}
