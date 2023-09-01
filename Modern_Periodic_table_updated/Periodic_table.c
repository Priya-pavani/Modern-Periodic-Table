#include <stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<string.h>

void gotoxy(int x, int y){
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

}

struct element{
    int atno;
    float atmass;
    char symb[4];
    char name[20];
    char block[20];
};

void addelement(FILE *fp){
    struct element e;

    system("cls");

    gotoxy(0,5);
    printf("\033[0;32m");
    printf(" ****************************************  Modern Periodic Table Application ******************************************");
    printf("\033[0m");
    gotoxy(0,10);
    printf("\033[0;32m");
    printf("***************************************Adding Elements to Modern Periodic Table  ********************************************\n\n\n\n\n");
    printf("\033[0m");
    
    printf("\t\t\tEnter atomic number of the element : ");
    scanf("%d", &e.atno);
    printf("\n\t\t\tEnter Name of the element : ");
    scanf("%s",e.name);
    printf("\n\t\t\tEnter symbol of the element : ");
    scanf("%s",e.symb);
    printf("\n\t\t\tEnter atomic mass of the element : ");
    scanf("%f", &e.atmass);
    printf("\n\t\t\tEnter block of the element : ");
    scanf("%s", e.block);

    fwrite(&e, sizeof(struct element), 1, fp);


}

void displayelements(FILE *fp) {
    struct element e;
    
    system("cls");
    gotoxy(2,3);
    printf("\033[0;32m");
    printf("######################################## Modern Periodic Table Application #############################################");
    printf("\033[0m");
    gotoxy(5,5);
    printf("\033[0;33m");
    printf("****************************************   Modern Periodic Table******************************************\n\n\n\n");
    printf("\033[0m");
    
    // Assuming each element is stored as binary data
    while (fread(&e, sizeof(struct element), 1, fp) == 1) {
        printf("\t\tAtomic Number: %d\n", e.atno);
        printf("\t\tName: %s\n", e.name);
        printf("\t\tSymbol: %s\n", e.symb);
        printf("\t\tAtomic Mass: %.2f\n", e.atmass);
        printf("\t\tBlock: %s\n\n", e.block);
    }
}

void display_as_table(FILE *fp){

    struct element e;
    system("cls");
    printf("\033[0;35m");
    printf("\n#############################################################   Modern Periodic Table Application   #######################################################");
    printf("\033[0;33m");
    printf("\n\n\n");
    printf("\n****************************************************   Displaying elements in a table in atomic number order   **************************************************");
    printf("\033[0m");
    printf("\n\n");
    printf("\nAtomic Number    \tElement Name   \t       \t Symbol             Atomic Mass             Block ");
    printf("\033[0;32m");
    printf("\n\n----------------------------------------------------------------------------------------------------------------------------------");
    printf("\n\033[0m");
    while(fread(&e,sizeof(struct element),1,fp) == 1){
        printf("\n    %-3d       \t\t   %-20s     %-3s              %-10f            %-8s",e.atno,e.name,e.symb,e.atmass,e.block);

    }
}

int  searchelement(int no, FILE *fp){
    struct element e;
    int flag = 0;
    system("cls");
    gotoxy(0,0);
    printf("\033[0;32m");
    printf("############################################## Modern Periodic Table Application #############################################");
    printf("\033[0m");
    gotoxy(5,5);
    printf("\033[0;33m");
    printf("****************************************   Result for given atomic number   ***********************************\n\n\n\n");
    printf("\033[0m");
    while (fread(&e, sizeof(struct element), 1, fp) == 1) {
        if (e.atno == no){

            flag = 1;
            printf("\t\tAtomic Number: %d\n", e.atno);
            printf("\t\tName: %s\n", e.name);
            printf("\t\tSymbol: %s\n", e.symb);
            printf("\t\tAtomic Mass: %.2f\n", e.atmass);
            printf("\t\tBlock: %s\n\n", e.block);
            return flag;
        }
    }
    if (flag == 0){
        printf("\t\t Sorry.............");
        printf("\n\t\t We haven't found the element with atomic number %d.",no);
    }
    return flag;
}


void delete(int no){
    FILE *original = fopen("Periodic_elements.txt", "rb");
    if (original == NULL){
        printf("\n\t\t Error in opening the file............");
        return;
    }
    FILE *temp = fopen("temporary.txt","wb");
    if (temp == NULL){
        printf("\n\n\t\tError in creating temporaty file ............");
        return;
    }
    struct element e;
    while(fread(&e,sizeof(struct element),1,original) == 1){

        if (no != e.atno){
            fwrite(&e,sizeof(struct element),1,temp);
        }
    }
    fclose(original);
    fclose(temp);
    remove("Periodic_elements.txt");
    rename("temporary.txt", "Periodic_elements.txt");
    printf("\n\n\t\t\t**************************** Element is deleted  ****************************.");


}

int search_by_name( char *nm, FILE  *fp){
    struct element e;
    int flag = 0;
    system("cls");
    gotoxy(0,0);
    printf("\033[0;32m");
    printf("############################################## Modern Periodic Table Application #############################################");
    printf("\033[0m");
    gotoxy(5,5);
    printf("\033[0;33m");
    printf("****************************************   Result for given atomic number   ***********************************\n\n\n\n");
    printf("\033[0m");
    
    while (fread(&e, sizeof(struct element), 1, fp) == 1) {
        if (strcmp(e.name, nm) == 0){

            flag = 1;
            printf("\t\tAtomic Number: %d\n", e.atno);
            printf("\t\tName: %s\n", e.name);
            printf("\t\tSymbol: %s\n", e.symb);
            printf("\t\tAtomic Mass: %.2f\n", e.atmass);
            printf("\t\tBlock: %s\n\n", e.block);
            return flag;
        }
    }
    if (flag == 0){
        printf("\t\t Sorry.............");
        printf("\n\t\t We haven't found the element with name %s.",nm);
    }
    return flag;

    

}

void update(int no, FILE *fp){
    FILE *fp1;
    fp1 = fopen("Periodic_elements.txt","rb+");
    int pos;
    struct element e;
    int res = searchelement(no,fp);
    fclose(fp);
    if (res){

        printf("\n\n********************************** Update the element details  *********************************************");
        while (fread(&e, sizeof(struct element), 1, fp1) == 1) {
        if (e.atno == no){

            
            printf("\n\t\t\tEnter atomic number of the element : ");
            scanf("%d", &e.atno);
            printf("\n\t\t\tEnter Name of the element : ");
            scanf("%s",e.name);
            printf("\n\t\t\tEnter symbol of the element : ");
            scanf("%s",e.symb);
            printf("\n\t\t\tEnter atomic mass of the element : ");
            scanf("%f", &e.atmass);
            printf("\n\t\t\tEnter block of the element : ");
            scanf("%s", e.block);
             
            fseek(fp1, pos, SEEK_SET);
                
            fwrite(&e, sizeof(struct element), 1, fp1);
            fclose(fp1);
            break;

        }
        pos = ftell(fp1);
    }
    }

}

// Main block

int main(){
system("cls");
printf("\033[0;32m");
printf("##############################################  Modern Periodic Table Application #############################################");
printf("\033[0m");
gotoxy(45,15);
printf("If you are an admin press '1' else '0': ");
int user;
int password;
int opinion;
int no;
char nm[20];
int choice;
int result;
scanf("%d",&user);



FILE *fp;
if (user == 1){
    printf("\n\t\t\t Please enter the password : ");
    scanf("%d",&password);
    if (password == 1234){
        printf("please wait while we direct to next page...........................");
        Sleep(2000);

        do{

        system("cls");
        gotoxy(0,0);
        printf("\033[0;32m");
        printf("##############################################  Modern Periodic Table Application #############################################");
        printf("\033[0m");
        gotoxy(45,5);
        printf("1)Add an element");
        gotoxy(45,7);
        printf("2)Delete an element");
        gotoxy(45,9);
        printf("3)Searching  an element by atomic number");
        gotoxy(45,11);
        printf("4)Searching an element by its name ");
        gotoxy(45,13);
        printf("5)Updating  an element");
        gotoxy(45,15);
        printf("6)Displaying all elements in list format");
        gotoxy(45,17);
        printf("7)Displaying all elements in table format");
        gotoxy(45,19);
        printf("8) Exit from the program");
        gotoxy(0,21);
        printf("\033[0;33m");
        printf("*****************************************************************************************************************************");
        printf("\033[0m");

        printf("\n  Please select an option : ");
        
        scanf("%d",&choice);

        printf("\033[0;33m");
        printf("\n*********************************    Please wait while we display your desired option  ********************************");
        printf("\033[0m");
        Sleep(1000);

        switch(choice){
            case 1 : fp = fopen("Periodic_elements.txt","ab");
                        addelement(fp);
                        fclose(fp);
                        printf("Element is successfully added");
                        Sleep(1000);
                        system("cls");
                        break;
            case 2 :     printf("\n\n\n Enter atomic number of the element that you want to delete : ");
                        scanf("%d",&no);
                        printf("\n\n\n You are going to delete the element with atomic number %d", no);
                        delete(no);
                        system("cls");
                        break;

            case 3 : fp =   fopen("Periodic_elements.txt","rb");
                            printf("\n\n\n\t\t\t\tEnter atomic number: ");
                            
                            scanf("%d",&no);
                            result = searchelement(no,fp);
                            if (result == 0)
                                printf("\n\n\nIf you want to add this element then please type '1' and next select '1', else '0' ");
                            else printf("\n\nIf you want to continue please select '1' else '0' to quit ......");
                            scanf("%d",&opinion);
                            if( opinion ){
                            system("cls");

                            }
                            else exit(0);
                            break;

            case 4 : fp =   fopen("Periodic_elements.txt","rb");
                            printf("\n\n\t\tWhile searching please enter first letter in capitals");
                            printf("\n\n\n\t\t\t\tEnter name of the element : ");
                            
                            scanf("%s",nm);
                            result = search_by_name(nm,fp);
                            if (result == 0)
                                printf("\n\n\nIf you want to add this element then please type '1' and next select '1', else '0' ");
                            else printf("\n\nIf you want to continue please select '1' else '0' to quit ......");
                            scanf("%d",&opinion);
                            if( opinion ){
                            system("cls");

                            }
                            else exit(0);
                            break;

            case 5 :        fp = fopen("Periodic_elements.txt","rb");
                            printf("\n\n\n\t\t\t\tEnter atomic number: ");
                            
                            scanf("%d",&no);
                            update(no,fp);
                            printf("\n\nElement record is updated ");
                            Sleep(1000);
                            system("cls");
                            break;
                            

            case 6 : fp = fopen("Periodic_elements.txt","rb");
                        displayelements(fp);
                        fclose(fp);
                        printf("\n\n\nIf you want to continue please type '1'else '0' ");
                        
                        scanf("%d",&opinion);
                        if( opinion ){
                            system("cls");

                        }
                        else exit(0);
                        break;
            case 7  :fp = fopen("Periodic_elements.txt", "rb");
                        display_as_table(fp);   
                        fclose(fp);
                        printf("\n\n\nIf you want to continue please type '1'else '0' ");
                        
                        scanf("%d",&opinion);
                        if( opinion ){
                            system("cls");

                        }
                        else exit(0);
                        break;  
                        
            case 8 : exit(0);



        }

        } while(1);
        system("pause");
    }

    else{ 
        printf("\033[0;31m");
         printf("\n\n\t\t You are either not an authenticated administrator or your password is wrong please type it correctly for next execution..........");
        printf("\033[0m");
        }
}

else{
        printf("\n\t\t\t\tYou are logging as a user. You have permission only to see the data...........");
        printf("\n\n\t\t\t\tPlease wait while redirecting.....................");
        Sleep(2000);
    do{

        system("cls");
        gotoxy(0,0);
        printf("\033[0;32m");
        printf("##############################################  Modern Periodic Table Application #############################################");
        printf("\033[0m");
        gotoxy(45,5);
        printf("1)Searching  an element by atomic number");
        gotoxy(45,7);
        printf("2)Searching an element by its name ");
        gotoxy(45,9);
        printf("3)Displaying all elements in list format");
        gotoxy(45,11);
        printf("4)Displaying all elements in table format");
        gotoxy(45,13);
        printf("5) Exit from the program");
        gotoxy(0,16);
        printf("\033[0;33m");
        printf("*****************************************************************************************************************************");
        printf("\033[0m");

        printf("\n  Please select an option : ");
        
        scanf("%d",&choice);

        printf("\033[0;33m");
        printf("\n*********************************    Please wait while we display your desired option  ********************************");
        printf("\033[0m");
        Sleep(1000);

        switch(choice){
            

            case 1 : fp =   fopen("Periodic_elements.txt","rb");
                            printf("\n\n\n\t\t\t\tEnter atomic number: ");
                            
                            scanf("%d",&no);
                            result = searchelement(no,fp);
                            if (result == 0)
                                printf("\n\n\nIf you want to add this element then please type '1' and next select '1', else '0' ");
                            else printf("If you want to continue please select '1' else '0' to quit ......");
                            scanf("%d",&opinion);
                            if( opinion ){
                            system("cls");

                            }
                            else exit(0);
                            break;

            case 2 : fp =   fopen("Periodic_elements.txt","rb");
                            printf("\n\n\t\tWhile searching please enter first letter in capitals");
                            printf("\n\n\n\t\t\t\tEnter name of the element : ");
                            
                            scanf("%s",nm);
                            result = search_by_name(nm,fp);
                            if (result == 0)
                                printf("\n\nIf you want to add this element then please contact admin...... ");
                            else printf("\n\nIf you want to continue please select '1' else '0' to quit ......");
                            scanf("%d",&opinion);
                            if( opinion ){
                            system("cls");

                            }
                            else exit(0);
                            break;
                            

            case 3 : fp = fopen("Periodic_elements.txt","rb");
                        displayelements(fp);
                        fclose(fp);
                        printf("\n\n\nIf you want to continue please type '1'else '0' ");
                        
                        scanf("%d",&opinion);
                        if( opinion ){
                            system("cls");

                        }
                        else exit(0);
                        break;
            case 4  : fp = fopen("Periodic_elements.txt", "rb");
                        display_as_table(fp);   
                        fclose(fp);
                        printf("\n\n\nIf you want to continue please type '1'else '0' ");
                        
                        scanf("%d",&opinion);
                        if( opinion ){
                            system("cls");

                        }
                        else exit(0);
                        break;  
                        
            case 5 : exit(0);



        }

        } while(1); 

    system("pause");


}



return 0;


}