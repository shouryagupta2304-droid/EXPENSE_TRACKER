
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

// Store details of one expense
struct Expense {
    int category;
    long long amount;
};

// Array of structures
struct Expense expenses[MAX];

int count = 0;
long long budget = 0;
int budgetSet = 0;

// Category names
const char *categories[] = {
    "Food", "Travel", "Shopping",
    "Stationery", "Others"
};

// Read a whole number safely
long long readNumber() {
    char line[100];
    char extra;
    long long number;

    while (1) {
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nInput closed. Goodbye!\n");
            exit(0);
        }

        // Reject lines that are too long
        int i = 0;
        while (line[i] != '\0' && line[i] != '\n')
            i++;

        if (line[i] != '\n') {
            int ch;
            while ((ch = getchar()) != '\n' &&
                   ch != EOF) {
            }

            printf("Invalid input! Enter a whole number: ");
            continue;
        }

        // Accept only one integer
        if (sscanf(line, " %lld %c",
                   &number, &extra) == 1) {
            return number;
        }

        printf("Invalid input! Enter a whole number: ");
    }
}

// Calculate total spending
long long totalExpenses() {
    long long total = 0;

    for (int i = 0; i < count; i++) {
        total += expenses[i].amount;
    }

    return total;
}

// Feature 1: Set monthly budget
void setBudget() {
    printf("\nEnter monthly budget (Rs.): ");
    long long amount = readNumber();

    if (amount <= 0 || amount > 1000000000LL) {
        printf("Invalid budget! Enter Rs. 1 to 1000000000.\n");
        return;
    }

    budget = amount;
    budgetSet = 1;

    printf("SUCCESS: Monthly budget set to Rs. %lld\n",
           budget);
}

// Feature 2: Add expense
void addExpense() {
    if (!budgetSet) {
        printf("Please set your monthly budget first!\n");
        return;
    }

    if (count >= MAX) {
        printf("Storage full! Maximum 100 expenses.\n");
        return;
    }

    printf("\n--- SELECT CATEGORY ---\n");
    for (int i = 0; i < 5; i++) {
        printf("%d. %s\n", i + 1, categories[i]);
    }

    printf("Enter category number: ");
    long long category = readNumber();

    if (category < 1 || category > 5) {
        printf("ERROR: Invalid category!\n");
        return;
    }

    printf("Enter expense amount (Rs.): ");
    long long amount = readNumber();

    if (amount <= 0 || amount > 1000000000LL) {
        printf("ERROR: Expense must be between Rs. 1 and Rs. 1000000000!\n");
        return;
    }

    // Prevent overflow when adding totals
    if (totalExpenses() > LLONG_MAX - amount) {
        printf("ERROR: Expense total is too large!\n");
        return;
    }

    expenses[count].category = (int)category;
    expenses[count].amount = amount;
    count++;

    printf("SUCCESS: Expense recorded!\n");
    printf("Category: %s\n", categories[category - 1]);
    printf("Amount: Rs. %lld\n", amount);
}

// Feature 3: View expenses
void viewExpenses() {
    if (count == 0) {
        printf("\nNo expenses recorded.\n");
        return;
    }

    printf("\n----------- EXPENSE HISTORY -----------\n");
    printf("%-5s %-15s %-12s\n",
           "No.", "Category", "Amount");
    printf("---------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-5d %-15s Rs. %-10lld\n",
               i + 1,
               categories[expenses[i].category - 1],
               expenses[i].amount);
    }

    printf("---------------------------------------\n");
    printf("Total Expenses: Rs. %lld\n",
           totalExpenses());
}

// Feature 4: Category summary
void categorySummary() {
    printf("\n------- CATEGORY-WISE SUMMARY -------\n");

    for (int c = 1; c <= 5; c++) {
        long long sum = 0;

        for (int i = 0; i < count; i++) {
            if (expenses[i].category == c) {
                sum += expenses[i].amount;
            }
        }

        printf("%-15s : Rs. %lld\n",
               categories[c - 1], sum);
    }

    printf("-------------------------------------\n");
    printf("Total Spending : Rs. %lld\n",
           totalExpenses());
}

// Feature 5: Remaining balance
void checkBalance() {
    if (!budgetSet) {
        printf("Please set your monthly budget first!\n");
        return;
    }

    long long spent = totalExpenses();
    long long remaining = budget - spent;

    printf("\n--------- BUDGET REPORT ---------\n");
    printf("Monthly Budget : Rs. %lld\n", budget);
    printf("Total Expenses : Rs. %lld\n", spent);
    printf("Remaining      : Rs. %lld\n", remaining);

    if (remaining < 0) {
        printf("You have exceeded your budget by Rs. %lld!\n",
               -remaining);
    }

    printf("---------------------------------\n");
}

// Feature 6: Budget alert
void budgetAlert() {
    if (!budgetSet) {
        printf("Please set your monthly budget first!\n");
        return;
    }

    long long spent = totalExpenses();

    double percentage =
        ((double)spent / budget) * 100.0;

    printf("\n---------- BUDGET ALERT ----------\n");
    printf("Budget Used: %.2f%%\n", percentage);

    if (spent > budget) {
        printf("ALERT: You have overspent your budget!\n");
    }
    else if (spent == budget) {
        printf("WARNING: Your budget is fully exhausted!\n");
    }
    else if (percentage >= 80.0) {
        printf("WARNING: You have used 80%% or more of your budget!\n");
    }
    else {
        printf("STATUS: Your spending is under control.\n");
    }

    printf("----------------------------------\n");
}

// Main function
int main() {
    long long choice;

    while (1) {
        printf("\n====================================\n");
        printf("       STUDENT EXPENSE TRACKER\n");
        printf("====================================\n");

        printf("1. Set Monthly Budget\n");
        printf("2. Add Expense\n");
        printf("3. View All Expenses\n");
        printf("4. Category-wise Summary\n");
        printf("5. Check Remaining Balance\n");
        printf("6. Budget Alert\n");
        printf("7. Exit\n");

        printf("------------------------------------\n");
        printf("Enter your choice: ");

        choice = readNumber();

        switch (choice) {
            case 1:
                setBudget();
                break;

            case 2:
                addExpense();
                break;

            case 3:
                viewExpenses();
                break;

            case 4:
                categorySummary();
                break;

            case 5:
                checkBalance();
                break;

            case 6:
                budgetAlert();
                break;

            case 7:
                printf("\nThank you for using Student Expense Tracker!\n");
                return 0;

            default:
                printf("Invalid menu choice! Try again.\n");
        }
    }
}
