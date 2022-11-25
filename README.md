# arduino-game-of-life
PMOS + resistor game of life implementation on Arduino UNO 8x8 LED board

## Board

The arduino Uno expects a 8x8 LED input with PMOS transistors connecting to a 5V source and resistors (80 Ohm) connecting to ground. 

The program consumes an 8x8 array representing the starting point for each LED. 0 represents off and 1 represents on. 

e.g.
```
const byte MOCK_GRID[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
};
```

