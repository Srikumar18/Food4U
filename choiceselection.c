#include "menu.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//time module for sorting tiffin,meals,etc
int time_mod(int start_hour, int start_minute, int end_hour, int end_minute) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    int current_hour = local->tm_hour;
    int current_minute = local->tm_min;
    if (start_hour < end_hour || (start_hour == end_hour && start_minute < end_minute)) {
        if ((current_hour > start_hour || (current_hour == start_hour && current_minute >= start_minute)) &&
            (current_hour < end_hour || (current_hour == end_hour && current_minute <= end_minute))) {
            return 1;
        }
    } else {
        if ((current_hour > start_hour || (current_hour == start_hour && current_minute >= start_minute)) ||
            (current_hour < end_hour || (current_hour == end_hour && current_minute <= end_minute))) {
            return 1;
        }
    }
    return 0;
}
//sorting food items based on frequency
void bubblesort(int len, int foodfreq[]) {
  for (int i = 1; i < len - 1; i += 2) {
    for (int j = 1; j < len - i - 3; j += 2) {
      if (foodfreq[j] < foodfreq[j + 2]) {
        int tempf = foodfreq[j - 1];
        int tempc = foodfreq[j];
        foodfreq[j - 1] = foodfreq[j + 1];
        foodfreq[j] = foodfreq[j + 2];
        foodfreq[j + 1] = tempf;
        foodfreq[j + 2] = tempc;
      }
    }
  }
}
//sorting scores
int * scores(char *filename){
  int count;
  int *arr1 = (int*)malloc(10 * sizeof(int));
  float arr2[10];
  FILE *fp = fopen(filename, "r");
  int temp;
  for (int i=0; i<10; i++){
    fscanf(fp, "%d %f %d", &arr1[i], &arr2[i],&temp);
  }
  fclose(fp);
  for (int i=0; i<9; i++){
    for (int j=0; j<9-i; j++){
      if (arr2[j]<arr2[j+1]){
        int tempc=arr1[j];
        float tempf=arr2[j];
        arr1[j]=arr1[j+1];
        arr2[j]=arr2[j+1];
        arr1[j+1]=tempc;
        arr2[j+1]=tempf;
      }
    }
  }
  return arr1;
}
//display top 10 restaurant
void displayrest(){
  menu* rest=init_menu();
  char filename[20];
  strcpy(filename,"review_rest.txt");
  int *codes=scores(filename);
  for (int i=0; i<10; i++){
    int n=codes[i];
    printf("%2d.\t\t %-25s - %2d\n",i+1, rest[n-1].restname, rest[n-1].fcode[0]/100);
  }
}
//getting user preferences
char *preferences() {
  char *pref = (char *)malloc(100 * sizeof(char));
  char allergy[10];
  while (getchar() != '\n');
  while (1) {
    printf("\nAllergen details:\n* N - Nuts allergy\n* L - Lactose intolerance\n* S - Seafood allergy\n");
    printf("Enter you allergy preferences (separated by spaces):");
    fgets(allergy, sizeof(allergy), stdin);  
    int flagallergy = 0;
    for (int v = 0; allergy[v] != '\0'; v += 2) {
      allergy[v] = toupper(allergy[v]);
      if (allergy[v] == 'L' || allergy[v] == 'N' || allergy[v] == 'S' || allergy[v] == '\n')
        continue;
      else {
        printf("Enter a valid choice.\n");
        flagallergy = 1;
        break;
      }
    }
    if (flagallergy == 1)
      continue;
  while (1) {
    printf("Enter your mode of cuisine: [V-Veg or X-Non-Veg]:");
    scanf("%s", pref);
    for (int v = 0; pref[v] != '\0'; v++)
      pref[v] = toupper(pref[v]);
    if (pref[0] != 'V' && pref[0] != 'X') {
      printf("Enter valid choice [V or X]\n");
      continue;
    }
    break;
  }
    strcat(pref, " ");
    strcat(pref, allergy);
    return pref;
  } 
}
//display restaurant based on user preferences
carts restcart(carts cart,int choice, char pref[10]) {
  menu *rest = init_menu();
  int fcode[15], i = 0;
  char checkcode[10];
  menu restc = rest[choice - 1];
  printf("Food code  Item Name\t\t\t\t\t\t Price (Rs)\n");
  for (int j = 0; j < 15; j++) {
    strcpy(checkcode, restc.code[j]);
    int found = 0;
    for (int k = 2; k < strlen(pref); k += 2) {
      for (int l = 4; l < strlen(checkcode); l += 2) {
        if (checkcode[l] == pref[k]) {
          found++;
          break;
        }
      }
    }
    if (found == (strlen(pref) - 2) / 2) {
      if (pref[0] == 'V' && pref[0] == checkcode[0]) {
        if((checkcode[2]=='T' && (time_mod(1,30,4,30)||time_mod(10,30,18,30)))||(checkcode[2]=='M'&&time_mod(4,30,8,30))||(checkcode[2]=='A')){
        printf("%d.       %-30s - Rs.%.2f  \n", restc.fcode[j], restc.food_items[j],restc.price[j]);
        fcode[i] = restc.fcode[j];
        i++;
        }
      } else if (pref[0] == 'X') {
        if((checkcode[2]=='T' && (time_mod(1,30,4,30)||time_mod(10,30,18,30)))||(checkcode[2]=='M'&&time_mod(4,30,8,30))||(checkcode[2]=='A')){
        printf("%d.       %-30s - Rs.%.2f   \n", restc.fcode[j], restc.food_items[j],
               restc.price[j]);
        fcode[i] = restc.fcode[j];
        i++;
      }
      }
    }
  }
  
  if (i == 0) {
    printf("The restaurant does not have any food items that match your "
           "preferences. Try another restaurant\n");
    cart.total = -1;
    return cart;
  }
  
  cart = init_cart(cart, restc, fcode);
  return cart;
}
//creating cart with selected items
carts init_cart(carts cart, menu restc, int fcode[15]) {//10->15
  printf("\nPress 0 to stop adding to cart\n");
  int count;
  int flag=0;
  while (1) {
    int code;
    printf("\nEnter food code to add to cart: ");
    scanf("%d", &code);
    if (code == 0) {
      return cart;
    }
    //check if item already in cart
    int codeflag = 0;
    int j = cart.count;
    for (int b = 0; b < j; b++) {
      if (code == cart.code[b]) {
        printf("The food item is already in cart. To change quantity, customize the cart instead\n");
        codeflag = 1;
      }
    }
    if (codeflag == 1)
      continue;
    flag=0;
    //m<10 -> m<15
    for (int m = 0; m < 15; m++) {
      if (code == fcode[m]){
        flag = 1;
        while (1) {
          printf("Enter quantity: ");
          scanf("%d", &count);
          if (count > 0)
            break;
          else
            printf("Enter a valid quantity\n");
        }
        char temps[5];
        while (1){
          printf("Enter the temperature of your choice.<Hot/Warm/Cold>: ");
          scanf("%s",temps);
          for (int i = 0; temps[i] != '\0'; i++) {
            temps[i] = toupper(temps[i]);
          }
          if (strcmp(temps,"HOT")==0||strcmp(temps,"COLD")==0||strcmp(temps,"WARM")==0)
            break;
        else
          printf("Enter a valid choice\n");
        }
        cart.code[j] = fcode[m];
        cart.total += restc.price[code % 100 - 1] * count;
        cart.qty[j] = count;
        strcpy(cart.tempr[j],temps);
        strcpy(cart.cartlist[j], restc.food_items[code % 100 - 1]);
        strcpy(cart.tempr[j], temps);
        cart.count++;
        if (frec==1){
          freccheck[j]=1;
        }
        displaycart(cart);
      }
    }
    if (flag != 1) {
      printf("Invalid choice: Enter a valid food code or press 0\n");
    }
    flag=0;
  }
}

carts foodcart(carts cart, char pref[10]) {
  menu *rest = init_menu();
  char pref1[10];
  int foodfreq[]={//array size 200->300
      101, 0, 102, 0, 103, 0, 104, 0, 105, 0,
      106, 0, 107, 0, 108, 0, 109, 0, 110, 0,
      111, 0, 112, 0, 113, 0, 114, 0, 115, 0,
      201, 0, 202, 0, 203, 0, 204, 0, 205, 0,
      206, 0, 207, 0, 208, 0, 209, 0, 210, 0,
      211, 0, 212, 0, 213, 0, 214, 0, 215, 0,
      301, 0, 302, 0, 303, 0, 304, 0, 305, 0,
      306, 0, 307, 0, 308, 0, 309, 0, 310, 0,
      311, 0, 312, 0, 313, 0, 314, 0, 315, 0,
      401, 0, 402, 0, 403, 0, 404, 0, 405, 0,
      406, 0, 407, 0, 408, 0, 409, 0, 410, 0,
      411, 0, 412, 0, 413, 0, 414, 0, 415, 0,
      501, 0, 502, 0, 503, 0, 504, 0, 505, 0,
      506, 0, 507, 0, 508, 0, 509, 0, 510, 0,
      511, 0, 512, 0, 513, 0, 514, 0, 515, 0,
      601, 0, 602, 0, 603, 0, 604, 0, 605, 0,
      606, 0, 607, 0, 608, 0, 609, 0, 610, 0,
      611, 0, 612, 0, 613, 0, 614, 0, 615, 0,
      701, 0, 702, 0, 703, 0, 704, 0, 705, 0,
      706, 0, 707, 0, 708, 0, 709, 0, 710, 0,
      711, 0, 712, 0, 713, 0, 714, 0, 715, 0,
      801, 0, 802, 0, 803, 0, 804, 0, 805, 0,
      806, 0, 807, 0, 808, 0, 809, 0, 810, 0,
      811, 0, 812, 0, 813, 0, 814, 0, 815, 0,
      901, 0, 902, 0, 903, 0, 904, 0, 905, 0,
      906, 0, 907, 0, 908, 0, 909, 0, 910, 0,
      911, 0, 912, 0, 913, 0, 914, 0, 915, 0,
      1001, 0, 1002, 0, 1003, 0, 1004, 0, 1005, 0,
      1006, 0, 1007, 0, 1008, 0, 1009, 0, 1010, 0,
      1011, 0, 1012, 0, 1013, 0, 1014, 0, 1015, 0
  };
  FILE *fil=fopen("Food.csv","r");
  char line[30];
  while (fgets(line, sizeof(line), fil)) {
    char *token = strtok(line, ",");
    while (token != NULL) {
      int code = atoi(token);
      for (int i=0;i<300;i+=2){
        if (code==foodfreq[i])
          foodfreq[i+1]++;
      }
      token = strtok(NULL, ",");
  }
  }
  int len = sizeof(foodfreq) / sizeof(foodfreq[0]);
  bubblesort(len, foodfreq);
  printf("******Displaying most frequently ordered food items******\n\n");
   printf("Code\tRestaurant Name\t\t\tItem Name\t\t\tPrice\n");
  // Displaying food items completed
  int count = 0, i = 0;
  char checkcode[15];
  int fcode[15];
  while (count < 10) { 
    menu restc = rest[foodfreq[i] / 100 - 1];
    for (int j = 0; j < 15; j++) {
      if (foodfreq[i] == restc.fcode[j]) {
        strcpy(checkcode, restc.code[j]);
        int found = 0;
        for (int k = 2; k < strlen(pref); k += 2) {
          for (int l = 4; l < strlen(checkcode); l += 2) {
            if (checkcode[l] == pref[k]) {
              found++;
              break;
            }
          }
        }

        if (found == (strlen(pref) - 2) / 2) {
          if (pref[0] == 'V' && pref[0] == checkcode[0]) {
    //sorting tiffin,meals        
            if(((time_mod(1,30,4,30) || time_mod(10,30,18,30)) && checkcode[2]=='T') || (time_mod(4,30,8,30) && checkcode[2]=='M') || (checkcode[2]=='A')){
              printf("%d\t\t%-20s%-25s - Rs.%.2f\n", restc.fcode[j], restc.restname, restc.food_items[j], restc.price[j]);
            fcode[count] = restc.fcode[j];
            count++;
          } }
          else if (pref[0] == 'X') {
            if((checkcode[2]=='T' && (time_mod(1,30,4,30)||time_mod(10,30,18,30)))||(checkcode[2]=='M'&&time_mod(4,30,8,30))||(checkcode[2]=='A')){
              printf("%d\t\t%-20s%-25s - Rs.%.2f\n", restc.fcode[j], restc.restname, restc.food_items[j], restc.price[j]);
            fcode[count] = restc.fcode[j];
            count++;
            }
          }
        }
      }
    }
    i += 2;
  }
  printf("\n");
  //adding to cart
  printf("Enter the food code of the item you wish to add: ");
  int fcodef;
  scanf("%d", &fcodef);
  int flagfood = 0;
  menu restc = rest[fcodef / 100 - 1];
  int rno=fcodef/100-1;
  for (int i = 0; i < 15; i++) {
    int j = cart.count;
    if (fcodef == fcode[i]) {
      while (1) {
        printf("Enter quantity: ");
        scanf("%d", &count);
        if (count > 0)
          break;
        else
          printf("Enter a valid quantity\n");
      }
      char temps[5];
      //sorting by temperature
      while (1){
        printf("Enter the temperature of your choice.<Hot/Warm/Cold>: ");
        scanf("%s",temps);
        for (int i = 0; temps[i] != '\0'; i++) {
          temps[i] = toupper(temps[i]);
        }
        if (strcmp(temps,"HOT")==0||strcmp(temps,"COLD")==0||strcmp(temps,"WARM")==0)
          break;
      else
        printf("Enter a valid choice");
      }
      flagfood = 1;
      cart.code[j] = fcode[i];
      cart.total += restc.price[fcodef % 100 - 1] * count;
      cart.qty[j] = count;
      strcpy(cart.tempr[j],temps);
      strcpy(cart.cartlist[j], restc.food_items[fcodef % 100 - 1]);
      cart.count++;
      displaycart(cart);
      break;
    }
  }
  if (flagfood == 0){
    printf("Food code is not suited to your dietary requirements");
    cart.total=-1;
    return cart;
  }
  else{
    printf("Menu of %s\n",rest[rno].restname);
    cart=restcart(cart,rno+1,pref);
    return cart;
  }
}
//displaying cart
void foodcsv(int items[],int len){
  FILE *fil=fopen("Food.csv","a");
  for (int i = 0; i < len; i++) {
    if (i == len - 1) {
        fprintf(fil, "%d\n", items[i]);
    } else {
        fprintf(fil, "%d,", items[i]);
    }
  }
  fclose(fil);
}