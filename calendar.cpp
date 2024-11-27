
#include <iostream>
#include <iomanip>
#include <cstdlib>

const char* nameMonths[] = {
  "January","February","March","April","May","June","July","August","September","October","November","December" };

// Строка с сокращениями дней недели
const char* daysWeek = "Su Mo Tu We Th Fr Sa";


int findDayOfWeekFirstDayOfMonth(int year, int month) {
    if (month < 3) {
        month += 12;
        year -= 1;
    }

    int endOfYear = year % 100; 
    int introductionOfYear = year / 100;  

    int h = (1 + 13 * (month + 1) / 5 + endOfYear + endOfYear / 4 + introductionOfYear / 4 + 5 * introductionOfYear) % 7;
    return (h + 6) % 7;  
}

int getCountDayInMonth(int year, int month) {
    int countDayInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        countDayInMonth[1] = 29;  
    }
    return countDayInMonth[month - 1];  
}

bool checkRightInputMonth(int month) {
    return !(month > 12 || month < 1);  
}

bool checkRightInputYear(int year) {
    return !(year > 9999 || year < 1); 
}

void printYear(int year) {
    std::cout << year << std::endl;
    bool first = false; 
    bool second = false; 
    for (int quarter = 0; quarter < 4; quarter++) {
        int monthFirst = quarter * 3 + 1;
        int monthSecond = quarter * 3 + 2; 
        int monthThird = quarter * 3 + 3;

        int dayFirst = findDayOfWeekFirstDayOfMonth(year, monthFirst);
        int daysC = getCountDayInMonth(year, monthFirst);
        int weeksFirst = ((dayFirst + daysC - 1) / 7) + 1;

        int daySecond = findDayOfWeekFirstDayOfMonth(year, monthSecond);
        int daysCSec = getCountDayInMonth(year, monthSecond);
        int weeksSecond = ((daySecond + daysCSec - 1) / 7) + 1;

        int dayThird = findDayOfWeekFirstDayOfMonth(year, monthThird);
        int daysCThird = getCountDayInMonth(year, monthThird);
        int weeksThird = ((dayThird + daysCThird - 1) / 7) + 1;

        int maxBetweenWeeks = std::max(std::max(weeksFirst, weeksSecond), weeksThird);

        std::cout << std::left << std::setw(20) << nameMonths[monthFirst - 1];
        std::cout << "  ";
        std::cout << std::left << std::setw(20) << nameMonths[monthSecond - 1];
        std::cout << "  ";
        std::cout << std::left << nameMonths[monthThird - 1] << "\n";

        std::cout << std::left << std::setw(20) << daysWeek;
        std::cout << "  ";
        std::cout << std::left << std::setw(20) << daysWeek;
        std::cout << "  ";
        std::cout << std::left << std::setw(20) << daysWeek << "\n";
        first = false;
        second = false;

        for (int locWeek = 0; locWeek < maxBetweenWeeks; locWeek++) {  
            bool flag = false; 
            for (int dayOfSet = 0; dayOfSet < 7; dayOfSet++) { 
                int day = locWeek * 7 + dayOfSet - dayFirst + 1; 
                if (day >= 1 && day <= daysC) {
                    if (weeksFirst > weeksThird && weeksFirst > weeksSecond && day == daysC) {
                        if ((dayFirst + day) % 7 != 1) { std::cout << " "; }
                        std::cout << day;
                        first = true;
                        second = true;
                        break;
                    }
                    if (day > 9 && dayOfSet == 0) {
                        std::cout << day;
                    }
                    else {
                        if (day <= 9 && flag) {
                            std::cout << " ";
                        }
                        flag = true;
                        std::cout << " " << day;
                    }
                }
                else { 
                    if (day - daysC > 5 && dayOfSet == 6) {
                        std::cout << "  ";
                    }
                    else {
                        std::cout << "   ";
                    }
                }
            }
            if (locWeek == 0) {
                std::cout << " ";
            }
            else {
                if (!first) {
                    std::cout << "  ";
                }
            }
            flag = false;
            if (locWeek == 0) {
                std::cout << " ";
            }
            for (int dayLocWeek = 0; dayLocWeek < 7; dayLocWeek++) {
                if (locWeek + 1 > weeksSecond && locWeek + 1 != weeksThird) {
                    break;
                }
                int day = locWeek * 7 + dayLocWeek - daySecond + 1;
                if (day >= 1 && day <= daysCSec) {
                    if (weeksSecond > weeksThird && day == daysCSec) {
                        if ((daySecond + day) % 7 != 1) {
                            std::cout << " ";
                        }
                        std::cout << day;
                        second = true;
                        break;
                    }
                    if (dayLocWeek == 0 && locWeek + 1 == maxBetweenWeeks) {
                        std::cout << day;
                        continue;
                    }
                    if (day > 9 && dayLocWeek == 0) {
                        std::cout << day;
                    }
                    else {
                        if (day <= 9 && flag) {
                            std::cout << " ";
                        }
                        flag = true;
                        std::cout << " " << day;
                    }
                }
                else {
                    if (day - daysCSec > 6 && dayLocWeek % 7 == 6) {
                        std::cout << "  ";
                    }
                    else {
                        std::cout << "   ";
                    }
                }
            }
            if (locWeek == 0) {
                std::cout << " ";
            }
            else {
                if (!second) {
                    std::cout << "  ";
                    second = false;
                }
            }
            if (locWeek == 0) {
                std::cout << " ";
            }
            flag = false;
            for (int day_offset = 0; day_offset < 7; day_offset++) {
                if (locWeek + 1 > weeksThird) {
                    break;
                }
                int day = locWeek * 7 + day_offset - dayThird + 1;
                if (day >= 1 && day <= daysCThird) {
                    if (day > 9 && day_offset == 0) {
                        std::cout << day;
                    }
                    else {
                        if (day <= 9 && flag) {
                            std::cout << " ";
                        }
                        flag = true;
                        std::cout << " " << day;
                    }
                }
                else {
                    if (day > daysCThird) {
                        break;
                    }
                    std::cout << "   ";
                }
            }
            std::cout << std::endl;
        }
        if (quarter != 3) {
            std::cout << std::endl;
        }
    }
}

void printmonthandcalendar(int year, int month) {
    const char* nameMonths[] = { "January","February","March","April", "May","June","July","August","September", "October","November","December" };
    int countDaysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };  
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        countDaysInMonth[1] = 29; 
    }
    int firstDay = findDayOfWeekFirstDayOfMonth(year, month);
    int days = countDaysInMonth[month - 1];
    std::cout << nameMonths[month - 1] << std::endl;
    std::cout << "Su Mo Tu We Th Fr Sa" << std::endl; 
    for (int i = 0; i < firstDay; i++) {
        std::cout << "   ";
    }
    for (int day = 1; day <= days; day++) {
        if (day == days) {
            std::cout << day;
            break;
        }
        if ((day + firstDay) % 7 == 0) {
            if (day < 10) {
                std::cout << " ";
            }
            std::cout << day;
            std::cout << std::endl;
        }
        else {
            std::cout << std::setw(2) << day << " ";
            if ((firstDay + day) % 7 == 0) {
                std::cout << std::endl;
            }
        }
    }
}
int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        std::cerr << "Unknown" << std::endl;
        return 1;
    }
    if (argc == 2) {
        int year = std::atoi(argv[1]);
        if (!checkRightInputYear(year)) { 
            std::cerr << "Unknown" << std::endl;
            return 1;
        }
        printYear(year); 
    }
    else {
        int year = std::atoi(argv[2]);
        if (!checkRightInputYear(year)) {
            std::cerr << "Unknown" << std::endl;
            return 1;
        }
        int month = std::atoi(argv[1]);
        if (!checkRightInputMonth(month)) {
            std::cerr << "Unknown" << std::endl;
            return 1;
        }
        std::cout << year << "\n";
        printmonthandcalendar(year, month); 
        std::cout << "\n";
    }
    return 0; 
}
