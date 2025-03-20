#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define max 100
//change to lower case
char* lower(char str[32])
{
  for (int i = 0; str[i] != '\0'; i++){
    str[i] = tolower(str[i]);
  }
  return str;
}
//verification of username and password
int login(char uname[], char pwd[]) {
  char cred[max];
  char arr[max][20];
  FILE *fp = fopen("Userdetails.csv", "r");
  if (!fp) {
    return -1;
  }

  int num = 0;
  while (fgets(cred, max, fp) != NULL) {
    char *det = strtok(cred, ",");
    while (det != NULL) {
      strcpy(arr[num], det);
      det = strtok(NULL, ",");
      num++;
    }
  }
  
  int flag = 0;
  for (int i =1 ; strcmp("\0",arr[i]); i += 5) {
    if (strcmp(uname, arr[i]) == 0 && strcmp(pwd, arr[i + 1]) == 0) {
      printf("Welcome, %s\n", arr[i-1]);
      flag = 1;
      break;
    }
  }
  fclose(fp);
  return flag;
}
//deleting query after viewing
void delquer(int quernum){
  FILE *fque=fopen("queries.txt","r");
  char que_line[50][150];
  int rnum[50];
  int compno[50];
  int p=0;
  while(fscanf(fque, "%d %d %[^\n]",&compno[p],&rnum[p],que_line[p]) != EOF){
    p++;
  }
  fseek(fque,0,0);
  FILE *temp=fopen("Temp.txt","w");
  int lno=1;
  for (int i=0;i<p;i++){
    if (quernum==compno[i]){
      continue;
    }
    fprintf(temp,"%d %d %s\n",lno++,rnum[i],que_line[i]);
  }
  fclose(temp);
  fclose(fque);
  remove("queries.txt");
  rename("Temp.txt", "queries.txt");
}

