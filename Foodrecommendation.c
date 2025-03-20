#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mincount 3
#define max 200

// Define itemlist structure to hold items and their count
typedef struct {
  int items[10];
  int count;
} itemlist;

// Define score structure to hold item pairs, confidence, and lift
typedef struct{
  int items[2];
  float confidence;
  float lift;
} score;

itemlist transactions[max];  
itemlist candidates[10];     
itemlist subsets[max];       
score finalist[30];   

// Function to retrieve data from a CSV file
void ret_data(int *numTransactions) {
  FILE *file = fopen("Food.csv", "r");  
  if (!file) {  
    printf("error");
    exit(1);
  }
  char row[100];

  // Read the file line by line
  while (fgets(row, sizeof(row), file)) {
    transactions[*numTransactions].count = 0;
    char *token = strtok(row, ",\n");  
    while (token != NULL) {
      transactions[*numTransactions].items [transactions[*numTransactions].count++] = atoi(token);  
      token = strtok(NULL, ",\n");  
    }
    (*numTransactions)++;
  }
  fclose(file);  
}

// Function to clear data based on choice
void clear_data(int *size, int choice) {
  int index = 0;
  for (int i = 0; i < *size; i++) {
    if (transactions[i].items[0] / 100 == choice) {  // Check if item belongs to the chosen category
      if (index < i) {
        transactions[index] = transactions[i];
      }
      index++;
    }
  }
  *size = index;  // Update the size
}

// Function to calculate item frequency
void itemfreq(int size, int choice, int *sizex) {
  for (int i = 0; i < 15; i++) {
    int count = 0;
    int var = choice * 100 + i + 1;
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < transactions[j].count; k++) {
        if (transactions[j].items[k] == var) {
          count++;
        }
      }
    }
    if (count >= mincount) {
      candidates[*sizex].items[0] = var;
      candidates[*sizex].count = count;
      (*sizex)++;
    }
  }
}

// Function to find item sets
void itemsets(int size, int num1, int num2, int *sizey, int *count) {
  for (int i = 0; i < size; i++) {
    int found = 0;
    for (int j = 0; j < transactions[i].count; j++) {
      if (transactions[i].items[j] == num1)
        found++;
      if (transactions[i].items[j] == num2)
        found++;
    }
    if (found == 2)
      (*count)++;
    found = 0;
  }
  if (*count > 0) {
    subsets[*sizey].items[0] = num1;
    subsets[*sizey].items[1] = num2;
    subsets[(*sizey)++].count = *count;
  }
}

// Function to calculate scores (confidence and lift)
void calscores(int sizex, int sizey, int *sizez) {
  for (int i = 0; i < sizey; i++) {
    int temp1 = subsets[i].items[0], temp2 = 0;
    for (int k = 0; k < sizex; k++) {
      if (candidates[k].items[0] == subsets[i].items[1]) {
        temp2 = candidates[k].count;
        break;
      }
    }
    for (int j = 0; j < sizex; j++) {
      if (candidates[j].items[0] == temp1) {
        float confidence = (float)subsets[i].count / (float)candidates[j].count;
        if (confidence >= 0.4) {
          float lift = confidence / (float)temp2;
          finalist[*sizez].items[0] = subsets[i].items[0];
          finalist[*sizez].items[1] = subsets[i].items[1];
          finalist[*sizez].confidence = confidence;
          finalist[(*sizez)++].lift = lift;
        }
      }
    }
  }
}

// Function to recommend food items based on the cart
int* food_rec(carts cart, int *var) {
  int size = 0, sizex = 0, sizey = 0, sizez = 0;
  int choice;
  choice = cart.code[0] / 100;
  ret_data(&size);  
  clear_data(&size, choice);  
  itemfreq(size, choice, &sizex);  

  for (int i = 0; i < sizex; i++) {
    for (int j = 0; j < sizex; j++) {
      if (candidates[i].items[0] != candidates[j].items[0]) {
        int count = 0;
        itemsets(size, candidates[i].items[0], candidates[j].items[0], &sizey, &count);
      }
    }
  }
  calscores(sizex, sizey, &sizez);  // Calculate scores

  // Allocate memory for the recommended items
  int *fcoode = (int*)malloc(15 * sizeof(int)); 
  if (fcoode == NULL) {
    printf("Memory allocation failed"); 
    exit(1);
  }

  int flag = 1;
  for (int m = 0; m < cart.count; m++) {
    for (int i = 0; i < sizez; i++) {
      if (finalist[i].items[0] == cart.code[m]) {
        for (int k = 0; k < *var; k++) {
          if (finalist[i].items[1] == fcoode[k]) {
            flag = 0;
            break;
          }
        }
        if (flag == 1)
          fcoode[(*var)++] = finalist[i].items[1];
      }
    }  
  }
  return fcoode;  // Return the recommended items
}
