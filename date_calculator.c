#include <stdio.h>
#include <time.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

Date inputDate() {
    Date date;

    printf("Enter date (DD-MM-YYYY): ");
    scanf("%d-%d-%d", &date.day, &date.month, &date.year);

    return date;
}

int isLeapYear(int year) {
    if(year % 400 == 0) {
        return 1;
    }
    if(year % 100 == 0) {
        return 0;
    }
    if(year % 4 == 0) {
        return 1;
    }
    return 0;
}

int daysInMonth(int month, int year) {
    switch(month) {
        case 1: case 3: case 5:
        case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0;
    }
}

int isValidDate(Date date) {
    if(date.year < 1) {
        return 0;
    }
    if(date.month < 1 || date.month > 12) {
        return 0;
    }
    if(date.day < 1 || date.day > daysInMonth(date.month, date.year)) {
        return 0;
    }
    return 1;
}

int dayOfWeek(Date date) {
    int day = date.day;
    int month = date.month;
    int year = date.year;

    if(month < 3) {
        month += 12;
        year --;
    }

    int k = year % 100;
    int j = year / 100;

    int h = (day + (13 * (month + 1)) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;

    return (h + 6) % 7;
}

long long dateToDays(Date date) {
    long long year = date.year - 1;

    long long days = year * 365
                   + year / 4
                   - year / 100
                   + year / 400;
    
    for(int month = 1; month < date.month; month++) {
        days += daysInMonth(month, date.year);
    }

    days += date.day - 1;

    return days;
}

long long daysBetween(Date date1, Date date2) {
    long long days1 = dateToDays(date1);
    long long days2 = dateToDays(date2);

    return days2 - days1;
}

Date daysToDate(long long days) {
    Date date;

    int year = 1;

    while(1) {
        int daysInYear = isLeapYear(year) ? 366 : 365;

        if(days < daysInYear) {
            break;
        }
        days -= daysInYear;
        year++;
    }
    date.year = year;

    int month = 1;

    while(1) {
        int daysInCurrentMonth = daysInMonth(month, year);

        if(days < daysInCurrentMonth) {
            break;
        }
        days -= daysInCurrentMonth;
        month++;
    }
    date.month = month;
    date.day = days + 1;

    return date;
}

Date addDays(Date date, long long days) {
    long long totalDays = dateToDays(date);

    return daysToDate(totalDays + days);
}


Date subtractDays(Date date, long long days) {
    long long totalDays = dateToDays(date);

    return daysToDate(totalDays - days);
}


void displayMenu() {
    printf("\n========== DATE CALCULATOR ==========\n");
    printf("1. Calculate days between two dates\n");
    printf("2. Calculate date after N days\n");
    printf("3. Calculate date before N days\n");
    printf("4. Check leap year\n");
    printf("5. Find day of the week\n");
    printf("6. Exit\n");
    printf("=====================================\n");
    printf("Choose an option: ");
}


void calculateDaysBetween() {
    printf("\n--- Calculate Days Between ---\n");

    Date date1 = inputDate();

    if(!isValidDate(date1)) {
        printf("Invalid date!\n");
        return;
    }

    Date date2 = inputDate();

    if(!isValidDate(date2)) {
        printf("Invalid date!\n");
        return;
    }

    long long result = daysBetween(date1, date2);

    printf("\nDays between: %lld\n", result);

    if(result < 0)
        result = -result;

    printf("Absolute difference: %lld days\n", result);
}


int main() {
    Date date = inputDate();
    time_t currentTime = time(NULL);
    struct tm *date0 = localtime(&currentTime);
    Date newDate = addDays(date, 30);
    Date newDate1 = subtractDays(date, 30);
    int choice;

    Date currentDate;
    currentDate.day = date0->tm_mday;
    currentDate.month = date0->tm_mon + 1;
    currentDate.year = date0->tm_year + 1900;

    printf("Date: %02d-%02d-%04d\n", date.day, date.month, date.year);
    printf("Leap year: %s\n", isLeapYear(date.year) ? "Yes" : "No");
    printf("Days in month: %d\n", daysInMonth(date.month, date.year));

    if(isValidDate(date)) {
        printf("Valid date!\n");
    }
    else {
        printf("Invalid date!\n");
    }

    char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    printf("Day of the week: %s\n", days[dayOfWeek(date)]);
    printf("Day number : %lld\n", dateToDays(date));
    printf("Days Between: %lld\n", daysBetween(date, currentDate));
    printf("30 days later: %02d-%02d-%04d\n",
       newDate.day, newDate.month, newDate.year);
    printf("30 days earlier: %02d-%02d-%04d\n",
       newDate1.day, newDate1.month, newDate1.year);

    do {
        displayMenu();
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                calculateDaysBetween();
                break;

            case 6:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid option!\n");
        }

    } while(choice != 6);

    return 0;
}