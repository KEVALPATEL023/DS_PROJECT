#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 5 

struct Item {
    int id;
    char name[50];
    int quantity;
    float price;
} ;

struct Item inventory[MAX_ITEMS];  
int count = 0;             

int isDuplicateID(int id) {
	int i;
    for (i = 0; i < count; i++) {
        if (inventory[i].id == id) {
            return 1;  
        }
    }
    return 0;
}

void insertItem() {
    int tempID, tempQuantity;
    float tempPrice;
    char tempName[50];

    if (count >= MAX_ITEMS) {
        printf("\e[0;31m\n\t=> Inventory is Full...!\n");
        return;
    }

    printf("Enter Item ID: ");
    while (scanf("%d", &tempID) != 1 || isDuplicateID(tempID)) {
        printf("\e[0;31mInvalid or duplicate ID! Enter a unique numeric ID: ");
        while (getchar() != '\n'); 
    }

    printf("\033[0mEnter Item Name: ");
    while (getchar() != '\n'); 
    fgets(tempName, sizeof(tempName), stdin);
    tempName[strcspn(tempName, "\n")] = 0; 

    printf("Enter Quantity: ");
    while (scanf("%d", &tempQuantity) != 1 || tempQuantity <= 0) {
        printf("\e[0;31mInvalid quantity! Enter a positive number:\033[0m ");
        while (getchar() != '\n');
    }

    printf("Enter Price: ");
    while (scanf("%f", &tempPrice) != 1 || tempPrice <= 0) {
        printf("\e[0;31mInvalid price! Enter a positive value: \033[0m");
        while (getchar() != '\n');
    }

    inventory[count].id = tempID;
    strcpy(inventory[count].name, tempName);
    inventory[count].quantity = tempQuantity;
    inventory[count].price = tempPrice;
    count++;

    printf("\e[0;33m\n\t=> Item added successfully!\033[0m\n");
}

void deleteItem() {
    int id, i, found = 0,j;
    if (count == 0) {
        printf("\e[0;31m\n\t=> Inventory is Empty..!!\n");
        return;
    }
    printf("||-> Enter Item ID to delete: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++) {
        if (inventory[i].id == id) {
            found = 1;
            for (j = i; j < count - 1; j++) {
                inventory[j] = inventory[j + 1];  
            }
            count--;
            printf("\e[0;33m\n\t=> Item deleted successfully..!!\n");
            break;
        }
    }
    if (found==0) {
        printf("\e[0;31m\n\t=> Item not found..!!\n");
    }
}

void searchItem() {
    int id, i;
    if (count == 0) {
        printf("\e[0;31m\n\t=> Inventory is Empty..!!\n");
        return;
    }
    printf("||-> Enter Item ID to search: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++) {
        if (inventory[i].id == id) {
            printf("\n***************************************\n");
            printf("*            \e[0;33mITEM FOUND!\033[0m              *\n");
            printf("***************************************\n");
            printf("ID : %d  \nNAME : %s  \nQUANTITY : %d  \nPRICE : %.2f  \n",inventory[i].id,inventory[i].name, inventory[i].quantity, inventory[i].price);
            printf("***************************************\n");
            return;
        }
    }
    printf("\e[0;31m\n\t=> Item not found..!!\n");
}

void updateItem() {
    int id, i, choice;

    if(count>0){
	    printf("||-> Enter Item ID to update: ");
    	scanf("%d", &id);
			
        for (i = 0; i < count; i++) {
            if (inventory[i].id == id) {
                printf("\tWhat do you want to update?\n\t1. Quantity\n\t2. Price\n\tChoice: ");
                scanf("%d", &choice);

                if (choice == 1) {
                    printf("Enter new quantity: ");
                    scanf("%d", &inventory[i].quantity);
                } else if (choice == 2) {
                    printf("Enter new price: ");
                    scanf("%f", &inventory[i].price);
                } else {
                    printf("\e[0;31m\n\t=> Invalid choice!\n");
                    return;
                }
                printf("\e[0;33m\n\t=> Item updated successfully..!!\n");
                return;
            }
        }
        printf("\e[0;31m\n\t=> Item not found..!!\n");
	}else{
        printf("\e[0;31m\n\t=> Inventory is Empty..!!\n");
    }

}

void displayInventory() {
	int i;
    if (count == 0) {
        printf("\e[0;31m\n\t=> Inventory is Empty..!!\n");
        return;
    }

    // printf("\n*****************************************\n");
    // printf("*         \e[0;33mINVENTORY LIST\033[0m                *\n");
    // printf("*****************************************\n");
    // printf("* %s | \t%s\t|  %s | \t%s  *\n", "ID", "Name", "Quantity", "Price");
    // printf("*****************************************\n");

    // for (i = 0; i < count; i++) {
    //     printf("* %d | \t%s\t| %d \t|     %.2f   *\n",
    //            inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);
    // }

    // printf("*****************************************\n");

    printf("\n=====================================================================================\n");
    printf("\033[1m\033[34m%50s\033[0m\n", "INVENTORY LIST");
    printf("=====================================================================================\n");
    printf("\033[33m%-10s %-25s %-15s %-15s\033[0m\n", "ID", "Name", "Quantity", "Price");
    printf("-------------------------------------------------------------------------------------\n");

    for (i = 0; i < count; i++) {
        printf("%-10d %-25s %-15d %-15.2f\n",
               inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);
    }

    printf("-------------------------------------------------------------------------------------\n");
}


void main() {
    int choice;
    while (1) {
        printf("\033[0m\n=========================================\n");
        printf("|       Inventory Management System     |\n");
        printf("=========================================\n");
        printf("| 1. Add Item                           |\n");
        printf("| 2. Delete Item                        |\n");
        printf("| 3. Search Item                        |\n");
        printf("| 4. Update Item                        |\n");
        printf("| 5. Display Inventory                  |\n");
        printf("| 6. Exit                               |\n");
        printf("=========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
				insertItem(); 
				break;
            case 2: 
				deleteItem(); 
				break;
            case 3: 
				searchItem();
				break;
            case 4: 
				updateItem(); 
				break;
            case 5: 
				displayInventory(); 
				break;
            case 6: 
				printf("\e[0;34mExiting...\033[0m\n"); 
				return;
            default: 
				printf("\e[0;31mInvalid choice! Try again.\n");
        }
    }
}


