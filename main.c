#include "menu.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// declaring all functions from other files
int login(char uname[], char pwd[]);
char *registration();
menu *init_menu();
carts cart;
char username[32];
int restscores[10];
int frec=0;
int freccheck[15];
extern char branch[15];
char location[25];
int branchdist;
char BranchLocations[4][25];
extern int Branchdistances[4];
char address[200];
int items[10];
void foodcsv(int items[],int len);

int main() {
    printf("Welcome to Food4U App - where all food is home food!\n\n");
    // Login or Registration prompt
    while (1) {
        int choice_lr;
        printf("1 - Login\n2 - Register\n\n");
        printf("Enter your choice of action: ");
        scanf("%d", &choice_lr);
        printf("\n");

        if (choice_lr == 1) {
            int flag = 0;
            int count = 0;
            for (; count < 3; count++) {
                char password[32];
                printf("Enter your username: ");
                scanf("%s", username);
                printf("Enter your password: ");
                scanf("%s", password);

                // Admin login check
                if ((strcmp(username, "Admin1") == 0 || strcmp(username, "Admin2") == 0) && (strcmp(password, "Adm1n") == 0)) {
                    FILE *fque = fopen("queries.txt", "r");
                    if (fque == NULL) {
                        printf("Error opening queries file.\n");
                        exit(1);
                    }
                    printf("***************** QUERIES ********************\n");
                    printf("Qno.\tRno.\tEmail id\t\t\tQuery\n");
                    char que_line[150];
                    int rnum[50];
                    int compno[50];
                    int p = 0;
                    // Reading and displaying queries
                    while (fscanf(fque, "%d %d %[^\n]", &compno[p], &rnum[p], que_line) != EOF) {
                        printf("%-4d\t%-4d\t%-s%s\n", compno[p], rnum[p], "", que_line);
                        p++;
                    }
                    fclose(fque);
                    // Marking queries as completed
                    while (1) {
                        printf("\nEnter the query number to mark as completed. Enter 0 to exit: ");
                        int quernum;
                        scanf("%d", &quernum);

                        if (quernum < 0 || quernum > p) {
                            printf("Invalid input. Please enter a valid query number.\n");
                            continue;
                        }
                        if (quernum == 0)
                            break;
                        // Function to delete query
                        delquer(quernum);
                      fque = fopen("queries.txt", "r");
                      while (fscanf(fque, "%d %d %[^\n]", &compno[p], &rnum[p], que_line) != EOF) {
                        printf("%-4d\t%-4d\t%-s%s\n", compno[p], rnum[p], "", que_line);
                        p++;
                      }
                      fclose(fque);
                    }
                    exit(0);
                }
                // Regular user login check
                flag = login(username, password);
                if (flag == 1) {
                    printf("Successfully logged in!\n");
                    break;
                } else if (flag == 0) {
                    printf("Invalid username and password. Please try again.\n");
                    continue;
                } else {
                    printf("Unexpected error occurred during login.\n");
                }
            }
            // Maximum login attempts reached
            if (count == 3) {
                printf("You have exceeded the maximum number of attempts.\n");
                printf("Redirecting to registration page...\n\n");
                registration();
            }
            break;
        } else if (choice_lr == 2) {
            strcpy(username, registration());
            break;
        } else {
            printf("Invalid Entry. Please try again.\n\n");
        }
    }

    // Checking for customer churn
    int churn = churncust(username);
    if (churn == 1) {
        printf("\n");
        printf("Welcome back! Enjoy a 10%% discount with any purchase today!\n");
    }

    // Entering and storing food preferences
    char *pref = preferences();
    int choice_fr;

    while (getchar() != '\n');
    printf("Enter your delivery address: ");
    fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\n")] = '\0';
    // Displaying all the available locations
    printf("\nLocations we cater to:\n");
    for (int i = 0; i < 30; i++) {
        printf("** %s\n", R_Locations[i]);
    }

    // Selecting delivery location
    while (1) {
        printf("Enter the location closest to you from the list: ");
        fgets(location, sizeof(location), stdin);
        location[strcspn(location, "\n")] = '\0';

        // Capitalizing location names
        for (int i = 0; location[i] != '\0'; i++) {
            location[i] = tolower(location[i]);
            if (i == 0 || location[i - 1] == ' ') {
                location[i] = toupper(location[i]);
            }
        }

        // Validating location
        int found = 0;
        for (int i = 0; i < 30; i++) {
            if (strcmp(R_Locations[i], location) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Invalid location. Please select a valid location.\n");
            continue;
        }
        break;
    }

    // Choosing action: Order by food or restaurant
    printf("\nEnter your choice of action:\n");
    printf("1 - Order by food\n");
    printf("2 - Order by restaurant\n");
    printf("Enter your choice: ");
    scanf("%d", &choice_fr);
    printf("\n");

    // Handling food or restaurant selection
    while (1) {
        if (choice_fr == 1) {
            cart = foodcart(cart, pref);
            if (cart.total == -1) {
                cart.total = 0;
                continue;
            }
            break;
        } else if (choice_fr == 2) {
            printf("Displaying restaurant names based on ratings:\n");
            printf("\n");
            printf("S.no\tRestaurant Name\t\t\t\tRcode\n");
            displayrest();
            int choice;
            printf("Enter your choice [Rcode]: ");
            scanf("%d", &choice);
            printf("\n");
            cart = restcart(cart, choice, pref);
            if (cart.total == -1) {
                cart.total = 0;
                continue;
            } else {
                break;
            }
        } else {
            printf("Invalid choice. Please enter 1 or 2.\n");
            printf("Enter your choice: ");
            scanf("%d", &choice_fr);
        }
    }

    // Recommending food items based on preferences
    int var = 0, m = 0, codeflag = 0, fcodee[10] = {0};
    char checkcode[10];
    int *fcoode = food_rec(cart, &var);
    if (var > 0) {
        printf("\nFood recommendations for you:\n");
        menu *rest = init_menu();
        int rno = fcoode[0] / 100;
        menu restc = rest[rno - 1];
        for (int i = 0; i < var; i++) {
            codeflag = 0;
            for (int j = 0; j < 10; j++) {
                if (fcoode[i] == restc.fcode[j]) {
                    codeflag = 1;
                    for (int k = 0; k < cart.count; k++) {
                        if (fcoode[i] == cart.code[k]) {
                            codeflag = 0;
                            break;
                        }
                    }
        //Checking user preferences and time constraints
                    if (codeflag == 1) {
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
                                if ((checkcode[2] == 'T' && (time_mod(1, 30, 4, 30) || time_mod(10, 30, 18, 30))) ||
                                    (checkcode[2] == 'M' && time_mod(4, 30, 8, 30)) ||
                                    (checkcode[2] == 'A')) {
                                    printf("%d. %-30s - Rs. %.2f\n", restc.fcode[j], restc.food_items[j], restc.price[j]);
                                    fcodee[m] = restc.fcode[j];
                                    m++;
                                }
                            } else if (pref[0] == 'X') {
                                if ((checkcode[2] == 'T' && (time_mod(1, 30, 4, 30) || time_mod(10, 30, 18, 30))) ||
                                    (checkcode[2] == 'M' && time_mod(4, 30, 8, 30)) ||
                                    (checkcode[2] == 'A')) {
                                    printf("%d. %-30s - Rs. %.2f\n", restc.fcode[j], restc.food_items[j], restc.price[j]);
                                    fcodee[m] = restc.fcode[j];
                                    m++;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (fcodee[0] > 0) {
            frec = 1;
            cart = init_cart(cart, restc, fcodee);
        } else {
            printf("No food recommendations available for your preferences.\n");
        }
    } else {
        printf("No food recommendations available for your preferences.\n");
    }

    // Editing cart options
    char choice_cc[4];
    int flag_cc = 0;
    while (flag_cc != 1) {
        printf("\nDo you want to edit your cart? <Yes/No>: ");
        scanf("%s", choice_cc);
        for (int i = 0; choice_cc[i] != '\0'; i++) {
            choice_cc[i] = toupper(choice_cc[i]);
        }

        if (strcmp(choice_cc, "YES") == 0) {
            while (1) {
                printf("Enter:\n");
                printf("1 - Add items\n");
                printf("2 - Remove items\n");
                printf("3 - Customize cart\n");
                printf("4 - Stop editing\n");
                printf("Enter your choice: ");
                int choice_ec;
                scanf("%d", &choice_ec);
                if (choice_ec == 1) {
                    cart = add(cart, pref);
                } else if (choice_ec == 2) {
                    if (cart.count == 0)
                        exit(0);
                    cart = del(cart);
                    displaycart(cart);
                    break;
                } else if (choice_ec == 3) {
                    if (cart.count == 0)
                        continue;
                    cart = customize(cart);
                } else if (choice_ec == 4) {
                    if (cart.count == 0)
                        exit(0);
                    while (1) {
                        char choice_oc[4];
                        printf("\nDo you wish to confirm your order? <Yes/No>: ");
                        scanf("%s", choice_oc);
                        for (int i = 0; choice_oc[i] != '\0'; i++) {
                            choice_oc[i] = toupper(choice_oc[i]);
                        }
                        if (strcmp(choice_oc, "YES") == 0) {
                            printf("Order Confirmed!\n");
                            for (int i = 0; i < cart.count; i++) {
                                items[i] = cart.code[i];
                            }
                            foodcsv(items, cart.count);
                            break;
                        } else if (strcmp(choice_oc, "NO") == 0) {
                            printf("Order Cancelled. Thank you for using Food4U app!\n");
                            exit(0);
                        } else {
                            printf("Invalid Entry. Please enter 'Yes' or 'No'.\n");
                        }
                    }

                    // Branch selection for delivery
                    restaurantdistance(location, cart.code[0] / 100, BranchLocations, Branchdistances);
                    strcpy(branch, branchselection(BranchLocations, &branchdist, Branchdistances));
                    printf("Branch Distance: %d km\n", branchdist);
                    if (branchdist > 10) {
                        printf("You may incur a delivery fee since the distance from your address is over 10 km.\n");
                        printf("Do you want to select a different branch? <Yes/No>: ");
                        char bsel[4];
                        scanf("%s", bsel);
                        for (int i = 0; bsel[i] != '\0'; i++) {
                            bsel[i] = toupper(bsel[i]);
                        }
                        if (strcmp(bsel, "YES") == 0) {
                                strcpy(branch, branchselection(BranchLocations, &branchdist, Branchdistances));
                                printf("Branch Distance: %d km\n\n", branchdist);     
                        }
                    }
                    // Printing bill and finalizing order
                    bill(username, cart);
                    flag_cc = 1;
                    break;
                } else {
                    printf("Invalid Entry. Please enter a number from 1 to 4.\n");
                }
            }
        } else if (strcmp(choice_cc, "NO") == 0) {
            if (cart.count == 0)
                exit(0);
            while (1) {
                printf("\n");
                char choice_oc[4];
                printf("Do you wish to confirm your order? <Yes/No>: ");
                scanf("%s", choice_oc);
                for (int i = 0; choice_oc[i] != '\0'; i++) {
                    choice_oc[i] = toupper(choice_oc[i]);
                }
                if (strcmp(choice_oc, "YES") == 0) {
                    printf("Order Confirmed!\n");
                    for (int i = 0; i < cart.count; i++) {
                        items[i] = cart.code[i];
                    }
                    foodcsv(items, cart.count);
                    break;
                    //Cancelling order
                } else if (strcmp(choice_oc, "NO") == 0) {
                    printf("Order Cancelled. Thank you for using Food4U app!\n");
                    exit(0);
                } else {
                    printf("Invalid Entry. Please enter 'Yes' or 'No'.\n");
                }
            }
            // Branch selection for delivery
            restaurantdistance(location, cart.code[0] / 100, BranchLocations, Branchdistances);
            strcpy(branch, branchselection(BranchLocations, &branchdist, Branchdistances));
            printf("Branch Distance: %d km\n", branchdist);
            if (branchdist > 10) {
                printf("\nYou may incur a delivery fee since the distance from your address is over 10 km.\n");
                printf("Do you want to select a different branch? <Yes/No>: ");
                char bsel[4];
                scanf("%s", bsel);
                for (int i = 0; bsel[i] != '\0'; i++) {
                    bsel[i] = toupper(bsel[i]);
                }
                if (strcmp(bsel, "YES") == 0) {
                        strcpy(branch, branchselection(BranchLocations, &branchdist, Branchdistances));
                        printf("Branch Distance: %d km\n\n", branchdist);  
                    }
                }

            // Printing bill and finalizing order
            bill(username, cart);
            break;
        } else {
            printf("Invalid Entry. Please enter 'Yes' or 'No'.\n");
        }
    }

    // Delivery details and final processes
    printf("Delivery details:\n");
    int source_index = driverselection(branch);
    int driver_index = driverlocchange(source_index);
    rest_rev(cart);// Restaurant review
    food_rev(cart);// Food review
    rest_que(username, cart);// Add queries
    driver_rev(driver_index);// Driver review
    printf("\nThank you for using Food4U app!\n");
    return 0;
}
