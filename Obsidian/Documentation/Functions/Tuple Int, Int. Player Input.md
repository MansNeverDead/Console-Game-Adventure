Here is where the player can interact with the game.

After verifying that it isn't an invalid input such as a number or other types thanks to [[Int Verify Input]], it'll check if it is:

- Z
- Q
- S
- D

depending on that, it will increment or decrement the "velocity" of the player thus it's mouvement.

it returns a **tuple** of X and Y.

It is called inside of [[Main]]

(Author's Note):
The reason i chose for it to return a Tuple is because else if it were a simple int, we wouldn't know it is for X or for Y, and to solve this problem i just chose a tuple.