#include <iostream>
#include "game_functions.hpp"
#include "user.hpp"

#define MAX_NR 1000
#define MAX_MULT 1000

int game(){
   srand((unsigned)time(NULL));

   int t = 1;
   int l = LIVES;
   int curr;

   std::cout << "A new game of "<< GAME_NAME << " has begun! \n";

   while(l > 0){
      std::cout<< "\nTurn " << t << "! You got " << l << " lives left.\n";
      curr = turn();
      if(!curr){
         l--;
         continue;
      }
      else t++;
   }
   std::cout << "Game ended! It lasted " << t << " turns.\n";
   return t;
}

int turn(){

   int res = operation();
   int guess;
   int t = TRIES;
   for(;;){ //inserire quit?
      std::cout << "> ";
      std::cin >> guess;
      if(std::cin.fail()){
         std::cerr << "You didn't put an integer, try again!\n";
         std::cin.clear();
         continue;
      }
      else if(guess != res){
         t--;
         std::cout << "Wrong answer! ";
         if (t>0){
            std::cout << "Tries left for this turn: " << t << ".\n";
            continue;
         }
         else{
            std::cout << "No more tries left. You lost one life :( \n"
                      << "The result was: " << res << ".\n";
            return 0;
         }
      }
      else{ //correct answer
         std::cout << "Answer is correct!\nThe result was " << res << ".\n";
         return 1;
      }
   }

}

int operation(){

   

   int a = rand() % MAX_NR;
   int b = rand() % MAX_NR;
   int op = rand() % 4;

   switch(op){
      case 0: //+
         std::cout << a << " + " << b << " = ?\n";
         return a + b;
      case 1: // -
         std::cout << a << " - " << b << " = ?\n";
         return a - b;
      case 2: // *
         a = a % MAX_MULT; // troppo grandi
         b = b % MAX_MULT;
         std::cout << a << " * " << b << " = ?\n";
         return a * b;
      case 3: // /
         
         for(;;){
            if (a % b == 0){
               std::cout << a << " / " << b << " = ?\n";
               return a / b;
            }
            a = rand() % MAX_NR; 
            b = rand() % MAX_NR;
         }
      default:
         std::cerr << "unreachable" << std::endl;
         exit(-1);
   }

}