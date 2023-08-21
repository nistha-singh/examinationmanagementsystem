#include<stdio.h>
#include <sqlite3.h>
#include<string.h>
void add();
void delete();
void display();
void student_attendance();
void edit_eligibility();
void check_eligible_students();
void room_allotment();
int callback(void *, int, char **, char **);
sqlite3 *db;
char *err_msg = 0;
int select_callback = 1;    
int main(void) {
    int run=1;
    int option;
    printf("Welcome to our Examination Management System\n");
    printf("1 to add the detail of a student\n");
    printf("2 to delete the detail of a student\n");
    printf("3 to display all the details of students\n");
    printf("4 to monitor the student's attendance\n");
    printf("5 to set or edit the eligibility criteria\n");
    printf("6 to check the details of eligible students\n");
    printf("7 to allot rooms for the eligible students\n");
    printf("8 to exit this program\n");
    int rc = sqlite3_open("test.db", &db);
    char* sql = "CREATE TABLE IF NOT EXISTS Student(SRN TEXT, Name TEXT, Section TEXT, Subject1 INT, Subject2 INT, Subject3 INT, Subject4 INT, Subject5 INT, room allotment INT);";
         rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    while(run){
        scanf("%d",&option);
        switch(option){
            case 1: add();
            break;
            case 2: delete();
            break;
            case 3: display();
            break;
            case 4:student_attendance();
            break;
            case 5: edit_eligibility();
            break;
            case 6: check_eligible_students();
            break;
            case 7: room_allotment();
            break;
            case 8: run=0;
            sqlite3_close(db);
            break;
            default: printf("Invalid Option");
            break;
        }
        
    }
             
    return 0;
}

void add(){
    char srn[100];
    char name[100];
    char section[100];
    char Subject1[100];
    char Subject2[100];
    char Subject3[100];
    char Subject4[100];
    char Subject5[100];
    char room_allotment[100];
    
    printf("Enter the data as follows: SRN,Name,Section,Subject1,Subject2,Subject3,Subject4,Subject5,room allotment\n");
    scanf("%s",srn);
    scanf("%s",name);
    scanf("%s",section);
    scanf("%s",Subject1);
    scanf("%s",Subject2);
    scanf("%s",Subject3);
    scanf("%s",Subject4);
    scanf("%s",Subject5);
    scanf("%s",room_allotment);
    char prefix[1000] = "";
    strcat(prefix,"INSERT INTO Student VALUES('");
    strcat(prefix,srn);
    strcat(prefix,"','");
    strcat(prefix,name);
    strcat(prefix,"','");
    strcat(prefix,section);
    strcat(prefix,"',");
    strcat(prefix,Subject1);
    strcat(prefix,",");
    strcat(prefix,Subject2);
    strcat(prefix,",");
    strcat(prefix,Subject3);
    strcat(prefix,",");
    strcat(prefix,Subject4);
    strcat(prefix,",");
    strcat(prefix,Subject5);
    strcat(prefix,",");
    strcat(prefix,room_allotment);
    strcat(prefix,");");
  
  int rc = sqlite3_exec(db, prefix, 0, 0, &err_msg);
  printf("Added!\n");
}

void delete(){
    char srn[100];
    printf("Enter the SRN of the student record that you want to delete:");
    scanf("%s",srn);
    char prefix[1000] = "";
    strcat(prefix,"delete from Student where SRN='");
    strcat(prefix,srn);
    strcat(prefix,"';"); 
    int rc = sqlite3_exec(db,prefix,0,0,&err_msg);
    printf("Deleted!\n");
}

void display(){
    select_callback = 1;
    int rc = sqlite3_exec(db,"Select * from Student",callback,0,&err_msg);
    if(select_callback){
        printf("No student records are present in the system\n");
    }
}


int callback(void *NotUsed,int argc,char **argv,char **azColName){
    NotUsed = 0;
    select_callback=0;
    for (int i = 0; i < argc; i++) {
       // printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    if(strcmp(azColName[i],"room")==0){
        printf("%s\n",argv[i]);
        }
    else{
        printf("%s ",argv[i]);
        }
    }
    return 0;
}

void student_attendance(){
char checkpoint[100];
    printf("Enter the checkpoint:");
    scanf("%s",checkpoint);
    char prefix[1000] = "";
    strcat(prefix,"Select * from Student where Subject1<=");
    strcat(prefix,checkpoint);
    strcat(prefix," OR Subject2<=");
    strcat(prefix,checkpoint);
    strcat(prefix," OR Subject3<=");
    strcat(prefix,checkpoint);
    strcat(prefix," OR Subject4<="); 
    strcat(prefix,checkpoint);
    strcat(prefix," OR Subject5<=");
    strcat(prefix,checkpoint);
    strcat(prefix,";");
    select_callback = 1;
    int rc = sqlite3_exec(db,prefix,callback,0,&err_msg);
    if(select_callback){
        printf("No student records are present in the system\n");
    }
}

void edit_eligibility(){
char eligibility_criteria[50];
printf("Enter the eligibilty criteria:");
scanf("%s",eligibility_criteria);
FILE *filepointer = fopen("eligibility.txt","w");
fprintf(filepointer,"%s",eligibility_criteria);
fclose(filepointer);
}

void check_eligible_students(){

char checkpoint[100];
    FILE *filepointer = fopen("eligibility.txt","r");
fscanf(filepointer,"%s",checkpoint);
fclose(filepointer);
char prefix[1000] = "";
    strcat(prefix,"Select * from Student where Subject1<=");
    strcat(prefix,checkpoint);
    strcat(prefix," OR Subject2<=");
    strcat(prefix,checkpoint);
    strcat(prefix," OR Subject3<=");
    strcat(prefix,checkpoint);
    strcat(prefix," OR Subject4<="); 
    strcat(prefix,checkpoint);
    strcat(prefix," OR Subject5<=");
    strcat(prefix,checkpoint);
    strcat(prefix,";");
    select_callback = 1;
    int rc = sqlite3_exec(db,prefix,callback,0,&err_msg);
    if(select_callback){
        printf("No student records are present in the system\n");
    }    
}

void room_allotment(){
    int x=0;
}
