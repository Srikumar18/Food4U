#ifndef MENU_H
#define MENU_H
typedef struct{
  char restname[30];
  int fcode[15];
  char food_items[15][30];
  float price[15];
  char code[15][10];
  char timecode[15];
}menu;
typedef struct{
  int count;
  int code[10];
  char cartlist[10][50];
  int qty[10];
  char tempr[5][10];
  float total;
}carts;

menu * init_menu();
char *preferences();
carts add(carts cart, char *pref);
carts del(carts cart);
carts customize(carts cart);
void displaycart(carts cart);
carts init_cart(carts cart,menu restc,int fcode[10]);
int time_mod(int start_hour, int start_minute, int end_hour, int end_minute);
carts restcart(carts cart, int choice, char pref[10]);
carts foodcart(carts cart, char pref[10]);
void bill(char uname[], carts cart);
void delquer(int quernum);
extern int branchdist;
int * food_rec(carts cart,int *var);
void calscores(int sizex,int sizey,int *sizez );
void itemsets( int size, int num1,int num2, int *sizey, int *count);
void itemfreq(int size,int choice, int *sizex);
void clear_data(int *size, int choice);
void ret_data(int *numTransactions);
void food_rev(carts cart);
void rest_rev(carts cart);
void rest_que(char uname[],carts cart);
void displayrest();
void restaurantdistance(char location[],int choice, char BranchLocations[][25],int Branchdistances[]);
char* branchselection(char BranchLocations[][25],int * branchdist, int Branchdistances[]);
int driverselection(char branch[]);
int driverlocchange(int index);
extern char R_Locations[30][25];
extern int Branches[10][4];
extern int frec;
extern int freccheck[15];
int churncust(char username[]);
void changechurn(char username[]);
void driver_rev(int drivno);
extern char address[200];
#endif /* MENU_H */