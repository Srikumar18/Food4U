#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define max 100
typedef struct{
  char name[32];
  char username[32];
  char password[32]; 
  char pno[11];
  char emailid[32];
} Userdet;

Userdet Newuserdet;
//handling registration of new user
char * registration(){
  FILE *fp;
  fp=fopen("Userdetails.csv","r");
  if (!fp)
    return NULL;
  while (1){
    char name[32];
    printf("Enter your name: ");
    scanf("%s",name);
    int flag=0;
    for (int i=0;i<strlen(name);i++){
      if (isalpha(name[i])==0){
        printf("Invalid Entry. Numbers not allowed\nTry again\n");
        flag=1;
        break;
      }
    }
    if (flag==0){
      strcpy(Newuserdet.name,name);
      break;
    }
  }
//validation of username
  while (1){
    char uname[32];
    printf("Enter your username: ");
    scanf("%s",uname);
    int i = 0;
    char cred[max];
    char arr[max][20];
    while (fgets(cred, max, fp) != NULL) {
      char *det = strtok(cred, ",");
      while (det != NULL) {
        strcpy(arr[i], det);
        det = strtok(NULL, ",");
        i++;
      }
    }
    int lenarr = sizeof(arr) / sizeof(arr[0]);
    int flag = 0;
    for (int i = 1; i < lenarr - 1; i += 5) {
      if (strcmp(uname, arr[i])== 0) {
        printf("Username already exists. Try again\n");
        flag = 1;
        break;
      }
    }
    if (flag == 0){
      strcpy(Newuserdet.username,uname);
      break;
    }
  }
  //phone number validation-checking 10 digits
  while(1){
    char pno[20];
    char pno_str[11];
    int flag=0;
    printf("Enter phone number: ");
    scanf("%s",pno); 
    for (int i=0; pno[i]; i++){
    if (strlen(pno)!=10 || isdigit(pno[i])==0) {
      flag=1;
      break;
    }
    }
    if (flag==0){
        strcpy(Newuserdet.pno,pno);
        break;
    }
    else
      printf("Invalid phone number. Try again\n");
  }
  //email validation-checking @,.com 
  while (1){
  char emailid[32];
  printf("Enter your emailid: ");
  scanf("%s",emailid);
  int count=0;
  for(int i=0;emailid[i]!='\0';i++){
    if(emailid[i]=='@'|| emailid[i]=='.'){
      count++ ;
      
    }
  } 
  if(count==2 && strlen(emailid)>=5){
    strcpy(Newuserdet.emailid,emailid);
    break;
  }
  else{
      printf("Invalid mail id.Try again\n");
    }
  }
  //password validation
  printf("Password requirements\n* Must be atleast 8 characters long \n* Must contain atleast 1 uppercase character\n* Must contain atleast 1 number\n* Must contain atleast 1 special character\n");
  while (1){
    char pwd[32];
    char pwd_c[32];
    printf("Enter your password: ");
    scanf("%s",pwd);
    
      if (strlen(pwd)>=8){
        int up=0;
        int spl=0;
        int num=0;
        for (int i=0;i<strlen(pwd);i++){
          if (isupper(pwd[i])!=0)
            up+=1;
          if (isdigit(pwd[i])!=0)
            num+=1;
          if (pwd[i]=='!'||pwd[i]=='@'||pwd[i]=='#'||pwd[i]==';'||pwd[i]=='*')
            spl+=1;
        }
        //three time wrong password check
        if (up>=1 && num>=1 && spl>=1){
          printf("Confirm your password: ");
          scanf("%s",pwd_c);
          if (strcmp(pwd, pwd_c)==0){
            strcpy(Newuserdet.password,pwd);
            break;
          }
          else
            printf("Password does not match. Try again\n");
        }
      else{
          printf("Password is not strong enough. Try again\n");
        }
      }
      else
        printf("Password must be atleast 8 characters\n");
   
  
  }
  fclose(fp);
  fp = fopen("Userdetails.csv", "a");
  if (!fp)
    return NULL;

  fprintf(fp, "%s,%s,%s,%s,%s\n", Newuserdet.name,Newuserdet.username,Newuserdet.password,Newuserdet.emailid,Newuserdet.pno);
  fflush(fp);
  printf("Successfully registered!!\n");
  FILE *fip=fopen("coupons.txt","a");
  fprintf(fip,"%s %d\n",Newuserdet.username,0);
  fclose(fip);
  printf("Welcome, %s\n",Newuserdet.name);

  FILE *fch=fopen("custchurn.txt","a");
  fprintf(fch,"%s %d\n",Newuserdet.username,0);
  fclose(fch);
  return Newuserdet.username;
}
