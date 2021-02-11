#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fName[20];
    char lName[20];
    int id;
    double balance;
} User;

int cmpID(const void* p1, const void* p2);          
int cmpBalance(const void* p1, const void* p2);
int cmpFName(const void* p1, const void* p2);
int cmpLName(const void* p1, const void* p2); 

void enterInfo(User* users, int numUsers);
void printUsers(User* users, int numUsers);
int askNumUsers();
int printMenu();

int main() {

    int numUsers = askNumUsers();
    
    User* users = malloc(numUsers * sizeof(User));
    if (users == NULL) {
        return 0;
    }

    enterInfo(users, numUsers);
    do {
        switch (printMenu()) {
        case 1:
            qsort(users, numUsers, sizeof(User), cmpFName);
            printf("\nSorted by First Name\n");
            break;
        case 2:
            qsort(users, numUsers, sizeof(User), cmpLName);
            printf("\nSorted by Last Name\n");
            break;
        case 3:
            qsort(users, numUsers, sizeof(User), cmpID);
            printf("\nSorted by Student ID\n");
            break;
        case 4:
            qsort(users, numUsers, sizeof(User), cmpBalance);
            printf("\nSorted by Balance\n");
            break;
        case 5:
            printf("\nExiting...\n");
            free(users);
            exit(0);
        }
        printf("--------------------\n");
        printUsers(users, numUsers);
    } while (1);
}
//--------------END OF MAIN--------------//

int cmpID(const void* p1, const void* p2) {
    if (((User*)p1)->id < ((User*)p2)->id) return -1;
    if (((User*)p1)->id == ((User*)p2)->id) return 0;
    return 1;
}

int cmpBalance(const void* p1, const void* p2) {
    if (((User*)p1)->balance < ((User*)p2)->balance) return -1;
    if (((User*)p1)->balance == ((User*)p2)->balance) return 0;
    return 1;
}

int cmpFName(const void* p1, const void* p2) {
    const char* fN1 = ((User*)p1)->fName;
    const char* fN2 = ((User*)p2)->fName;
    return strcmp(fN1, fN2);
}

int cmpLName(const void* p1, const void* p2) {
    const char* lN1 = ((User*)p1)->lName;
    const char* lN2 = ((User*)p2)->lName;
    return strcmp(lN1, lN2);
}

int printMenu() {
    int option;
    do {
        printf("Sort Users By:\n--------------\n"
            "1: First Name\n"
            "2: Last Name\n"
            "3: User ID\n"
            "4: Balance\n"
            "5: Exit\n\n");

        char buf[20];
        if (!fgets(buf, 20, stdin)) {
            return 1;        
        }
        option = atoi(buf);   

        if (option == 1 || option == 2 || option == 3 || option == 4 || option == 5) {
            return option;
        }
        printf("\nInvalid Selection. Try again.\n\n");
    } while (1); 
}

int askNumUsers() {
    int numUsers;
    do {
        char buf[20];
        printf("Enter Number of Users to Register: ");
        if (!fgets(buf, 20, stdin)) {
            return 1;
        }
        numUsers = atoi(buf);
    } while (numUsers == 0); 
    return numUsers;
   }

void enterInfo(User* users, int numUsers) {
    for (int i = 0; i < numUsers; i++) {
        printf("\nEnter First Name: ");
        
        if (fgets(users[i].fName, 20, stdin)){
            users[i].fName[strcspn(users[i].fName, "\n")] = 0;
        }
        printf("Enter Last Name: ");
        if (fgets(users[i].lName, 20, stdin)) {
            users[i].lName[strcspn(users[i].lName, "\n")] = 0;
        }
        do {
            char buf[20];
            printf("Enter User ID: ");
            if (!fgets(buf, 20, stdin)) {
                continue;
            }
            users[i].id = atoi(buf);
        } while (users[i].id == 0); 
        do {
            char buf[20];
            printf("Enter Balance: ");
            if (!fgets(buf, 20, stdin)) {
                continue;
            }
            users[i].balance = atof(buf);
        } while (users[i].balance == 0); 
    }
    printf("\n");
}

void printUsers(User* users, int numUsers) {
    for (int i = 0; i < numUsers; i++) {
        printf("User Name: %s %s\nUser ID: %d\nBalance: %f\n\n",
            users[i].fName, users[i].lName, users[i].id, users[i].balance);
    }
}