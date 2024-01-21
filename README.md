As the program is launched, player will be asked to input a number to access three options:
1 for 'New game', where a field full of 'dead' cells is initialized,
2 for 'Load file', where field is read from file; if selected, player will be asked to give the location of the file. 
3 for 'Exit', where if chosen the game ends.

If input is invalid or out of bounds, they will not be permitted to proceed.

The current field will then be displayed.
Another menu is now available. With every choice, made by the player, the field is changed according to what is selected, and displayed again, until the user ends the ongoing iteration of the game.
The options in the menu are as follows:

4 for Step forward, where a 'step' as defined by the task rules is initiated,
5 for Resize, player will then be asked to input the new field dimensions and field will be shortened/widened to fit said dimensions,
5 for Toggle cell, player will then be asked to input cell coordinates and said cell will be replaced with its opposite value (If coordinates are out of bounds, field will be widened to fit)
7 for Clear, field of current dimensions will be transformed to only contain dead cells,
8 for Randomize, field will be randomly allocated new values, player will be asked to enter N, decribed as 'randomization quotient', where each cell will have a 1 in N chance of being alive.
9 for Save to file, player will be asked to provide destination file location, he will then be told whether the operation is successful and the game will continue,
10 for End, field will be erased, player will be taken to the menu from the beginning and they will be able to start a new game,
11 for Information menu, where each option will be described in details.

If input is invalid or out of bounds, they will not be permitted to proceed.

Player is free to enact as many steps as they desire until selecting exit from the menu at the beginning of each iteration of the game.
