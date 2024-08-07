#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void showMenu();
void placeOrder();
void getCustomerDetails(char *name, char *address, char *contact);

typedef struct {
    char name[30];
    float price;
} Item;

Item menu[] = {
    {"Espresso", 2.50},
    {"Cappuccino", 3.00},
    {"Latte", 3.50},
    {"Chicken Sandwich", 5.00},
    {"Veggie Sandwich", 4.50},
    {"Ham Sandwich", 5.50},
    {"French Fries", 2.00},
    {"Onion Rings", 2.50},
    {"Muffin", 1.50}
};

int main() {
	
    while (1) {
        showMenu();
        placeOrder();
        printf("Press Enter to continue to the menu for the next customer...\n");
        getchar(); // wait for user to press Enter
        getchar(); // clear the newline character from buffer
    }
    return 0;
}

void showMenu() {
	int i;
    printf("----- Menu -----\n");
    for ( i = 0; i < sizeof(menu) / sizeof(menu[0]); i++) {
        printf("%d. %s - $%.2f\n",  menu[i].name, menu[i].price);
    }
    printf("----------------\n");
}

void placeOrder() {
    int choice, quantity;
    float total = 0.0;
    char another;

    char customerName[50];
    char customerAddress[100];
    char customerContact[12]; // 11 digits + null terminator

    getCustomerDetails(customerName, customerAddress, customerContact);

    do {
        printf("Enter the item number to order: ");
        scanf("%d", &choice);
        if (choice < 1 || choice > sizeof(menu) / sizeof(menu[0])) {
            printf("Invalid choice, please try again.\n");
            continue;
        }

        printf("Enter quantity: ");
        scanf("%d", &quantity);

        total += menu[choice - 1].price * quantity;
        printf("Do you want to order another item? (y/n): ");
        scanf(" %c", &another);

    } while (another == 'y' || another == 'Y');

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("----- Bill -----\n");
    printf("Customer Name: %s\n", customerName);
    printf("Customer Address: %s\n", customerAddress);
    printf("Customer Contact: %s\n", customerContact);
    printf("Date and Time: %02d-%02d-%d %02d:%02d:%02d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("Total: $%.2f\n", total);
    printf("----------------\n");
}

void getCustomerDetails(char *name, char *address, char *contact) {
    printf("Enter your name: ");
    getchar(); // clear the newline character from buffer
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = '\0'; // remove newline character

    printf("Enter your address: ");
    fgets(address, 100, stdin);
    address[strcspn(address, "\n")] = '\0'; // remove newline character

    do {
        printf("Enter your contact number (max 11 digits): ");
        fgets(contact, 12, stdin);
        contact[strcspn(contact, "\n")] = '\0'; // remove newline character
    } while (strlen(contact) > 11);
}

