#include "menu.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
  char uname[32];
  int points;
}Coupons;

Coupons coupons[25];
  void bill(char uname[], carts cart) {
    char cred[100];
    char arr[100][20];
    FILE *file = fopen("Userdetails.csv", "r");
    int num = 0;
    while (fgets(cred, 100, file) != NULL) {
        char *det = strtok(cred, ",");
        while (det != NULL) {
            strcpy(arr[num], det);
            det = strtok(NULL, ",");
        }
        num++;   // finds number of users
    }
    fclose(file);

    FILE *fp = fopen("coupons.txt", "r");
    for (int i = 0; i < num; i++) {
        fscanf(fp, "%s %d", coupons[i].uname, &coupons[i].points);
    }
    fclose(fp);

    menu *rest = init_menu();
    menu restc = rest[cart.code[0] / 100 - 1];

    time_t date;
    time(&date);
    struct tm *localTime = localtime(&date);
    int month = localTime->tm_mon + 1;
    int tdate = localTime->tm_mday;

    printf("*************************************************************\n");
    printf("*********************** BILL SUMMARY ************************\n");
    printf("*************************************************************\n\n");

    // Displaying cart contents
    displaycart(cart);

    // Applying seasonal discounts based on current date
    if (month == 1 && tdate == 1) {
        printf("New Year's Discount: - Rs %.2f\n", 0.15 * cart.total);
        cart.total -= 0.15 * cart.total;
    } else if (month == 2 && tdate == 14) {
        printf("Valentine's Day Discount: - Rs %.2f\n", 0.05 * cart.total);
        cart.total -= 0.05 * cart.total;
    } else if (month == 8 && tdate == 15) {
        printf("Independence Day Discount: - Rs %.2f\n", 0.5 * cart.total);
        cart.total -= 0.5 * cart.total;
    } else if (month == 12 && tdate == 25) {
        printf("Christmas Day Discount: - Rs %.2f\n", 0.35 * cart.total);
        cart.total -= 0.35 * cart.total;
    } else if (month == 1 && tdate == 26) {
        printf("Republic Day Discount: - Rs %.2f\n", 0.5 * cart.total);
        cart.total -= 0.5 * cart.total;
    }
    else if (month == 6 && (tdate == 21 || tdate ==20)) {
      printf("Exam Day Discount :) : - Rs %.2f\n", 0.05 * cart.total);
      cart.total -= 0.05 * cart.total;
    }

    // Adding GST
    float gst = 0.07 * cart.total;
    printf("GST (7%%): Rs %.2f\n", gst);
    cart.total += gst;

    // Adding distance-based tax if applicable
    if (branchdist > 10) {
        float extra = (float)(branchdist - 10);
        float distTax = extra * 3.0;
        printf("Distance Based Tax: Rs %.2f\n", distTax);
        cart.total += distTax;
    }

    // Applying 5% discount for recommended items
    int var=0;
    if (frec==1){
    int *fcoode = food_rec(cart, &var);
    for (int i=0;i<cart.count;i++){
      for (int j=0;j<var;j++){
      if (cart.code[i]==fcoode[j]){
          if (freccheck[i]==1){
            printf("5%% discount for ordering recommended item %s\n",cart.cartlist[i]);
            printf("Discount : Rs %.2f\n",cart.qty[i]*restc.price[cart.code[i]%100-1]*0.05);
            cart.total-=cart.qty[i]*restc.price[cart.code[i]%100-1];
             cart.total+=cart.qty[i]*restc.price[cart.code[i]%100-1]*0.95;
            break;
        }
        }
    }
    }
      printf("Total : Rs %.2f\n",cart.total);
    }

    // Additional discounts for returning customers for churn prevention
    int churn = churncust(uname);
    if (churn == 1) {
        printf("Returning Customer Discount: 10%%\n");
        float churnDiscount = 0.1 * cart.total;
        cart.total -= churnDiscount;
      printf("Total: Rs %.2f\n",cart.total);
    }
    
    // Adding eco-friendly packaging cost
    int flag=0;
    printf("\nEco-Friendly Packaging Program:\n");
    printf("Each bio-degradable box costs Rs 5\n");
    printf("Do you want to opt for Eco-Friendly Packaging? <Yes/No>: ");
    char ecop[4];
    scanf("%s",ecop);
    for (int i = 0; ecop[i] != '\0'; i++) {
      ecop[i] = toupper(ecop[i]);
    if(strcmp(ecop,"YES")==0){
    int ecocost=0;
    flag=1;
    for(int i=0;i<cart.count;i++){
      ecocost+=5*cart.qty[i];
    }
    cart.total+=ecocost;
      
    }
      
    }
    if (flag==1)
    printf("Total: Rs %.2f\n",cart.total);
    

    // Plastic return program
    printf("\nPlastic Return Program:\n");
    printf("Return used plastic packaging and earn 15 points per item returned\n");
    printf("Do you want to opt for Plastic Return Program? <Yes/No>: ");
    char prp[4];
    scanf("%s", prp);
    int plast;
    for (int i = 0; prp[i] != '\0'; i++) {
        prp[i] = toupper(prp[i]);
    }
    if (strcmp(prp, "YES") == 0) {
        plast=1;
    }
    
  int i=0,total=0;
  if (cart.total>1000){   //adding coupons for current order
    total=cart.total-500;
  }
  for (i=0;i<num;i++){
    if (strcmp(coupons[i].uname,uname)==0){
      if (plast==1)
        coupons[i].points+=15;
      coupons[i].points+=total/500;
      printf("\nYou have a total of %d coupons!\n",coupons[i].points);
      break;
    }
  }

  if (cart.total>100){
  if (coupons[i].points>20){
    printf("Do you wish to use them <Yes/No>?: ");
    char chc[5];
    scanf("%s",chc);
    for (int i = 0; chc[i] != '\0'; i++) {
      chc[i] = toupper(chc[i]);
    }
    if (strcmp(chc, "YES") == 0){
      coupons[i].points-=20;
      cart.total-=100;
      printf("You have won Rs. 100 as cashback\n");
    }
  }
//mode of payment
  }
  printf("Final total: Rs %.2f\n",cart.total);
  while (1){
    printf("\nPayment options: \n");
    printf("1 - Cash on Delivery\n2 - Credit Card\n3 - Debit Card\n4 - UPI\n");
    int mode;
    printf("\nEnter your preferred mode of payment:");
    scanf("%d",&mode);
    if (mode==1){
      printf("You can pay on delivery. Enjoy your meal!\n");
      break;
    }
    else if (mode==2){
      //credit card credentials

      char ccnum[16];
      char ccname[20];
      char ccexp[5];
      char cccvv[3];
      printf("Processing fee has been waived. Enjoy your purchase!\n");
      printf("Enter payment details for card payment:\n");
      printf("Card Number: ");
      scanf("%s",ccnum);
      printf("Cardholder Name: ");
      scanf("%s",ccname);
      printf("Expiry (MM/YY): ");
      scanf("%s",ccexp);
      printf("CVV: ");
      scanf("%s",cccvv);
      printf("Payment successful. Thank you!\n");
      printf("\n");
      break;


    }
    else if(mode==3){
      // debit card credentials and discount
      char dcnum[16];
      char dcname[20];
      char dcexp[5];
      char dccvv[3];
      printf("Discount=5%%\nDiscount=%.2f\n",0.05*cart.total);
      cart.total-=0.05*cart.total;
      printf("Total: Rs %.2f\n",cart.total);
      printf("Enter payment details for card payment:\n");
      printf("Card Number: ");
      scanf("%s",dcnum);
      printf("Cardholder Name: ");
      scanf("%s",dcname);
      printf("Expiry (MM/YY): ");
      scanf("%s",dcexp);
      printf("CVV: ");
      scanf("%s",dccvv);
      
      printf("Payment successful. Thank you!\n");
      printf("\n");
      break;
    }
    else if(mode==4){
      printf("Pay via UPI to one of the following numbers:\n1. 78248000\n2. 9940546790\n3. 9344983510\n"); 
      break;
    }
    else
      printf("Invalid payment mode selected.\n");
  }
  //modifies latest date of purchase
  printf("\n");
  changechurn(uname);
  
  fp=fopen("coupons.txt","w");
  for (int i=0; i<num;i++){
    fprintf(fp,"%s %d\n",coupons[i].uname,coupons[i].points);
  }
  fclose(fp);
    
  srand(time(NULL));
  int randnum = (rand() % 
  (99999 - 9999 + 1)) + 9999; 
  printf("Your order number is: %d \n", randnum); // random order number generated
  displaycart(cart);
    
  char filename[36];
  strcpy(filename,uname);
  strcat(filename,".txt");
  file = fopen(filename, "a");
  fprintf(file,"%d\n",randnum);
  for (int i=0;i<cart.count;i++){
    fprintf(file,"%d\t%s\t%d\n",cart.code[i],cart.cartlist[i], cart.qty[i]);
  }
  fprintf(file, "%.2f\n",cart.total);
  printf("The order will be sent to the address: %s\nEnjoy your purchase!\n\n",address);
  fclose(file);
}

int churncust(char username[]){
  int churn=0;
  char cred[100];
  char arr[100][20];
  FILE *file = fopen("Userdetails.csv", "r");
  int cnum = 0;
  while (fgets(cred, 100, file) != NULL) {
    char *det = strtok(cred, ",");
    while (det != NULL) {
      strcpy(arr[cnum], det);
      det = strtok(NULL, ",");

    }
    cnum++; // finds number of users
  }
  fclose(file);
  FILE *fch=fopen("custchurn.txt","r");
  time_t t = time(NULL);
  struct tm *now = localtime(&t);
  int cmonth = now->tm_mon + 1;
  int month[100];
  char uname[100][32];
  for (int i=0;i<cnum;i++){
  fscanf(fch,"%s %d\n",uname[i],&month[i]);
  }
  fclose(fch);
  for (int i=0;i<cnum;i++){
    if (strcmp(uname[i],username)==0){
      int mondif;
      if (cmonth>=month[i])
        mondif=cmonth-month[i];
        // calculates difference between last purchase and current month
      else
        mondif=12 - month[i] + cmonth;
      if (month[i]==0)
        return 0;
      if (mondif>2)
        return 1;
      else
        return 0;
        
      
    }
  }
  return churn;
}
void changechurn(char username[]){
  char cred[100];
  char arr[100][20];
  FILE *file = fopen("Userdetails.csv", "r");
  int cnum = 0;
  while (fgets(cred, 100, file) != NULL) {
    char *det = strtok(cred, ",");
    while (det != NULL) {
      strcpy(arr[cnum], det);
      det = strtok(NULL, ",");

    }
    cnum++;
  }
  fclose(file);

FILE *fch=fopen("custchurn.txt","r");
time_t t = time(NULL);
struct tm *now = localtime(&t);
int cmonth = now->tm_mon + 1;
int month[100];
char uname[100][32];
for (int i=0;i<cnum;i++){
fscanf(fch,"%s %d\n",uname[i],&month[i]);
} //modifies the last purchase date t match current month if the bill has been generated
fclose(fch);
  for (int i=0;i<cnum;i++){
    if (strcmp(uname[i],username)==0){
      month[i]=cmonth;
    }
  }
  fch=fopen("custchurn.txt","w");
  for (int i=0;i<cnum;i++){
    fprintf(fch,"%s %d\n",uname[i],month[i]);
  }
  fclose(fch);
}
