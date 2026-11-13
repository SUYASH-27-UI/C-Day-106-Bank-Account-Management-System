
#include <stdio.h>
#include <string.h>

#define MAX 100
#define FILE_NAME "accounts.txt"

struct Account {
    int number;
    char name[50];
    float balance;
};

void saveAccounts(struct Account accounts[], int count) {
    FILE *fp = fopen(FILE_NAME, "w");

    if (fp == NULL) {
        printf("Error saving accounts!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d|%s|%.2f\n",
                accounts[i].number,
                accounts[i].name,
                accounts[i].balance);
    }

    fclose(fp);
}

int loadAccounts(struct Account accounts[]) {
    FILE *fp = fopen(FILE_NAME, "r");

    if (fp == NULL) {
        return 0;
    }

    int count = 0;

    while (count < MAX &&
           fscanf(fp, "%d|%49[^|]|%f",
                  &accounts[count].number,
                  accounts[count].name,
                  &accounts[count].balance) == 3) {
        count++;
    }

    fclose(fp);
    return count;
}

int findAccount(struct Account accounts[], int count, int number) {
    for (int i = 0; i < count; i++) {
        if (accounts[i].number == number) {
            return i;
        }
    }

    return -1;
}

void createAccount(struct Account accounts[], int *count) {
    if (*count >= MAX) {
        printf("Account limit reached!\n");
        return;
    }

    int number;

    printf("Enter Account Number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input!\n");
        return;
    }

    if (findAccount(accounts, *count, number) != -1) {
        printf("Account number already exists!\n");
        return;
    }

    accounts[*count].number = number;

    printf("Enter Account Holder Name: ");
    scanf(" %49[^\n]", accounts[*count].name);

    accounts[*count].balance = 0.0;

    (*count)++;
    saveAccounts(accounts, *count);

    printf("Account created successfully!\n");
}

void displayAccounts(struct Account accounts[], int count) {
    if (count == 0) {
        printf("No accounts found.\n");
        return;
    }

    printf("\n--- All Bank Accounts ---\n");

    for (int i = 0; i < count; i++) {
        printf("\nAccount Number: %d\n", accounts[i].number);
        printf("Holder Name: %s\n", accounts[i].name);
        printf("Balance: Rs. %.2f\n", accounts[i].balance);
    }
}

void searchAccount(struct Account accounts[], int count) {
    int number;

    printf("Enter Account Number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input!\n");
        return;
    }

    int index = findAccount(accounts, count, number);

    if (index == -1) {
        printf("Account not found.\n");
        return;
    }

    printf("\nAccount Number: %d\n", accounts[index].number);
    printf("Holder Name: %s\n", accounts[index].name);
    printf("Balance: Rs. %.2f\n", accounts[index].balance);
}

void depositMoney(struct Account accounts[], int count) {
    int number;
    float amount;

    printf("Enter Account Number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input!\n");
        return;
    }

    int index = findAccount(accounts, count, number);

    if (index == -1) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter Deposit Amount: ");
    if (scanf("%f", &amount) != 1 || amount <= 0) {
        printf("Enter a valid positive amount!\n");
        return;
    }

    accounts[index].balance += amount;
    saveAccounts(accounts, count);

    printf("Amount deposited successfully!\n");
    printf("New Balance: Rs. %.2f\n", accounts[index].balance);
}

void withdrawMoney(struct Account accounts[], int count) {
    int number;
    float amount;

    printf("Enter Account Number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input!\n");
        return;
    }

    int index = findAccount(accounts, count, number);

    if (index == -1) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter Withdrawal Amount: ");
    if (scanf("%f", &amount) != 1 || amount <= 0) {
        printf("Enter a valid positive amount!\n");
        return;
    }

    if (amount > accounts[index].balance) {
        printf("Insufficient balance!\n");
        return;
    }

    accounts[index].balance -= amount;
    saveAccounts(accounts, count);

    printf("Withdrawal successful!\n");
    printf("Remaining Balance: Rs. %.2f\n",
           accounts[index].balance);
}

int main() {
    struct Account accounts[MAX];
    int count = loadAccounts(accounts);
    int choice;

    while (1) {
        printf("\n===== BANK ACCOUNT MANAGEMENT =====\n");
        printf("1. Create Account\n");
        printf("2. Display All Accounts\n");
        printf("3. Search Account\n");
        printf("4. Deposit Money\n");
        printf("5. Withdraw Money\n");
        printf("6. Exit\n");
        printf("Enter Choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Restart the program.\n");
            break;
        }

        switch (choice) {
            case 1:
                createAccount(accounts, &count);
                break;
            case 2:
                displayAccounts(accounts, count);
                break;
            case 3:
                searchAccount(accounts, count);
                break;
            case 4:
                depositMoney(accounts, count);
                break;
            case 5:
                withdrawMoney(accounts, count);
                break;
            case 6:
                printf("Thank you for using the Bank System!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
