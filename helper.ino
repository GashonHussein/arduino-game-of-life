int isCellOn(Node *cell){
  const bool isOn = cell->wasOn;
  return isOn ? 1 : 0;
}

int countAliveNeighbors(Node *cell){
  int count = 0;

  for(byte i = 0; i < 8; i++){
    count += isCellOn(cell->neighbors[i]);
  }

  return count;
}

Node* initializeNeighbors(Node *n, int col, int row){

  // get the top node
  if(row > 0){
    n->neighbors[0] = &nodes[row - 1][col];

    //top left
    if(col > 0){
      n->neighbors[4] = &nodes[row - 1][col - 1];
    }

    // top right
    if(col < 7){
      n->neighbors[5] = &nodes[row - 1][col + 1];
    }
  }
  
  // get bottom node
  if(row < 7){
    n->neighbors[1] = &nodes[row + 1][col];

    // bottom left
    if(col > 0){
      n->neighbors[6] = &nodes[row + 1][col - 1];      
    }
    // bottom right
    if(col < 7){
        n->neighbors[7] = &nodes[row + 1][col + 1];
    }
  }
  
  // get left node
  if(col > 0){
    n->neighbors[2] = &nodes[row][col - 1];
  }

  // get right node
   if(col < 7){
    n->neighbors[3] = &nodes[row][col + 1];;
   }

   return n;
}

void updateLED(Node *node){
  Node n = *node;

  if(!n.isOn) return;

  digitalWrite(n.anode, LOW);
  digitalWrite(n.cathode, LOW);

  delayMicroseconds(50);
  
  digitalWrite(n.anode, HIGH);
  digitalWrite(n.cathode, HIGH);
}
