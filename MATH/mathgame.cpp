#include <iostream>
#include <fstream>
#include <stdexcept>

#include "game_functions.hpp"
#include "user.hpp"


using std::string; 

int tryLogin(string& usr, string& pwd);
bool logout(User& usr);
bool check_range(int& chc, int a, int b);
User login(string usr);
void createUser(string& usr, string& pwd);

int main(){
   
   int chc = 0, log;

   for(;;){ //login or register
      std::cout << "Choose Register (1), Login (2) or Quit (3).\n" << "> ";
      
      if (!check_range(chc, 1,3)) continue;
      string user, pwd;

      switch(chc){ 
         case 1: //register
            if (tryLogin(user, pwd)!= -1) 
               std::cerr << "Username already exists. Login?\n";
            
            else{// create new user
               createUser(user, pwd);
               //create user
               std::cout << "User created successfully. Please login now.\n";
            }
            break;
         case 2: //login //somehow non funzioona
            log = tryLogin(user, pwd);
            if (log == -1) // User does not exist
               std::cerr << "Username does not exist, register?\n";  
            else if (log == 1) // Wrong password
               std::cerr << "Wrong password, please try again.\n";
            else{ // login accepted
               //load user info
               User usr = login(user);

               for(;;){ // main menu game loop
                  std::cout << "Welcome to " << GAME_NAME << "! What would you like to do?\n"
                           << "1. New game\n" << "2. See stats\n" << "3. Logout\n" << "> ";

                  if (!check_range(chc, 1,3)) continue;
                  if(chc==1){ //perché si rompe?
                     int pts = game();
                     usr.update_stats(pts);
                    }
                   else if(chc==2){ // see stats
                     usr.show_stats();
                   }
                    else{ // quit
                        if(logout(usr)) break; //handle user data!
                  } 
                  std::cin.clear();
               } // main menu for end
            } // login else end
            break;
         case 3: 
            std::cout << "Quitting game...";
            return 0;
      }// signin switch end
   } // signin for end
} // main end

int tryLogin(string& usr, string& pwd){
   string testpw;

   std::cout << "Insert username.\n" << "> ";
   std::cin >> usr; 
   std::cout << "Insert password.\n" << "> ";
   std::cin >> pwd;

   std::ifstream u((usr+".dat").c_str());
   
   if(u.good()){ 
      std::getline(u,testpw);
      if (!testpw.compare(pwd)){ //login accepted
         return 0;
      }
      else{
         return 1; 
      }
   }
   else{ // user does not exist
   return -1; 
   }
}

bool logout(User& usr){

   std::cout << "Are sure you want to logout? [Y/N]\n" << "> ";
   char quit;
   std::cin >> quit;
   quit = toupper(quit);

   if(std::cin.fail() || !(quit == 'Y' || quit == 'N')){
      std::cerr << "Only Y/N accepted, returning to main menu.\n";
      std::cin.clear();
      return false;
   }
   else if(quit == 'N'){
      std::cout << "Understood. Returning to main menu.\n";
      return false;
   }
   else{ //yes
      if(usr.update_file() == -1){
         std::cout << "Error saving user data. If you logout now you might lose some data.\n"
                   << "Do it anyway? [Y/any]\n" << "> ";
         std::cin >> quit;
         quit = toupper(quit);
         if(std::cin.fail() || !(quit == 'Y')){
            std::cerr << "Returning to main menu.\n";
            std::cin.clear();
            return false;
         }   
      }
      std::cout << " See you next time!\n";
      return true;
   
   }

}

bool check_range(int& chc, int a, int b){ 
   std::cin >> chc;
   if(std::cin.fail() || (chc < a || chc > b)){
         std::cerr << "Select an option.\n";
         std::cin.clear();
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
         return false;
      }
   return true;
}

/**
 * User File structure
 * Row 1: Password
 * Row 2: games
 * Row 3: maxTurns
 * Row 4: totalPoints
 */
User login(string usr){
   string line, pwd;
   int g,t,p;
   try{
      std::ifstream u((usr+".dat").c_str()); 
      if(!u.good()) throw std::invalid_argument("Bad user file stream\n"); 
      
      std::getline(u, pwd);
      
      getline(u, line);
      g=std::stoi(line);

      getline(u, line);
      t=std::stoi(line);

      getline(u, line);
      p=std::stoi(line);
   }
   catch(std::exception& e){
      std::cerr << "Error while retrieving user data\n";
      std::exit(-1);
   }

   User user(usr,pwd,g,t,p);
   return user;
}

void createUser(string& usr, string& pwd){
   std::ofstream f((usr+".dat").c_str());
   f << pwd << "\n0\n0\n0" << std::endl; 
}




