using std::string;

class User{
   string username;
   string password;
   unsigned int games;
   unsigned int maxTurns;
   unsigned long totalPoints;

   public:
   User(string usr, string pwd, int g, int t, int p);
   User(string usr, string pwd);

   void show_stats();
   void update_stats(int pts);
   int update_file();
};
