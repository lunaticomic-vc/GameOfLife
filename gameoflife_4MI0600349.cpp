#include <iostream>
#include<vector> //for utilizing vectors
#include<string> //for utilizing strings
#include<fstream> //for working with files
#include<stdlib.h> //for rand()
#include<iomanip> //for setw()

using namespace std;

vector<vector<bool>> field;

size_t h = 8, w = 16; //field dimensions

size_t newH, newW, coordinateX, coordinateY; //will be used for field manipulation

string fileName, row; //used for file data

unsigned short n; //randomization quotient for randomize field function

//variables used to limit field to smallest sub-field which includes all living elements
size_t minElHeight, minElWidth, maxElHeight, maxElWidth;

//used in game menu selection
unsigned short begin, step = 1;

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

    cout << setw(4) << "1";

    for (int i = 0; i < width - 2; i++)
    {
        cout << " ";
    }

    cout << width << endl;

    for (size_t i = 0; i < height; i++)
    {
        if (i == height - 1 || i == 0) cout << setw(2) << i + 1 << " ";
        else cout << setw(3) << " ";

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

    size_t beginLoopHeight = coordinateX - 1, endLoopHeight = coordinateX + 1;
    size_t beginLoopWidth = coordinateY - 1, endLoopWidth = coordinateY + 1;

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

void widenUp(vector<vector<bool>>& field, size_t& height, size_t& width, int shiftStep)
{
    //At resize, new dimension will be <=0, convert to find out number of rows to add
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
    //At resize, new dimension will be <=0, convert to find out number of cols to add
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

void resizeFieldDown(vector<vector<bool>>& field, size_t& oldHeight, size_t& width, size_t newHeight)
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

        for (size_t i = 0; i < width; i++)
        {
            row.push_back(0);
        }

        for (size_t i = oldHeight; i < newHeight; i++)
        {
            field.push_back(row);
        }
    }

    oldHeight = newHeight;

}

void resizeFieldRight(vector<vector<bool>>& field, size_t& height, size_t& oldWidth, size_t newWidth)
{
    if (oldWidth > newWidth)
    {
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = newWidth; j < oldWidth; j++)
            {
                field[i].pop_back();
            }
        }
    }
    else if (oldWidth < newWidth)
    {
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = oldWidth; j < newWidth; j++)
            {
                field[i].push_back(0);
            }
        }
    }

    oldWidth = newWidth;

}

//Since all cells outside field are dead, field will only have be widened at step in case of three consecutive living cells in field frame
//Apply algorithm for top and bottom expansion
bool doesItWidenUpDown(vector<vector<bool>>& fieldCopy, size_t& height, size_t& width, int row)
{
    unsigned short count = 0;
    for (size_t j = 0; j < width; j++)
    {
        if (fieldCopy[row][j] == 1)count++;
        else count = 0;
        if (count == 3)
        {
            return 1;
        }
    }
    return 0;
}

//Apply same algorithm for left and right expansion
bool doesItWidenLeftRight(vector<vector<bool>>& fieldCopy, size_t& height, size_t& width, int col)
{
    unsigned short count = 0;
    for (size_t i = 0; i < height; i++)
    {
        if (fieldCopy[i][col] == 1)count++;
        else count = 0;
        if (count == 3)
        {
            return 1;
        }
    }
    return 0;
}

//Checks if field will need to be widened for conducting step forward, changes dimensions accordingly
void prepareForStepForward(vector<vector<bool>>& field, size_t& height, size_t& width)
{
    size_t refCol = 0, refRow = 0;

    //Checks if field will have to be widened at the top, first row used for reference
    if (doesItWidenUpDown(field, height, width, refRow))//
    {
        widenUp(field, height, width, 0);
    }

    //Checks if field will have to be widened on the left, first column used for reference
    if (doesItWidenLeftRight(field, height, width, refCol))
    {
        widenLeft(field, height, width, 0);
    }

    refCol = width - 1;
    refRow = height - 1; 

    //Checks if field will have to be widened at the bottom, last row used for reference
    if (doesItWidenUpDown(field, height, width, refRow))
    {
        resizeFieldDown(field, height, width, height + 1);
    }

    //Checks if field will have to be widened on the right, last column used for reference
    if (doesItWidenLeftRight(field, height, width, refCol))
    {
        resizeFieldRight(field, height, width, width + 1);
    }

}

//Conducts forward step according to rules
void stepForward(vector<vector<bool>>& field, size_t& height, size_t& width)
{
    vector<vector<bool>> fieldCopy;

    prepareForStepForward(field, height, width);

    fieldCopy.insert(fieldCopy.end(), field.begin(), field.end());//create a copy of field as a reference for toggling cells

    int neighboursCount;

    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            neighboursCount = countNeighbours(fieldCopy, height, width, i, j);

            if (field[i][j] == 1 && (neighboursCount < 2 || neighboursCount > 3))
            {
                field[i][j] = 0;
            }

            else if (field[i][j] == 0 && neighboursCount == 3)
            {
                field[i][j] = 1;
            }
        }
    }

}

//Find the smallest sub-field where all living cells are included
void checkFieldFrame()
{
    ::minElHeight = ::h;
    ::minElWidth = ::w;
    ::maxElWidth = 0;
    ::maxElHeight = 0;

    for (int i = 0; i < ::h; i++)
    {
        for (int j = 0; j < ::w; j++)
        {
            if (field[i][j] == 1)
            {
                if (i < ::minElHeight)::minElHeight = i;
                if (j < ::minElWidth)::minElWidth = j;
                if (i > ::maxElHeight)::maxElHeight = i;
                if (j > ::maxElWidth)::maxElWidth = j;
            }
        }
    }
}

//Non-positive values allowed in field resize coordinates
void toggleCell(vector<vector<bool>>& field, size_t& height, size_t& width, int coordinateX, int coordinateY)
{
    if (coordinateX <= 0)
    {
        widenUp(field, height, width, coordinateX);
        coordinateX = 1;
    }
    else if (coordinateX > height) resizeFieldDown(field, height, width, coordinateX);

    if (coordinateY <= 0)
    {
        widenLeft(field, height, width, coordinateY);
        coordinateY = 1;
    }
    else if (coordinateY > width) resizeFieldRight(field, height, width, coordinateY);

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

void beginMenu();

void errorMessage()
{
    cout << "Invalid input. Please provide output according to menu rules." << endl;
}

void loadFile(vector<vector<bool>>& field, string nameOfFile, size_t& height, size_t& width)
{
    ifstream inputFile(nameOfFile);

    string row;

    size_t indRow = 0, getWidth = 0;

    if (inputFile.is_open())
    {
        while (getline(inputFile, row))
        {
            field.push_back({});

            getWidth = row.length();

            for (int i = 0; i < getWidth; i++)
            {
                field[indRow].push_back(translateFieldCharToBool(row, i));
            }

            indRow++;
        }
        inputFile.close();

        height = indRow;
        width = getWidth;
    }
    else
    {
        errorMessage();
        beginMenu();
    }

}

void saveToFile(vector<vector<bool>> field, string fileName, size_t height, size_t width)
{
    checkFieldFrame();

    ofstream outFile(fileName);

    if (outFile.is_open())
    {
        for (size_t i = ::minElHeight; i <= ::maxElHeight; i++)
        {
            for (size_t j = ::minElWidth; j <= ::maxElWidth; j++)
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

bool errorCapture()
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        errorMessage();
        return true;
    }
    return false;
}

void gameMenuContents()
{
    cout << "Please choose an option:" << endl;
    cout << "For \"Step forward\" please enter 4..." << endl;
    cout << "For \"Resize\" please enter 5..." << endl;
    cout << "For \"Toggle cell\" please enter 6..." << endl;
    cout << "For \"Clear\" please enter 7..." << endl;
    cout << "For \"Randomize\" please enter 8..." << endl;
    cout << "For \"Save to file\" please enter 9..." << endl;
    cout << "For \"End\" please enter 10" << endl;
    cout << "For more information please enter 11" << endl;
}

void infoMenu()
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
}

void gameMenu();

void beginMenu()
{
    cout << "Welcome to the Game of Life! Please choose an option:" << endl;
    cout << "For \"New game\" please enter 1...\nFor \"Load game\" please enter 2...\nFor \"Exit\" please enter 3..." << endl;
    cin >> ::begin;

    if (errorCapture() == true) beginMenu();

    if (::begin == 1)
    {
        h = 8;
        w = 16;
        initializeField(field);
        gameMenu();
    }

    else if (::begin == 2)
    {
        cout << "Enter filename:\nNote: In case of issue, try providing absolute filepath." << endl;
        cout << "E.g.: C:\\C++\\GameOfLife\\example.txt NOT example.txt!" << endl;
        cin >> fileName;
        loadFile(field, fileName, h, w);
        gameMenu();
    }

    else if (::begin == 3);

    else
    {
        errorMessage();
        beginMenu();
    }
}

void gameMenu()
{
    while (step)
    {
        printField(field, h, w);

    makeMove:

        gameMenuContents();

        cin >> step;

        if (errorCapture() == true) goto makeMove;

        switch (step)
        {
        case 4:
        {
            stepForward(field, h, w);
            break;
        }

        case 5:
        {
            cout << "PLease input new height: ";
            cin >> newH;
            cout << "PLease input new width: ";
            cin >> newW;

            resizeFieldDown(field, h, w, newH);
            resizeFieldRight(field, h, w, newW);
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

        case 7: clearField(field, h, w); break;

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
            //Clear field of any values
            resizeFieldDown(field, h, w, 0);
            resizeFieldRight(field, h, w, 0);

            beginMenu();

            break;
        }

        case 11: infoMenu(); break;

        default:
        {
            errorMessage();
            goto makeMove;

            break;
        }
        }

    }

}

int main()
{
    beginMenu();

    cout << "Thank you for playing. Press enter to close program. Please come again!" << endl;
    std::cin.get();
    return 0;

}
