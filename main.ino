
struct Node {
  bool wasOn;
  bool isOn;
  int row;
  int col;
  byte anode;
  byte cathode;
  Node *neighbors[8];
};

//[row][col]
const Node nodes[8][8] = {};

void setup(){
  Serial.begin(115200);
  Serial.setTimeout(100);

  const byte ANODE_PINS[8] = {13, 12, 11, 10, 9, 8, 7, 6}; // rows
  const byte CATHODE_PINS[8] = {A3, A2, A1, A0, 5, 4, 3, 2}; // cols

  // turn all nodes off
  for (byte i = 0; i < 8; i++){
    pinMode(ANODE_PINS[i], OUTPUT);
    pinMode(CATHODE_PINS[i], OUTPUT);
    
    digitalWrite(ANODE_PINS[i], HIGH);
    digitalWrite(CATHODE_PINS[i], HIGH);
  }
  
  setupBoard();
}

void setupBoard(){
  const byte ANODE_PINS[8] = {13, 12, 11, 10, 9, 8, 7, 6}; // rows
  const byte CATHODE_PINS[8] = {A3, A2, A1, A0, 5, 4, 3, 2}; // cols
  
  // create all of the nodes in the matrix
  for (byte row = 0; row < 8; row++){
    for(byte col = 0; col < 8; col++){
      bool isOn = MOCK_GRID[row][col] == 1;
      
      Node newNode = {isOn, isOn, row, col, ANODE_PINS[row], CATHODE_PINS[col]};
      nodes[row][col] = newNode;
    }
  }

  // Connect each pin with its neighbors
  for (byte row = 0; row < 8; row++){
    for(byte col = 0; col < 8; col++){
      initializeNeighbors(&nodes[row][col], col, row);
    }
  }
}

void loop(){

    for (byte row = 0; row < 8; row++){
      for(byte col = 0; col < 8; col++){
          Node *cell = &nodes[row][col];
          const int numNeighbors = countAliveNeighbors(cell);
          
          if(numNeighbors > 0) Serial.println(numNeighbors);
          
          if(cell->wasOn){
              // cell dies from underpopulation or overpopulation
              if(numNeighbors == 3 || numNeighbors == 2){
                cell->isOn = true;
              }
          } else {
            if(numNeighbors == 3){
              cell->isOn = true;
            }
          }
      }
    } 
  
    // rerender
    for(byte nRenders = 0; nRenders < 200; nRenders++){
      delayMicroseconds(2500);
      for (byte row = 0; row < 8; row++){
        for(byte col = 0; col < 8; col++){
          updateLED(&nodes[row][col]);
        }
      }
    }
  
    byte totalOn = 0;
    // clean, moving isOn --> wasOn + setting all isOn = false
      for (byte row = 0; row < 8; row++){
        for(byte col = 0; col < 8; col++){
            Node *cell = &nodes[row][col];
            if(cell->isOn){
              cell->wasOn = true;
              totalOn += 1;
            } else{
              cell->wasOn = false;
            }
            cell->isOn = false;
        }
      }

      // end game
      if(totalOn == 0) return;
}