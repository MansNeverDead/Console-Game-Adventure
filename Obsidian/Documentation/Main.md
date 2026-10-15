Here is where everything will be initialized.

First is makes the player instance called User thanks to [[Struct Entity]].

Secondly it makes the map thanks to [[Void Make Map]].

Thirdly it shows the map to the console thanks to [[Void Visualise Map]].

Afterwards it creates 4 temporary variables which will be explained later, those being:

- addX: Int
- addY: Int
- TempMouvX: Int
- TempMouvY: Int

Now that it has initialized everything, the game can commence.

Here the functions creates a **while** loop with true as it's parameter (good luck leaving >:)) ).

Ties up addX, addY as a tupple for the player input thanks to [[Tuple Int, Int. Player Input]].
Of which the sum of addX and the User's X current position will be stored in TempMouvX,
same thing with Y but with Y.

It'll then check if the player is allowed to move to that square using [[Bool Can Move]].

If it can move to that Square, the User's X and Y coordinates will be updated to the current TempMouvX and Y.

If not the User won't be updated.

it'll then again Visualise the map once more before looping back.