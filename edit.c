#include <stdio.h>
#include <string.h>
#include "menu.h"
//display current food items
void displaycart(carts cart){
 printf("\n**************************** Cart ****************************\n");
    printf("S.no  Food Code      Food item                Qty    Temperature\n");
    for (int i = 0; i < cart.count; i++) {
        printf("%-6d%-14d%-30s%-7d%-10s\n", i + 1, cart.code[i], cart.cartlist[i], cart.qty[i], cart.tempr[i]);
    }
    printf("\nTotal : Rs.%.2f\n\n", cart.total);
}
//adding food items
carts add(carts cart,char *pref){
  menu * rest=init_menu();
  int choice=cart.code[0]/100;//restaurant code=food code's first digit
  int fcode[15],i=0;
  char checkcode[10];
  menu restc = rest[choice-1];
  int len=sizeof(cart.code)/sizeof(cart.code[0]);
    for (int j=0; j<15; j++){
      strcpy(checkcode,restc.code[j]);
      int found=0;
      for (int k=2; k<strlen(pref);k+=2)
      {
        for (int l=4; l<strlen(checkcode); l+=2){
            if (checkcode[l]==pref[k]){
              found++;
              break;
            }
        }
      }
      if (found==(strlen(pref)-2)/2 ){
        if (pref[0]=='V' && pref[0]==checkcode[0]){
          if((checkcode[2]=='T' && (time_mod(1,30,4,30)||time_mod(10,30,18,30)))||(checkcode[2]=='M'&&time_mod(4,30,8,30))||(checkcode[2]=='A')){
              printf("%d. %-30s - Rs.%.2f  \n",restc.fcode[j],restc.food_items[j],restc.price[j]);
              fcode[i]=restc.fcode[j];
              i++;
            }
        }
        else if(pref[0]=='X'){
          if((checkcode[2]=='T' && (time_mod(1,30,4,30)||time_mod(10,30,18,30)))||(checkcode[2]=='M'&&time_mod(4,30,8,30))||(checkcode[2]=='A')){
          printf("%d. %-30s - Rs.%.2f   \n",restc.fcode[j],restc.food_items[j],restc.price[j]);
          fcode[i]=restc.fcode[j];
          i++;
          }
        }
      }  
    }
  cart=init_cart(cart, restc,fcode);
  return cart;
}
//delete cart items
carts del(carts cart){
      menu *rest=init_menu();
      int code;
      displaycart(cart);
      printf("Enter the foodcode of item to be deleted:");
      scanf("%d",&code);
      int found = 0;
      for (int i = 0; i < cart.count; i++) {
          if (cart.code[i] == code) {
              menu restc=rest[code/100-1];
              cart.total -= cart.qty[i] * restc.price[code%100-1]; 
              for (int j = i; j < cart.count -1; j++) {
                  cart.code[j] = cart.code[j + 1];
                  cart.qty[j] = cart.qty[j + 1];
                  strcpy(cart.cartlist[j], cart.cartlist[j + 1]);
                  strcpy(cart.tempr[j], cart.tempr[j + 1]);
                  freccheck[i]=freccheck[i+1];
              }
              cart.count--;
              found = 1;
              break;
          }
      }
      if (!found) {
          printf("Item with code %d not found in the cart.\n", code);
      }
  return cart;
}
//change quantity
carts customize(carts cart){
  menu * rest= init_menu();
  menu restc=rest[cart.code[0]/100-1];
  int found=0;
  displaycart(cart);
  printf("Enter the code of the food item to customize:");
  int fcodec;
  scanf("%d",&fcodec);
  for (int i=0;i<cart.count;i++){
    if (cart.code[i]==fcodec){
      found=1;
      printf("Enter the new quantity for the food item:");
      int qty;
      scanf("%d",&qty);
      int temp=cart.qty[i];
      cart.qty[i]=qty;
      cart.total=cart.total+restc.price[fcodec%100-1]*(qty-temp);
    }
  }
  if (!found)
    printf("Food item with code %d not found in the cart.\n",fcodec);

  else{
    printf("Displaying Updated cart: \n");
    displaycart(cart);
  }
  return cart;
}