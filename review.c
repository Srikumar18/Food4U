#include "menu.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define column 100
int code;
int rating;

typedef struct{
  int rest;
  float rat;
  int num;
}reviews;
reviews rev[10];

void rest_rev(carts cart){
  FILE *frev=fopen("review_rest.txt","r");
  for (int i=0; i<10;i++){
    fscanf(frev, "%d %f %d", &rev[i].rest, &rev[i].rat,&rev[i].num);
  }
  fclose(frev);

  menu *rest = init_menu();
  int rno;
  rno=cart.code[0]/100;
  printf("\nRate %s to help improve service!\n" ,rest[rno-1].restname);
  while (1){ //suitable restaurant review is obtained
    printf("1 - Very poor\n2 - Poor\n3 - Average\n4 - Good\n5 - Excellent\n");
    printf("Enter your rating:");
      scanf("%d",&rating);
      if (rating>5 || rating<1)
        printf("Enter a valid number\n");
      else
        break;
  }
  float avgrev;
  avgrev=(float)((rev[rno-1].rat*rev[rno-1].num)+rating)/(++rev[rno-1].num);
  rev[rno-1].rat=avgrev;
  frev=fopen("review_rest.txt","w");
  for (int i=0; i<10;i++){
    fprintf(frev,"%d %.1f %d\n",rev[i].rest,rev[i].rat, rev[i].num);
    }
    fclose(frev);
// file contains restaurant number, average review and number of reviews
}

typedef struct{
  int fno;
  float rat;
  int num;
}freview;
freview revf[150];
void food_rev(carts cart){
  FILE *frev=fopen("review_food.txt","r");
  for (int i=0; i<150;i++){
    fscanf(frev, "%d %f %d", &revf[i].fno, &revf[i].rat, &revf[i].num);
  }
  fclose(frev);

  int rno;
  rno=cart.code[0]/100;
  for (int l=0;l<cart.count;l++){ //suitable food review is obtained
  printf("\nHelp us out by rating %s!\n",cart.cartlist[l]);
  int rate;
  float avgrev;
  for (int m=0;m<150;m++){
    if (revf[m].fno==cart.code[l]){
      while (1){
        printf("1 - Very poor\n2 - Poor\n3 - Average\n4 - Good\n5 - Excellent\n");
        printf("Enter your rating:");
        scanf("%d",&rate);
        if (rate>5 || rate<1)
          printf("Enter a valid number\n");
        else
          break;
      }
      avgrev=((revf[m].rat*revf[m].num)+rate)/(revf[m].num+1);
      revf[m].rat=avgrev;
      revf[m].num++;
    }
  }
  }

  frev=fopen("review_food.txt","w");
  for (int i=0; i<150;i++){
    fprintf(frev,"%d %.1f %d\n",revf[i].fno,revf[i].rat, revf[i].num);
    }
    fclose(frev);
  // file contains food code, average review and number of reviews
}

//queries 
typedef struct{
  char email[20];
  char query[1000];
}queries;
queries que[500];
void rest_que(char uname[],carts cart){
  // queries stored with query number, restaurant number, email id and query for easy admin access
  FILE *quer=fopen("queries.txt","r");
  int count = 0;
  char c;
  while ((c = fgetc(quer)) != EOF) {
      if (c == '\n') {
          count++;
      }
  }

  FILE *fque=fopen("queries.txt","a");
  int num_que=0;
  char que_choice[4];
  while (1){
    printf("Do you have any queries?<Yes/No>: ");
    scanf("%s",que_choice);
    while (getchar() != '\n');
    for (int i = 0; que_choice[i] != '\0'; i++) {
      que_choice[i] = toupper(que_choice[i]);
    } 
    if (strcmp(que_choice, "YES") == 0){
      char cred[100];
      char arr[100][20];
      int num=0;
      FILE *usdet=fopen("Userdetails.csv","r");
      while (fgets(cred, 100, usdet) != NULL) {
        char *det = strtok(cred, ",");
        while (det != NULL) {
          strcpy(arr[num], det);
          det = strtok(NULL, ",");
          num++;
    }
  }
      
      char email[32];
  for (int i =1 ; arr[i][0]!='\0'; i += 5) {
    if (strcmp(uname, arr[i]) == 0) {
      strcpy(email,arr[i+2]);
      break;
    }
  }
      printf("Please enter your query: ");
      scanf("%[^\n]",que[num_que].query);
      strcpy(que[num_que].email,email);
      int rno=cart.code[0]/100;
      fprintf(fque,"%d %d %-20s\t%s\n",++count,rno,que[num_que].email,que[num_que].query);
      num_que++;
    }
    else if (strcmp(que_choice,"NO")==0)
      break;
    else
      printf("Invalid choice. Try again");
  }
  fclose(fque);
}

typedef struct{
  float rat;
  int num;
}dreview;

dreview revd[10];
void driver_rev(int driverindex){
  FILE *drev=fopen("review_driver.txt","r");
  for (int i=0; i<10;i++){
    fscanf(drev, "%f %d", &revd[i].rat, &revd[i].num);
  }
  fclose(drev);
  float avgrev;
  int rate;
  while (1){ //suitable driver review is obtained
    printf("1 - Very poor\n2 - Poor\n3 - Average\n4 - Good\n5 - Excellent\n");
    printf("Enter your rating for driver %d:",driverindex+1);
    scanf("%d",&rate);
    if (rate>5 || rate<1)
      printf("Enter a valid number\n");
    else
      break;
  }
    avgrev=((revd[driverindex].rat*revd[driverindex].num) +rate)/(revd[driverindex].num+1);
    revd[driverindex].rat=avgrev;
    revd[driverindex].num++;
  
  drev=fopen("review_driver.txt","w");
  for (int i=0; i<10;i++){
    fprintf(drev,"%.1f %d\n",revd[i].rat, revd[i].num);
    }
    fclose(drev);
  // file contains driver number, average review and number of reviews
}
