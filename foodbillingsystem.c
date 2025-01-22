#include <stdio.h>
void displayMenu();
float calculateBill(int itemCode, int quantity);
int main() {
    int itemCode, quantity;
    char choice;
    float totalBill = 0;

    printf("Welcome to the Food Billing System!\n\n");

    do {
        displayMenu();
        printf("\nEnter the code of the food item you want to order: ");
        scanf("%d", &itemCode);
        printf("Enter the quantity: ");
        scanf("%d", &quantity);
        totalBill += calculateBill(itemCode, quantity);
        printf("\nDo you want to order more? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');
    printf("\nYour total bill is: %.2f\n", totalBill);
    printf("Thank you for visiting!\n");

    return 0;
}
void displayMenu() {
    printf("Menu:\n");
    printf("1. Burger       - Rs5.00\n");
    printf("2. Pizza        - Rs8.00\n");
    printf("3. Sandwich     - Rs4.00\n");
    printf("4. Pasta        - Rs7.00\n");
    printf("5. Cold Drink   - Rs2.00\n");
}
float calculateBill(int itemCode, int quantity) {
    float price = 0;
    switch (itemCode) {
        case 1: price = 5.00; break;
        case 2: price = 8.00; break; 
        case 3: price = 4.00; break; 
        case 4: price = 7.00; break; 
        case 5: price = 2.00; break; 
        default:
            printf("Invalid item code! Please select a valid item.\n");
            return 0;
    }

    return price * quantity; 
}
