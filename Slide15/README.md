## Slide 15 Game in C

### Overview
This C program implements the "Slide 15" puzzle, where players arrange shuffled tiles into numerical order by sliding them into an empty space.

### Key Features
- **Tile Movement**: Enables tiles to move up, down, left, and right.
- **Shuffling**: Randomly shuffles tiles at game start.
- **Game Status**: Checks and displays if the game is solved.

### Functions
- `get_command()`: Translates user input into game commands.
- `board_new()`: Initializes a new game board.
- `perform_move()`: Executes tile movements based on commands.
- `show_board()`: Displays the board's state.
- `solved()`: Determines if the game is in a solved state.

### Execution
- Start with `./slide15`. Use commands to move tiles and solve the puzzle.
