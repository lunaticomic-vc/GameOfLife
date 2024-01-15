#include <iostream>
using namespace std;

const int HEIGHT = 24, WIDTH = 80;

bool field[HEIGHT][WIDTH];

void initializeClearField(bool field[][80], size_t height, size_t width)
{
    for (size_t i = 0; i < height; i++) 
    {
        for (size_t j = 0; j < width; j++) 
        {
            field[i][j] = 0;
        }
    }
}

int countNeighbours(bool (*field)[80], size_t height, size_t width, int coordinateX, int coordinateY)
{
    int countN = 0;
    for (int i = coordinateX - 1; i <= coordinateX + 1; i++)
    {
        if (i >= 0 && i < height)
        {
            for (int j = coordinateY - 1; j <= coordinateY + 1; j++)
            {
                if(j>=0 && j<width && field[i][j] == true)countN++;
            }
        }
    }
    return countN;
}

void printField(bool field[][80], size_t height, size_t width)
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


void widenUp(bool(*field)[80], size_t height, size_t width, int shiftStep)
{
    shiftStep = shiftStep * (-1);
    height += shiftStep+1;
    for (size_t i = height-1; i > shiftStep; i--)
    {
        for (size_t j = width-1; j>=0; j--)
        {
            field[i][j] = field[i-1][j];
        }
    }
}

void widenLeft(bool(*field)[80], size_t &height, size_t &width, int shiftStep)
{
    shiftStep = shiftStep * (-1);
    width += shiftStep + 1;
    for (size_t i = height-1; i >= 0; i--)
    {
        for (size_t j = width-1; j > shiftStep; j--)
        {
            field[i][j] = field[i][j-1];
        }
    }

}

void stepForward(bool(*field)[80], size_t height, size_t width)
{
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if (field[i][j]==1 && (countNeighbours(field, height, width, i, j) < 2 || countNeighbours(field, height, width, i, j) > 3))
            {
                field[i][j] = 0;
            }
            else if (field[i][j] == 0 && countNeighbours(field, height, width, i, j) == 3)
            {
                field[i][j] = 1;
            }
            
        }
    }
}

void resizeField(bool(*field)[80], size_t &oldHeight, size_t &oldWidth, size_t newHeight, size_t newWidth)
{
    if (oldHeight > newHeight)
    {
        for (size_t i = newHeight; i < oldHeight; i++)
        {
            for (size_t j = 0; j < newWidth; j++)
            {
                field[i][j] = 0;
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
                field[i][j] = 0;
            }
        }
    }
    oldWidth = newWidth;
}

void toggleCell(bool field[][80], size_t &height, size_t &width, int coordinateX, int coordinateY)
{
    if (coordinateX <= 0)widenUp(field, height, width, coordinateX);
    else if (coordinateX >= height) height = coordinateX;

    if (coordinateY <= 0)widenLeft(field, height, width, coordinateY);
    else if (coordinateY >= width) width = coordinateY;

    if (field[coordinateX][coordinateY] == true) field[coordinateX][coordinateY] = false;
    else field[coordinateX][coordinateY] = true;

    cout << field[coordinateX][coordinateY] << endl;
}

void saveToFile(bool** field)
{

}

void loadFile(bool** field)
{

}

void readMatrix(bool(*field[80]))
{

}

void readMenuCommand(int n)
{

}

int main()
{
    int begin, step = 0;
    size_t h, w, newH, newW, coordinateX, coordinateY;
    cout << "Welcome to the Game of Life! Please choose an option:" << endl;
    cout << "For \"New game\" please enter 1...\nFor \"Load game\" please enter 2...\nFor \"Exit\" please enter 3..." << endl;
    cin >> begin;
    if (begin == 1)
    {
        h = 8;
        w = 16;
        initializeClearField(field, h, w);
    }
    else if (begin == 2)
    {

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
        case 4: stepForward(field, h, w); break;
        case 5: 
        {
            cout << "PLease input new height: ";
            cin >> newH;
            cout << "PLease input new width";
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
            initializeClearField(field, h, w);
        } break;
        case 8:; break;
        case 9:; break;
        }
    }

}
