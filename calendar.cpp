#include <iostream>
#include <iomanip>
#include <cstdlib>

// Массив с названиями месяцев
const char* nameMonths[] = {
  "January","February","March","April","May","June","July","August","September","October","November","December" };

// Строка с сокращениями дней недели
const char* daysWeek = "Su Mo Tu We Th Fr Sa";


//-----------------------------------// Начнем описание вспомогательных функций

// Напишем функцию, которая вычисляет, каким днем недели начинается первое число n-го месяца
int findDayOfWeekFirstDayOfMonth(int year, int month) {
    // Алгоритм Зеллера требует, чтобы январь и февраль были перенесены на 13-й и 14-й месяц предыдущего года
    if (month < 3) {
        month += 12;
        year -= 1;
    }

    int endOfYear = year % 100;  // Последние 2 цифры года
    int introductionOfYear = year / 100;  // Первые 2 цифры года

    // Применяем формулу Зеллера
    int h = (1 + 13 * (month + 1) / 5 + endOfYear + endOfYear / 4 + introductionOfYear / 4 + 5 * introductionOfYear) % 7;
    return (h + 6) % 7;  // Возвращаем день недели с поправкой на начало недели (воскресенье)
}

// Функция, которая возвращает количество дней в n-ом месяце
int getCountDayInMonth(int year, int month) {
    int countDayInMonth[] = { 31,28,31,30,31,30,31,31,30,31,3,31 }; // Количество дней в месяце 

    // Проверяем, високосный ли год
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        countDayInMonth[1] = 29;  // Високосный год - февраль имеет 29 дней
    }
    return countDayInMonth[month - 1];  // Возвращаем количество дней в месяце
}

// Функция для проверки правильности введенного месяца
bool checkRightInputMonth(int month) {
    return !(month > 12 || month < 1);  // Месяц должен быть в диапазоне от 1 до 12
}

// Функция для проверки правильности введенного года
bool checkRightInputYear(int year) {
    return !(year > 9999 || year < 1);  // Год должен быть в диапазоне от 1 до 9999
}


//-----------------------------------// Начнем описание основных функций

// Функция для печати календаря на год
void printYear(int year) {
    std::cout << year << std::endl;  // Печатаем год
    bool first = false;  // Флаг для первого месяца квартала
    bool second = false; // Флаг для второго месяца квартала
    for (int quarter = 0; quarter < 4; quarter++) {  // Разбиваем год на 4 квартала
        int monthFirst = quarter * 3 + 1;  // Первый месяц квартала
        int monthSecond = quarter * 3 + 2; // Второй месяц квартала
        int monthThird = quarter * 3 + 3;  // Третий месяц квартала

        // Вычисляем начало недели для каждого месяца и количество недель в месяце
        int dayFirst = findDayOfWeekFirstDayOfMonth(year, monthFirst);
        int daysC = getCountDayInMonth(year, monthFirst);
        int weeksFirst = ((dayFirst + daysC - 1) / 7) + 1;

        int daySecond = findDayOfWeekFirstDayOfMonth(year, monthSecond);
        int daysCSec = getCountDayInMonth(year, monthSecond);
        int weeksSecond = ((daySecond + daysCSec - 1) / 7) + 1;

        int dayThird = findDayOfWeekFirstDayOfMonth(year, monthThird);
        int daysCThird = getCountDayInMonth(year, monthThird);
        int weeksThird = ((dayThird + daysCThird - 1) / 7) + 1;

        // Находим максимальное количество недель среди 3 месяцев квартала
        int maxBetweenWeeks = std::max(std::max(weeksFirst, weeksSecond), weeksThird);
        // Печатаем заголовки месяцев
        std::cout << std::left << std::setw(20) << nameMonths[monthFirst - 1];
        std::cout << "  ";
        std::cout << std::left << std::setw(20) << nameMonths[monthSecond - 1];
        std::cout << "  ";
        std::cout << std::left << nameMonths[monthThird - 1] << "\n";
        // Печатаем заголовки дней недели
        std::cout << std::left << std::setw(20) << daysWeek;
        std::cout << "  ";
        std::cout << std::left << std::setw(20) << daysWeek;
        std::cout << "  ";
        std::cout << std::left << std::setw(20) << daysWeek << "\n";
        first = false;
        second = false;
        // Печатаем календарь для каждого квартала
        for (int locWeek = 0; locWeek < maxBetweenWeeks; locWeek++) {  // Проходим по неделям квартала
            bool flag = false;  // Флаг для отслеживания форматирования
            for (int dayOfSet = 0; dayOfSet < 7; dayOfSet++) {  // Проходим по дням недели
                int day = locWeek * 7 + dayOfSet - dayFirst + 1;  // Вычисляем день месяца
                // Печатаем дни месяца, если они попадают в нужный диапазон
                if (day >= 1 && day <= daysC) {
                    if (weeksFirst > weeksThird && weeksFirst > weeksSecond && day == daysC) {
                        if ((dayFirst + day) % 7 != 1) { std::cout << " ";}  // Если это последний день месяца
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
                else {  // Если день не входит в текущий месяц
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
            // Печатаем второй месяц квартала
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
            // Печатаем третий месяц квартала
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
                else {  // Если день не входит в текущий месяц
                    if (day > daysCThird) {
                        break;
                    }
                    std::cout << "   ";
                }
            }
            std::cout << std::endl;
        }
        // Разделяем кварталы пустой строкой
        if (quarter != 3) {
            std::cout << std::endl;
        }
    }
}

// Функция для печати календаря для одного месяца
void printmonthandcalendar(int year, int month) {
    // Массив с названием месяцев
    const char* nameMonths[] = { "January","February","March","April", "May","June","July","August","September", "October","November","December" };
    int countDaysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };  // Количество дней в месяцах
    // Проверка на високосный год
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        countDaysInMonth[1] = 29;  // Високосный год
    }
    // Получаем первый день месяца и количество дней в месяце
    int firstDay = findDayOfWeekFirstDayOfMonth(year, month);
    int days = countDaysInMonth[month - 1];
    std::cout << nameMonths[month - 1] << std::endl;  // Печатаем название месяца
    std::cout << "Su Mo Tu We Th Fr Sa" << std::endl;  // Печатаем дни недели
    // Пропускаем пустые дни перед первым днем месяца
    for (int i = 0; i < firstDay; i++) {
        std::cout << "   ";
    }
    // Печатаем дни месяца
    for (int day = 1; day <= days; day++) {
        if (day == days) {
            std::cout << day;  // Печатаем последний день месяца
            break;
        }
        // Печатаем день недели
        if ((day + firstDay) % 7 == 0) {
            if (day < 10) {
                std::cout << " ";
            }
            std::cout << day;
            std::cout << std::endl;
        }
        else {
            std::cout << std::setw(2) << day << " ";  // Печатаем день с пробелами
            if ((firstDay + day) % 7 == 0) {
                std::cout << std::endl;
            }
        }
    }
}

// Основная функция программы
int main(int argc, char* argv[]) {
    // Проверка количества аргументов командной строки
    if (argc < 2 || argc >= 3) {
        std::cerr << "Unknown" << std::endl;  // Ошибка при неверных аргументах
        return 1;
    }

    // Если задан только год, печатаем календарь на год
    if (argc == 2) {
        int year = std::atoi(argv[1]);
        if (!checkRightInputYear(year)) {  // Проверка на допустимый диапазон года
            std::cerr << "Unknown" << std::endl;
            return 1;
        }
        printYear(year);  // Печатаем календарь на год
    }
    // Если заданы месяц и год, печатаем календарь для месяца
    else {
        int year = std::atoi(argv[2]);
        if (!checkRightInputYear(year)) {  // Проверка на допустимый диапазон года
            std::cerr << "Unknown" << std::endl;
            return 1;
        }
        int month = std::atoi(argv[1]);
        if (!checkRightInputMonth(month)) {  // Проверка на допустимый диапазон месяца
            std::cerr << "Unknown" << std::endl;
            return 1;
        }
        std::cout << year << "\n";
        printmonthandcalendar(year, month);  // Печатаем календарь для месяца
        std::cout << "\n";
    }
    return 0;  // Завершаем программу
}
