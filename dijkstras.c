#include "menu.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITY 9999
#define MAX 30

int r_distance[MAX];
int d_distance[MAX];
char branch[15];
int Branchdistances[4];
int source;
// Array of arrays storing possible routes and respective distances for all locations
int Graph[MAX][MAX] = {{0, 0, 2, 0, 0, 3, 0, 0, 0, 0, 0, 0, 8, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {1, 0, 4, 2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {2, 4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 2, 3, 0, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 7, 0, 1, 0, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {3, 0, 0, 8, 3, 0, 3, 4, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 2, 3, 0, 4, 2, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 4, 4, 0, 1, 5, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 2, 1, 0, 2, 3, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 5, 2, 0, 3, 2, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 2, 4, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 3, 5, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 3, 0, 3, 2,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 3, 0, 2,
                        3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0,
                        1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1,
                        0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
                        1, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        2, 1, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 3, 2, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 1, 2, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 1, 2, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 1, 2, 0, 2, 1, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 1, 2, 0, 2, 1, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 1, 2, 0, 2, 1, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 2, 1, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 2, 1, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 2, 1, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 2, 1},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 2},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0}};
// Array of Locations of restaurants
char R_Locations[MAX][25] = {
    "Adyar",       "Anna Nagar",     "Ashok Nagar",  "Besant Nagar",
    "Chromepet",   "Egmore",         "Guindy",       "Kilpauk",
    "Kodambakkam", "Kolathur",       "Madhavaram",   "Madipakkam",
    "Mandaveli",   "Mylapore",       "Nanganallur",  "Nungambakkam",
    "Perambur",    "Porur",          "Purasawalkam", "Royapettah",
    "Saidapet",    "Sholinganallur", "Tambaram",     "Teynampet",
    "T. Nagar",    "Thiruvanmiyur",  "Triplicane",   "Vadapalani",
    "Velachery",   "West Mambalam"};
// Array of all possible Locations of drivers
char D_Locations[MAX][25] = {
    "Adyar",       "Anna Nagar",     "Ashok Nagar",  "Besant Nagar",
    "Chromepet",   "Egmore",         "Guindy",       "Kilpauk",
    "Kodambakkam", "Kolathur",       "Madhavaram",   "Madipakkam",
    "Mandaveli",   "Mylapore",       "Nanganallur",  "Nungambakkam",
    "Perambur",    "Porur",          "Purasawalkam", "Royapettah",
    "Saidapet",    "Sholinganallur", "Tambaram",     "Teynampet",
    "T. Nagar",    "Thiruvanmiyur",  "Triplicane",   "Vadapalani",
    "Velachery",   "West Mambalam"};
// Array of arrays of branches for each restaurant
int Branches[10][4] = {{0, 4, 13, 28},  {2, 5, 8, 13},    {9, 19, 21, 28},
                       {6, 11, 18, 27}, {10, 15, 22, 29}, {3, 7, 10, 28},
                       {6, 12, 14, 16}, {1, 3, 4, 11},    {8, 17, 20, 25},
                       {19, 23, 24, 26}};

void Dijkstra(int Graph[][MAX], int n, int start, int distance[], char Locations[][25]) {
  int cost[MAX][MAX], pred[MAX];
  int visited[MAX], count, mindistance, nextnode, i, j;

  // Creating cost matrix
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (Graph[i][j] == 0)
        cost[i][j] = INFINITY;
      else
        cost[i][j] = Graph[i][j];
    }
  }
  for (i = 0; i < n; i++) {
    distance[i] = cost[start][i];
    pred[i] = start;
    visited[i] = 0;
  }

  distance[start] = 0;
  visited[start] = 1;
  count = 1;

  while (count < n - 1) {
    mindistance = INFINITY;

    for (i = 0; i < n; i++) {
      if (distance[i] < mindistance && !visited[i]) {
        mindistance = distance[i];
        nextnode = i;
      }
    }
    visited[nextnode] = 1;
    for (i = 0; i < n; i++) {
      if (!visited[i]) {
        if (mindistance + cost[nextnode][i] < distance[i]) {
          distance[i] = mindistance + cost[nextnode][i];
          pred[i] = nextnode;
        }
      }
    }
    count++;
  }
}
// Finding distances from user location to all restaurant branches
void restaurantdistance(char location[], int choice, char BranchLocations[][25], int Branchdistances[]) {
  int branches[4], n = 30;
  for (int i = 0; i < MAX; i++) {
    if (strcmp(location, R_Locations[i]) == 0) {
      source = i;
      break;
    }
  }
  for (int k = 0; k < 4; k++) {
    branches[k] = Branches[choice - 1][k];// Getting the branch numbers for the restaurant
    strcpy(BranchLocations[k], R_Locations[Branches[choice - 1][k]]);
  }
  // Using Dijkstras algorithm to find the shortest distance from the user location to each branch
  Dijkstra(Graph, MAX, source, r_distance, R_Locations);

  char Source[25];
  strcpy(Source, R_Locations[source]);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - 1; j++) {
      if (r_distance[j] > r_distance[j + 1]) {
        char temloc[25];
        int temp;
        temp = r_distance[j];
        strcpy(temloc, R_Locations[j]);
        r_distance[j] = r_distance[j + 1];
        strcpy(R_Locations[j], R_Locations[j + 1]);
        r_distance[j + 1] = temp;
        strcpy(R_Locations[j + 1], temloc);
      }
    }
  }
  printf("\nDisplaying the branches near %s:", Source);
  for (int i = 0; i < 30; i++) {
    for (int j = 0; j < 4; j++) {
// Displaying each branch with shortest distance
      if (strcmp(BranchLocations[j], R_Locations[i]) == 0) {
        Branchdistances[j] = r_distance[i];
        printf("\n%s: %d km", R_Locations[i], r_distance[i]);
      }
    }
  }
}
// Enabling user to enter restaurant branch
char *branchselection(char BranchLocations[][25], int *branchdist, int Branchdistances[]) {
  while (1) {

    printf("\nEnter your choice of branch: ");
    while (getchar() != '\n');
    fgets(branch, sizeof(branch), stdin);
    branch[strcspn(branch, "\n")] = '\0';
    if (strlen(branch) != 0) {
      for (int i = 0; branch[i] != '\0'; i++) {
        branch[i] = tolower(branch[i]);
        if (i == 0 || branch[i - 1] == ' ')
          branch[i] = toupper(branch[i]);
      }
      int found = 0;
      for (int i = 0; i < 4; i++) {
        if (strcmp(BranchLocations[i], branch) == 0) {
          *branchdist = Branchdistances[i];// Storing distance of chosen branch from user location
          found = 1;
          break;
        }
      }

      if (found == 0) {
        printf("Enter a valid branch\n");
        continue;
      }
      return branch;
    }
  }
}

int driverselection(char branch[]) {
  // Arrays to store driver details
  float driver_rating[10];
  int driver_index[10];
  char driver_name[10][20];
  char driver_ph[10][20];
  int driver_loc[10];
  char DriverLocations[10][25];

  // Read driver ratings from file
  FILE *file = fopen("review_driver.txt", "r");
  for (int i = 0; i < 10; i++) {
    int temp;
    fscanf(file, "%f %d", &driver_rating[i], &temp);
    driver_index[i] = i; // Store driver indices
  }
  fclose(file);
  // Read driver details (name, phone number, current location)
  file = fopen("Driverdetails.txt", "r");
  for (int i = 0; i < 10; i++) {
    fscanf(file, "%s %s %d", driver_name[i], driver_ph[i], &driver_loc[i]);
    strcpy(DriverLocations[i], D_Locations[driver_loc[i]]);
  } 
  fclose(file);

  // Find the index of the source location (branch)
  int source = -1;
  for (int i = 0; i < MAX; i++) {
    if (strcmp(branch, D_Locations[i]) == 0) {
      source = i;
      break;
    }
  }

  if (source != -1) {
    // Run Dijkstra's algorithm to find shortest paths from branch to all locations
    Dijkstra(Graph, MAX, source, d_distance, D_Locations);

    // Calculate review scores for all drivers based on distance and rating
    float scores[10];
    for (int i = 0; i < 10; i++) {
      if (driver_loc[i] >= 0 && driver_loc[i] < MAX) {
        scores[i] =
            0.4 * (5.0 - driver_rating[i]) + 0.6 * d_distance[driver_loc[i]];
      } else {
        scores[i] =INFINITY; 
      }
    }

    // Find the index of the driver with the minimum score
    int min_index = -1;
    float min_score = INFINITY;
    for (int i = 0; i < 10; i++) {
      if (scores[i] < min_score) {
        min_score = scores[i];
        min_index = i;
      }
    }

    
    if (min_index != -1) {
      // Print details of the selected driver
      printf("\nDriver details:\n");
      printf("Driver name: %s\nPhone Number: %s\nRatings: %.1f\nDriver Current "
             "location: %s\n",
             driver_name[min_index], driver_ph[min_index],
             driver_rating[min_index], DriverLocations[min_index]);

      return min_index; // Return the index of the selected driver
    } else {
      printf("\nNo valid driver found.\n");
      return -1; 
    }
  } else {
    printf("\nInvalid branch location.\n");
    return -1; 
  }
}
// Updating drivers current location to user location
int driverlocchange(int index) {
  int driver_index;
  FILE *fp1 = fopen("Driverdetails.txt", "r");// Reading driver details from file
  FILE *fp2 = fopen("Temp.txt", "w");
  char ph_num[10];
  int loc;
  char name[20];
  for (int i = 0; i < 10; i++) {
    fscanf(fp1, "%s %s %d", name, ph_num, &loc);
    if (i == index) {
      driver_index = i;
      loc = source;// Updating location index
    }
    fprintf(fp2, "%s %s %d\n", name, ph_num, loc);
  }
  fclose(fp1);
  fclose(fp2);
  remove("Driverdetails.txt");
  rename("Temp.txt", "Driverdetails.txt");
  return driver_index; // Returning position of the driver in the file
}
