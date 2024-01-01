#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct User{
	char NIK[15];
	char Name[100];
	char email[100];
	char nomor_telepon[13];
	char status[10];
};

int check_user(char Email[], char notelepon[]){
	struct User users[100];
	FILE *file = fopen("user.txt", "r");
	
	char line[1000];
	int rows = 0;
	if(file != NULL){
		if (fgets(line, sizeof(line), file) == NULL) {
        	printf("There's no Data'\n");
        	fclose(file);
        	return -1;
        }
        
        int found;
        do {
        	fgets(line, sizeof(line), file);
        	int read = sscanf(line, "%14[^,],%99[^,],%99[^,],%12[^,],%[^\n]", users[rows].NIK, users[rows].Name, users[rows].email,
								users[rows].nomor_telepon, users[rows].status);

        	if (read != 5) {
            	printf("Invalid Data Format\n");
            	fclose(file);
            	return -1;
			}
			
			if((strcmp(users[rows].email, Email) == 0) && (strcmp(users[rows].nomor_telepon, notelepon) == 0) &&
				(strcmp(users[rows].status, "Admin") == 0)){
				return 2;
			}else if((strcmp(users[rows].email, Email) == 0) && (strcmp(users[rows].nomor_telepon, notelepon) == 0) &&
				(strcmp(users[rows].status, "Dokter") == 0)){
				return 3;
			}else if((strcmp(users[rows].email, Email) == 0) && (strcmp(users[rows].nomor_telepon, notelepon) == 0)){
				return 1;
			}
			else rows++;
        	
    	} while (!feof(file));
    	
    	return 0;
    	
    }else
		printf("Error in reading the data!\n");
		return -1;
	
}

void register_data(struct User user, int choice){
	FILE *file = fopen("user.txt", "a");
	
	char line[1000];
	int rows = 0;
	if(file != NULL){
		if(choice == 1){
			fprintf(file, "\n%s,%s,%s,%s,%s", user.NIK, user.Name, user.email, user.nomor_telepon, "Pasien");	
		}
		else fprintf(file, "\n%s,%s,%s,%s,%s", user.NIK, user.Name, user.email, user.nomor_telepon, "Dokter");
		
		printf("Account has been added to the database.\n");
		fclose(file);	
		
    }else
    	printf("Error in reading the file\n");
    	return;
}

void delay(int seconds) {
    int i, j;
    for (i = 0; i < seconds; ++i) {
        for (j = 0; j < 100000000; ++j) {
            // Delay
        }
    }
}

void print(int choice){
	struct User users[100];
	FILE *file = fopen("user.txt", "r");
	
	char line[1000];
	int rows = 0;
	if(file != NULL){
		if (fgets(line, sizeof(line), file) == NULL) {
        	printf("There's no Data'\n");
        	fclose(file);
        }

        do {
        	fgets(line, sizeof(line), file);
        	int read = sscanf(line, "%14[^,],%99[^,],%99[^,],%12[^,],%[^\n]", users[rows].NIK, users[rows].Name, users[rows].email,
								users[rows].nomor_telepon, users[rows].status);

        	if (read != 5) {
            	printf("Invalid Data Format\n");
            	fclose(file);
			}
			
			rows++;
			
		} while(!feof(file));
		
        int found = 0;
		int match;
		int many = 0;
		
		for(int i = 0; i < rows; i++){
			switch(choice){
				case 1:
				{
					match = ((strcmp("Pasien", users[i].status)) == 0);
					break;
				}
				case 2:
				{
					match = ((strcmp("Dokter", users[i].status)) == 0);
					break;
				}
			}
			

			if(match){
				many++;
				if(!found){
					printf("\n============================================================================================\n");
					printf("%-5s|%-20s|%-20s|%-30s|%-20s\n", "ID", "Status", "Nama", "Email", "Nomor Telepon");
					printf("============================================================================================\n");
					found = 1;
				}
				
				printf("%-5d|%-20s|%-20s|%-30s|%-20s\n", many, users[i].status, users[i].Name, 
							users[i].email, users[i].nomor_telepon);
			}
		}
		
		if(!found) printf("There's no data\n");
		else printf("============================================================================================\n");
		
		
	}else printf("Error in reading the data!\n");
}

void menu_admin(){
	int choice;
	do{
		printf("==========\n");
		printf("Menu Admin\n");
		printf("==========\n");
		printf("1. Print Pasien Data\n");
		printf("2. Print Dokter Data\n");
		printf("3. Log Out\n");
		printf("Enter user choice >> ");
		scanf("%d", &choice);
		
		if (choice == 3){
			printf("You have succesfully log out!\n");
		}
		else if(choice == 1 || choice == 2){
			print(choice);
		}else printf("Invalid Choice");	
		
		if(choice != 3){
			printf("\nPress Enter to Continue....");
			getchar();
			getchar();
			system("cls");
		}
		
	}while(choice != 3);
	
}

int main(){
	
	int choice;
	do{
		printf("Welcome to Comver!\n");
		printf("1. Login\n");
		printf("2. Sign up\n");
		printf("3. Exit\n");
		printf("What do you want to do: ");
		scanf("%d", &choice);
		
		switch(choice){
			case 1:
			{
				char gmail[100];
				char pnumber[13];
				printf("Enter your Gmail: ");
				scanf("%s", gmail);
				printf("Enter your Phone Number: ");
				scanf("%s", pnumber);
				int z = check_user(gmail,pnumber);
				
				if(z == 2){
					printf("You have log in as an admin.");
					delay(10);
					system("cls");
					menu_admin();
				}else if(z == 3){
					printf("You have log in as a doctor.\n");
				}else if(z == 1){
					printf("You have log in as a pasient\n");
				}else if(z == 0){
					printf("You don't have an account yet.\n");
				}
				
				break;
			}
			
			case 2:
			{
				struct User users;
				int choice1;
				
				while(1){
					printf("Enter your NIK: ");
					scanf("%s", users.NIK);
					printf("Enter your Nama: ");
					scanf(" %[^\n]", users.Name);
					printf("Enter your Email: ");
					scanf("%s", users.email);
					printf("Enter your Nomor Telepon: ");
					scanf("%s", users.nomor_telepon);
					printf("Register Choiec\n");
					printf("1. Pasien\n");
					printf("2. Dokter\n");
					printf("What do you want to register for: ");
					scanf("%d", &choice1);
					
					if(choice1 == 1 || choice1 == 2){
						register_data(users, choice);
						break;
					}else {
						printf("Not one of the choice!\n");
						delay(10);
						system("cls");
						continue;	
					}
				}	
				break;
			}
			
			case 3:{
				printf("\nYou are exiting Comver....\n");
				printf("Thank you for visiting Comver\n");
				break;
			}
			
			default:
			{
				printf("Invalid Input\n");
				break;
			}
		}
		
		if(choice != 3){
			printf("\nEnter to continue....");
			getchar();
			getchar();
			system("cls");
		}
		
	}while(choice != 3);
	
	return 0;
}
