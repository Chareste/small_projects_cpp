#include <iostream>
#include <fstream>
#include "user.hpp"

User::User(string usr, string pwd, int g, int t, int p){
   this->username = usr;
   this->password = pwd;
   this->games = g;
   this->maxTurns = t;
   this->totalPoints = p;
}
User::User(string usr, string pwd){
   this->username = usr;
   this->password = pwd;
   this->games = 0;
   this->maxTurns = 0;
   this->totalPoints = 0;
   create_file();
}


void User::show_stats(){ 
   std::cout << "Showing stats for user " << username << ".\n"
               << "Total games: " << games << "\nLongest match: "
               << maxTurns << " turns\nPoints: " << totalPoints << "\n";
   
}
void User::update_stats(int pts){
   this->games++;
   this->maxTurns = this->maxTurns > pts ? this->maxTurns : pts; 
   this->totalPoints+=pts;
   update_file();
}
int User::update_file(){
   try{
      std::ofstream f((username+".dat").c_str());
      if(!f.good()) throw std::invalid_argument("Bad user file stream\n");
      f << password << std::endl << games << std::endl << maxTurns
        << std::endl << totalPoints << std::endl;


   } catch(std::exception& e){
      std::cerr << "Error while saving user data.\n";
      return -1;
   }
   return 0;

}
void User::create_file(){}


