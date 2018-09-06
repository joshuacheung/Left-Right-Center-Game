# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

int money[] = {3,3,3,3,3,3,3,3,3,3};
bool checkIfWon();
bool hasMoney();
void passMoney();
void winner();
int centerMoney = 0;

typedef enum faciem {LEFT , RIGHT , CENTER , PASS } faces ;
faces die [] = {LEFT , RIGHT , CENTER , PASS , PASS , PASS };


const char *names[] = {"Whoopi", "Dale", "Rosie", "Jimmie", "Barbara", "Kyle", "Raven", "Tony", "Jenny", "Clint"};

int main(void){

   bool gameOver = false;
   unsigned int seed;
   int randomNumber;
   int numPlayers;

   printf("Random seed: ");
   scanf("%u", &seed);
   srand(seed);

   printf("How many players? ");
   scanf("%d", &numPlayers);

   int player  = 0; //keep track of whose turn it is
   int temp = 0;
   while(gameOver == false){
      if(checkIfWon(numPlayers) == true){
          winner(numPlayers);
          break;
      }
      if(player == numPlayers){ //if it is the last person's turn, go to first
         player = 0;
      }
      if(hasMoney(player) == true){
         printf("%s rolls... ",names[player]);
         temp  = money[player];
         if (temp > 3){temp =3; }
         for(int i = 0; i < temp; i++){ //runs depending on how much money player has
            randomNumber = rand()%6;
            passMoney(randomNumber, player, numPlayers);
         }
         printf("\n");
      }
      player++;


   }
   return 0;

}

/*this function is called to determine who exactly is the winner*/
void winner(int numPlayers){
    for(int i = 0; i < numPlayers; i++){
        if(money[i] != 0){
            printf("%s wins the $%d pot with $%d left in the bank!", names[i], centerMoney, money[i]);
        }
    }
    printf("\n");

}

/*this function checks if more than one person has money. If this is so then the game will continue playing. */
bool checkIfWon(int numPlayers){
  int playersWMoney = 0;
  for(int i = 0; i < numPlayers; i++){
     if(money[i] > 0){
        playersWMoney++;
     }
  }
  if(playersWMoney ==  1){
      return true;
  }else{
      return false;
  }
}

/*this function will check to see if the current player has any money*/
bool hasMoney(int position ){
   if(money[position] > 0){
      return true;
   }
   return false;
}

/* This function uses the pseudo random number to determine where the money goes*/
void passMoney(int rand, int pos, int numPlayers){

  switch(rand){
    case 0:
      if(pos == 0){
        money[numPlayers-1]++;
        money[pos]--;
        printf("gives $1 to %s ", names[numPlayers-1]);
      }else{
        money[pos-1]++;
        money[pos]--;
        printf("gives $1 to %s ", names[pos-1]);
      }
    break;

    case 1:
      if(pos == numPlayers-1){
          money[0]++;
          money[pos]--;
          printf("gives $1 to %s ", names[0]);
      }else{
          money[pos+1]++;
          money[pos]--;
          printf("gives $1 to %s ", names[pos+1]);
      }
    break;

    case 2:
      centerMoney++;
      money[pos]--;
      printf("puts $1 in the pot ");
    break;

    default:
      printf("gets a pass ");
      break;
  }

}
