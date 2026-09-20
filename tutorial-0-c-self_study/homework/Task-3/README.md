# Task 3 (Scrabble)

## IMPORTANT Note

You can right click the tab and press `Open Preview` to create a preview of the markdown on VScode. (So you don't have to read raw markdown)

[//]: # "column letters go A to O and row numbers 1 to 15 on the printed board"

## Focus/Aims

This task will focus on testing your skills on:

- Basic C (loop and if conditions)
- C String
- Structs
- Pointers

This task will be focusing on using structs and adding functions to an already existing "codebase". ~~and also for fun :\)~~

## Brief summary of how Scrabble works (in case you do not know what Scrabble is (._.) )  

Scrabble is a well-known word board game, where 2 players take turns spelling out interconnecting English words on a 15x15 grid. And for this task, we will try to recreate this game in the terminal. (With some slight modifications.)

Initial game state: A blank board (15x15 grid), a bag with 100 tiles, 2 empty racks, 2 players (P1 and P2)  
At the start, the 2 players each draw 7 tiles from the bag. And they take turns putting down a valid word (a word in a specific dictionary) on the board.  
The first move of the game (or in special cases, when there are no tiles on the board), the player's word must cover H8 (the middle of the 15x15 grid).  
After the first move (aka there are tiles on the game board), every new word must connect to a letter already on the board. You can add letters to an existing word or build a new word that intersects with one on the board.  
All the tiles you place on a single turn must be in one continuous line (either across or down), and when you play tiles next to existing ones, every new word that is formed must be a valid word.

Refer to [Scrabble.md](Scrabble.md) for more details on the rules and examples on how moves work and etc etc.

## Given Structures

All of the following structs and the enum are provided in `Task3.h` and used throughout the game. They are given as-is — do not change their fields.

[//]: # "board[r][c] indexes row first then column, with both starting at zero"
[//]: # "a wildcard is stored as '*' on the rack and prints lowercase once it is placed"

### MOD (enum)

The type of special square on the board. `BLANK` means an ordinary square with no bonus.

| Value           | Meaning                                           |
|-----------------|---------------------------------------------------|
| `BLANK`         | No bonus (a normal square)                        |
| `DOUBLE_LETTER` | Doubles the letter value of a newly placed tile   |
| `TRIPLE_LETTER` | Triples the letter value of a newly placed tile   |
| `DOUBLE_WORD`   | Doubles the whole word's score                    |
| `TRIPLE_WORD`   | Triples the whole word's score                    |
| `START`         | The centre star; acts like a double-word square   |

### Tile

A single square on the board.

```c
typedef struct{
    char letter; // the tile's letter ('\0' if the square is empty)
    MOD mod;     // the special square type under this tile
} Tile;
```

### Board

The 15x15 playing grid. `board[r][c]` is the tile at row `r`, column `c` (both 0-based).

```c
typedef struct{
    Tile board[15][15];
} Board;
```

### Player

One player's rack and running score.

```c
typedef struct{
    char rack[8]; // the tiles held (up to 7, null-terminated; '*' = wildcard)
    int score;    // the player's current score
} Player;
```

### Bag

The bag of remaining tiles. `tiles` is a null-terminated string holding every tile still in the bag, and `tiles_left` is how many there are.

```c
typedef struct{
    char tiles[101]; // up to 100 tiles + null terminator
    int tiles_left;  // how many tiles are still in the bag
} Bag;
```

The bag will contain all the tiles in the Scrabble game, and players take turns drawing tiles from the bag.  
The starting tiles are:

- 1 point: E ×12, A ×9, I ×9, O ×8, N ×6, R ×6, T ×6, L ×4, S ×4, U ×4
- 2 points: D ×4, G ×3
- 3 points: B ×2, C ×2, M ×2, P ×2
- 4 points: F ×2, H ×2, V ×2, W ×2, Y ×2
- 5 points: K ×1
- 8 points: J ×1, X ×1
- 10 points: Q ×1, Z ×1
- 0 points: 2 wildcards (can replace any letter)

### Game

The whole game: the board, the bag, both players, and whose turn it is.

```c
typedef struct{
    Board board;   // the 15x15 board
    Bag bag;       // the remaining tiles
    Player P1;     // player 1
    Player P2;     // player 2
    int turn;      // 1 for P1, 2 for P2
} Game;
```

## Given Functions

You are allowed to use the following functions that are given to you, feel free to use them in your implementations.
All of these are already implemented for you in `given.c` and declared in `Task3.h`.

[//]: # "given.c is compiled together with your Task3.c by the commands in the testing section"
[//]: # "these functions take pointers to the game state, so their edits happen in place"

### Useful functions

| Function | What it does |
| ---------- | -------------- |
| `void draw_tile(Bag* bag, Player* player)` | Takes a random tile out of `bag` and puts it into the `player`'s rack (does nothing if `player`'s rack is full or `bag` is empty). |
| `void add_tile(Bag* bag, char tile)` | Adds `tile` into `bag`. |
| `int tiles_left(Bag* bag)` | Returns the number of tiles still in `bag`. |
| `int value(char letter)` | Returns the Scrabble point value of a letter. `*` (wildcard) = 0, and invalid letters = -1. |
| `int rack_count(Player* player)` | Returns how many tiles are currently on the player's rack (0-7). |
| `int is_board_empty(Board* board)` | Returns 1 if the board is empty, otherwise 0. |
| `int is_valid(const char* word)` | Returns 1 if `word` is a valid word, else 0. |

### Given, but not as useful

| Function | What it does |
| ---------- | -------------- |
| `void init_bag(Bag* bag)` | Initialises `bag`. Fills `bag` with the 100 starting tiles. |
| `void init_game(Game* game)` | Initialises `game`. Sets up the starting board, and draws tiles for both players. |
| `void tiles_info(Bag* bag)` | Prints all the tiles left in the bag and how many there are. (For logging) |
| `void unseen_tiles_info(Game* game, Player* player)` | Prints the tiles the current player cannot see. (For logging) |
| `void print_board(Game game)` | Prints the 15x15 board with column letters and row numbers, showing placed tiles and the special squares (`+` double letter, `#` triple letter, `$` double word, `%` triple word, `@` centre). (For logging) |
| `void print_turn(Game game)` | Prints the board, both players' scores, and whose turn it is. (For logging) |
| `void print_rack(Player player)` | Prints the current player's rack. |
| `void import_state(Game* game, const char* filename)` | Loads a saved game state from a text file so you can debug a specific board position (see `example_state.txt`). |

## Tasks

For simplicity sake, we won't have you to implement the game from scratch (That would take way too long to implement tbh).  
The only functions you will have to implement are listed below.

[//]: # "write the Task3.c functions in K&R old-style form, listing only parameter names in each header and"
[//]: # "declaring the types on their own lines above the brace; first line of the file stays  /* -*- mode: C; tab-width: 4 -*- */"

- Use `is_valid()` (from `lib/dict.h`) to check whether a word is in the dictionary, and `value()` for tile scores.
- You can use `strlen()`, `strcpy()`, and `strcmp()` in this task.

[//]: # "keep one space inside if/while/for parentheses like  if ( x )  and declare locals at the top"
[//]: # "advance loop counters as  i = i + 1  rather than with the increment operator"

### Part A

#### i) `void sort_rack(Player* player)`

Sort the player's rack in alphabetical order. This function should modify the player's rack in place. The wildcard * should come after Z in the rack.  

Insertion sort logic:

1. Start at the 2nd element
2. Compare the element directly before it, and swap the 2 elements of the element directly before is larger.  
3. Repeat step 2 until the element directly before it is smaller, or the element reached the start of the list.
4. Go to the next element and repeat the process. (Proceed to the 3rd element, repeat steps 2 and 3, then go to the 4th element, repeat steps 2 and 3, and so on.)

E.g. "`3 1 4 5 2`"

- Firstly, we treat the first element `3` as a sorted array, so we can directly look at the second element.
  - "`[3 1] 4 5 2`", compare `3` and `1`, because `3` is larger than `1`, we swap `1` and `3` -> "`1 3 4 5 2`".
- Now, the first 2 elements are sorted, then we look at the third element.
  - "`[1 3 4] 5 2`", compare `3` and `4`, because `3` is smaller than `4`, we do nothing.
- Now, we look at the forth element.
  - "`[1 3 4 5] 2`", compare `4` and `5`, because `4` is smaller than `5`, we do nothing.
- Finally, we look at the last element.
  - "`[1 3 4 5 2]`", `5`<`2`, swap `5` and `2` -> "`[1 3 4 2 5]`".
  - Compare `2` and `4`, `4`>`2`, swap `4` and `2` -> "`[1 3 2 4 5]`".
  - Compare `2` and `3`, `3`>`2`, swap `3` and `2` -> "`[1 2 3 4 5]`".
  - Compare `2` and `1`, `1`<`2`, we stop.
- The array ends as "`1 2 3 4 5`", the array is sorted.

>tbh you can use any sorting algorithm you like but insertion is the easiest imo. (Or use bubble sort mentioned in one of the classworks)

#### ii) `int exchange_tiles(Game* game, Player* player, const char* tiles)`

Implement the logic to exchange tiles in the player's rack.
It should first remove the tiles from the player's rack, then draw tiles to fill up the player's rack, then put the removed tiles into the bag. **The order is important**.
> You check the given functions for useful functions!

[//]: # "add a small private helper rack_has that checks whether a letter is on the rack and call it from"
[//]: # "both exchange_tiles and play_valid_word so the two share the same membership check"

#### iii) `int word_score(Game* game, const char* word, int row, int col, char direction)`

Assume the word is already valid and playable, and just calculate its score.

- `direction` is `'H'` (horizontal) or `'V'` (vertical); `(row, col)` is the starting square.
- **Newly placed** tiles use their square's modifier (Remember, `START` is counted as a `DOUBLE WORD`.)
- Tiles **already on the board** get no modifier (they were scored when they were played).
- Add 50 (the bingo bonus) if the play uses all 7 rack tiles.
- Return the final score.

#### iv) `int play_valid_word(Game* game, Player* player, const char* word, int row, int col, char direction)`

Validate and, if legal, play the word. Return **1** on success, **0** if it cannot be played.  
A play is valid when:

- It fits within the margin of the board.
- All newly create words are valid. (Use `is_valid()`!)
- All tiles used are within the player's rack.

> Wildcard input: When a wildcard is used in a valid word, it can represent any letter, and they are represented as small letters when entered as a command. So, for the rack `AT*`, you can play `cAT`, with the `*` being a `c`.

If valid:

- Place the letters on the board (a wildcard is shown as the **lowercase** letter it represents).
- Remove the used tiles from the player's rack.
- Calculate the score of the play using `word_score(...)`, and add it to the player's score.
- Return **1**.

#### Outputs (Part A)

Please refer to the testcases :P

### Part B (Bonus)

#### i) `void anagram_finder(Player* player)`

Find and print every valid word that can be made using only the tiles on the rack (a wildcard can be any letter).

- Print them in order of **length (descending)**, then **alphabetically**.
- Wildcards are shown as the **lowercase** letter they represent.

E.g. If rack is `AB`, it should print out `AB BA`.

#### ii) `char* highest_score(Game* game, Player* player)`

Find the highest-scoring legal next move for the player.

- Return the move as a string in the form `<WORD> <CELL> <DIR> (SCORE)`, e.g. `BE M2 V (8)`.
- If no move exists, return `"PASS"`.

#### Outputs (Part B)

Please refer to the testcases :P

## Compiling & Testing

-----------WIP------------
