#include <iostream>
using namespace std;

bool field[80][24];

void initializeClearField(bool** field, size_t height, size_t width)
{
    for (size_t i = 0; i < n; i++) 
    {
        for (size_t j = 0; j < m; j++) 
        {
            field[i][j] = false;
        }
    }
}

int countNeighbours(bool** field, size_t height, size_t width, int coordinateX, int coordinateY)
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

void printField(bool** field, size_t width, size_t height)
{
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if (field[i][j] == true)cout << "@";
            else cout << "-";
        }
        cout << endl;
    }
}


void widenUp(bool** field, size_t height, size_t width, int shiftStep)
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

void widenLeft(bool** field, size_t &height, size_t &width, int shiftStep)
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

void stepForward(bool** field, size_t height, size_t width)
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

void resizeField(bool** field, size_t &oldHeight, size_t &oldWidth, size_t newHeight, size_t newWidth)
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

void toggleCell(bool** field, size_t &height, size_t &width, int coordinateX, int coordinateY)
{
    if (coordinateX <= 0)widenUp(field, height, width, coordinateX);
    else if (coordinateX >= height) height = coordinateX;

    if (coordinateY <= 0)widenLeft(field, height, width, coordinateY);
    else if (coordinateY >= width) width - coordinateY;

    field[coordinateX][coordinateY] = !(field[coordinateX][coordinateY]);
}

void saveToFile(bool** field)
{

}

void loadFile(bool** field)
{

}

int main()
{
    int begin;
    cout << "Welcome to the Game of Life! Please choose an option:" << endl;
    cout << "For \"New game\" please enter 1...\nFor \"Load game\" please enter 2...\nFor \"Exit\" please enter 3..." << endl;

    
}
