#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 1000

// структура данных
struct InfoOfFlight
{
    char informations[MAXLEN];
};
// функция быстрой сортировка
int Quick_Sort(int *quickmsv, int size);
// функция ввода/дополнения данных
void enterdata(FILE *file);
void repeatenternewinformations(struct InfoOfFlight *, FILE *file, int choise, int count);
// функция проверки корректности ввода
int correctinput(char *line);
// функция вывода данных
void outputdata(struct InfoOfFlight *, FILE *file, int idoutput);
void outputdata_for_edit(struct InfoOfFlight *, FILE *file, int idoutput);
// функция удаления данных
void deletedata(struct InfoOfFlight *, FILE *file, int number, int count);
// функция редактирования данных
void editdata(struct InfoOfFlight *, FILE *file, int count);
// функция изменения данных
void changedata(struct InfoOfFlight *, FILE *file, int choise, int count, int changechoise);
// функция записи данных в файл
void writedata(struct InfoOfFlight *, FILE *file, int count);
void rewritedata(struct InfoOfFlight *, FILE *file, int count);
// функция подбора маршрута с наименьшей стоимостью
void minimumprice(struct InfoOfFlight *, int count);
// функция подбора маршрута с наименьшем временем пересадки
void minimumtransfer(struct InfoOfFlight *, int count);
// функция подсчета кол-ва элементов
int countingelements(struct InfoOfFlight *, FILE *file, int count);

int main()
{
    struct InfoOfFlight info[1000];


    FILE *file;
    file = fopen("CRS/info.bin", "rb"); char line[MAXLEN];
    char *bufline = fgets(line, MAXLEN, file); int idstruct = 0;

    if (bufline == NULL)
    {
        file = fopen("CRS/info.bin", "wb");
        printf("\n\033[101mFILE IS EMPTY\033[0m\n" "\nPLEASE ENTER THE DATA\n"
        "If you want \033[91mto get out, enter 'exit'\033[0m\n" "\n\033[95mINPUT FORMAT\033[0m\n"
        "\nEnter everything in one line\n"
        "Enter the flight number (\033[92mformat: N1234\033[0m)\n"
        "Enter the start of depatrture and arrival (\033[92mformat: FirstCountry- SecondCountry\033[0m)\n"
        "Enter the time of departure (\033[92mformat: 00:00-00:00\033[0m)\n" "Enter the flight time (\033[92mformat: 000\033[0m)\n"
        "Enter the waiting time during the transfer (\033[92mformat: 000\033[0m)\n"
        "Enter the cost of the flight in dollars(\033[92mformat: 123456\033[0m)\n"
        "\n\033[90m\033[106mINPUT EXAMPLE: N12 Russia-USA 17:14 5 2990\033[0m\n"
        "\nENTER:\n");

        enterdata(file);
        file = fopen("CRS/info.bin", "rb");
        int count = countingelements(info, file, idstruct); rewritedata(info, file, count);
    }

    else
    {
        while(1)
        {
            printf("\nIf you want to \033[91mexit\033[0m, \033[91m enter - 1\033[0m\n"
            "\nIf you want to \033[91msee\033[0m information about flight,\033[91menter 0\033[0m"
            "\nIf you want to \033[91medit\033[0m the database, \033[91menter 1\033[0m"
            "\nIf you want to \033[91mdelete\033[0m an entry from the database,\033[91menter 2\033[0m"
            "\nIf you want to \033[91mreplenish\033[0m the database,\033[91menter 3\033[0m"
            "\nIf you want to \033[91mchoose a route with the least amount of waiting time\033[0m, \033[91menter 4\033[0m"
            "\nIf you want to \033[91mchoose the route with the lowest cost\033[0m, \033[91menter 5\033[0m\n");

            int inputnumber; // переменная выбора действий
            int count; // переменная кол-ва структур
            printf("Enter: ");
            scanf("%d", &inputnumber); // ввод выбора
            getchar();

            if (inputnumber == -1) exit(1); // выход

            else if(inputnumber == 0)
            {
                file = fopen("CRS/info.bin", "rb");
                outputdata(info, file, idstruct); // вывод информации
            }
            else if(inputnumber == 1) // редактирование информации
            {
                file = fopen("CRS/info.bin", "rb"); outputdata_for_edit(info, file, idstruct); file = fopen("CRS/info.bin", "rb");
                count = countingelements(info, file, idstruct); file = fopen("CRS/info.bin", "wb");
                editdata(info, file, count); // вызов функции изменения данных
            }
            else if(inputnumber == 2) // удаление из данных
            {
                file = fopen("CRS/info.bin", "rb"); outputdata_for_edit(info, file, idstruct); file = fopen("CRS/info.bin", "rb");
                count = countingelements(info, file, idstruct);
                int choisenumber; // переменная выбора строки удаления
                printf("Enter the number of the line you want to delete: "); scanf("%d", &choisenumber); // выбор строки пользователем getchar();
                file = fopen("CRS/info.bin", "wb");
                deletedata(info, file, choisenumber, count); // функция удаления
                file = fopen("CRS/info.bin", "rb");
                outputdata_for_edit(info, file, idstruct);
            }
            else if(inputnumber == 3) // дополнение базы
            {
                file = fopen("CRS/info.bin", "ab"); enterdata(file); // вызов дополнения данных
                file = fopen("CRS/info.bin", "rb");
                count = countingelements(info, file, idstruct); rewritedata(info, file, count);
            }
            else if(inputnumber == 4) // подбор с наименьшей пересадкой
            {
                file = fopen("CRS/info.bin", "rb");
                count = countingelements(info, file, idstruct);
                file = fopen("CRS/info.bin", "rb");
                outputdata_for_edit(info, file, idstruct);
                minimumtransfer(info, count);
            }

            else if(inputnumber == 5) // подбор с наименьшей стоимостью
            {
                file = fopen("CRS/info.bin", "rb");
                count = countingelements(info, file, idstruct);
                file = fopen("CRS/info.bin", "rb");
                outputdata_for_edit(info, file, idstruct);
                minimumprice(info, count);
            }
            else exit(1);
        }
    }

    return 0;
}
// функция подсчета кол-во элементов
int countingelements(struct InfoOfFlight *info, FILE *file, int count)
{
    while (!feof(file)) // пока не конец файла
    {
        char bufline[MAXLEN]; // строка, в которой хранится строка из файла
        fread(bufline, sizeof(char),
        sizeof(bufline)/sizeof(bufline[0]), file); //cчитываем строку
        if (strcmp(bufline, "\n")!= 0) // если строка не пустая
        {
            strcpy(info[count].informations, bufline); // копируем в структуру count++;
        }
    }
    count--;

    fclose(file);

    return count;
}
// функция ввода/дополнения данных
void enterdata(FILE *file)
{
    char linecycle[1000]; // строка с новой инфомацией
    int cycle = 1; // переменная бесконечного цикла

    while (cycle) // пока вводим
    {
        fgets(linecycle, MAXLEN, stdin); // считываем строку
        int flag = correctinput(linecycle);

        if (strstr(linecycle, "exit")) cycle = 0; // если exit выходим

        else
        {
            if (flag) fwrite(linecycle, sizeof(char), sizeof(linecycle)/sizeof(linecycle[0]), file); // дозаписываем в файл новую информацию
            else
            {
            printf("\nINCORECTED\n");
            }
        }
    }

    fclose(file);
}

void repeatenternewinformations(struct InfoOfFlight *info, FILE *file, int choise, int count)
{
    char newline[MAXLEN]; printf("Enter new information: ");
    fgets(newline, MAXLEN, stdin);
    int crct = correctinput(newline);
    if (crct)
    {
        strcpy(info[choise].informations, newline); writedata(info, file, count); rewritedata(info, file, count);
    }
    else
    {
        printf("\nINCORECTED\n"); repeatenternewinformations(info, file, choise, count);
    }
}
// функция проверки корректности ввода
int correctinput(char *line)
{
    char bufline[MAXLEN]; strcpy(bufline, line); char *trans;
    char *perelet; char *transfer;
    char sim; // символ

    char proverkacyfril;
    char *in_sim = bufline; // указатель на строку
    int count = 0; // счетчик символов в словах
    int len = 6; // длина максимальная на каждое слово
    int flag = 0; // флаг на корректность строки
    int found = 0; // флаг на некорректность строки
    int razdelcount = 0; // счетчик пробелов
    int cifri = 0; // счетчик цифр
    int proverka = 0; // флаг на часы
    int ip = 0;
    int trpr = 0; // флаг на время перелета


    int ln = 0; int start = 1;
    char *in_start = bufline;

    do
    {
        sim = *in_sim;
        if (sim == ' ')
        {
            razdelcount++; ip = 0;
            if (found) return flag;
            else if (count > 6 && len == 6) return flag;
            else if (count > 20 && len == 20) return flag;
            else if (count > 10 && len == 10) return flag;
            else if ((count > 5 || count < 5) && len == 5) return flag;
            else if (count > 3 && len == 3) return flag;
            else if (count > 7 && len == 7) return flag;

            count = 0;
            cifri = 0;
            if (razdelcount == 1) len = 20;
            else if(razdelcount == 2) len = 10;
            else if (razdelcount == 3) len = 5;
            else if (razdelcount == 4) len = 3;
            else if (razdelcount == 5)
            {
                ln = 0;
                start = 1;
                transfer = (char*)malloc(ln*sizeof(char));
                int transid = 0;
                while (in_start < in_sim) transfer[transid++] = *in_start++; trpr++;
                len = 3;
            }
            else if (razdelcount == 6)
            {
                perelet = (char*)malloc(ln*sizeof(char));
                int perid = 0;
                while (in_start < in_sim) perelet[perid++] = *in_start++;
                int first = atoi(perelet);
                int second = atoi(transfer);
                if (first >= second) return 0;
                len = 7;
            }
        }
    else if (sim == '\n')
    {
        if (found) return flag;
    }
    else
    {
        count++;
        if (len == 6)
        {
            if ((sim < 'A' || sim > 'Z') && (sim < '0' || sim > '9')) found = 1;
        }
        else if (len == 20)
        {
            if (sim < 'A' || sim > 'Z' && sim < 'a' || sim > 'z')
            {
                if (sim != '-') found = 1;
            }
        }
        else if (len == 10)
        {
            if (sim < 'A' || sim > 'Z' && sim < 'a' || sim > 'z')
            {
                found = 1;
            }
        }
        else if (len == 5)
        {
            cifri++;
            if ((sim < '0' || sim > '9') && sim != ':') found = 1;

            if (cifri == 1)
            {
                proverkacyfril = sim; if (sim > '2') found = 1;
            }
            else if (cifri == 2)
            {
                if (proverkacyfril == '2' && sim > '4') found = 1;
                if (proverkacyfril == '2' && sim == '4') proverka = 1;
            }
            else if (cifri == 4)
            {
                proverkacyfril = sim;
                if (sim >= '6') found = 1; if (proverka) found = 1;
            }
            else if (cifri == 5)
            {
                if (proverkacyfril == '6' && sim > '0' && proverka == 0) found =1;
            }
        }
        else if (len == 3)
        {
            if (trpr == 0)
            {
                if ((sim < '0' || sim > '9')) found = 1;
                if (start) in_start = in_sim;
                start = 0; ln++;
            }

            else
            {
                if ((sim < '0' || sim > '9')) found = 1;
                if (start) in_start = in_sim;
                start = 0; ln++;
            }
        }
        else if (len == 7)
        {
            if ((sim < '0' || sim > '9')) found = 1;
        }
    }

    in_sim++;
    } while (sim != '\0');

    if (razdelcount < 6) return 0;
    else if (razdelcount == 6)
    {
        if (bufline[strlen(bufline)] == '\n') return 0; else return 1;
    }
    else return 0;
}

// функиця вывода данных
void outputdata(struct InfoOfFlight *info, FILE *file, int idoutput)
{
    printf("\n\033[33mNumber|	Route	| Transfer |Time departure| Flight time |Waiting time| Cost\033[0m\n");

    printf("	|	|	|	|	|	|-\n");
    while (!feof(file)) // пока не конец файла
    {
        char bufline[MAXLEN]; // строка, в которой хранится строка из файла
        fread(bufline, sizeof(char), sizeof(bufline)/sizeof(bufline[0]), file); //считываем строку
        if (strcmp(bufline, "\n")!= 0) // если строка не пустая
        {
            strcpy(info[idoutput].informations, bufline); // копируем в структуру
            idoutput++;
        }
    }
    idoutput--;

    for (int i = 0; i < idoutput; i++)
    {
        int countlen = 0; int tab = 6;
        int razdel = 0;
        for (int j = 0; j < strlen(info[i].informations); j++)
        {
            if (info[i].informations[j] == ' ' || info[i].informations[j] == '\n')
            {
    //printf("%c", info[i].informations[j]);
                int center = (tab - countlen)/2;
                int bufcenter = 0; int bufrazdel = 0; int schet = 0;

    //printf("!%d! !%d! !%d!", center, tab, countlen);
                countlen = 0;
                while (bufcenter < center)
                {
                    printf(" "); bufcenter++; schet++;
                }

                for (int k = 0; k < strlen(info[i].informations); k++)
                {
                    if (info[i].informations[k] == ' ')
                    {
                        bufrazdel++;
                        if (bufrazdel > razdel)
                        {
                            while (schet < tab)
                            {
                                printf(" "); schet++;
                            }
                            printf("|");
                            break;
                        }
                    }
                    else
                    {
                        if (bufrazdel == razdel)
                        {
                            printf("%c", info[i].informations[k]);
                            schet++;
                        }
                    }
                }
                razdel++;
                if (razdel == 1)
                {
                    tab = 20;
                }
                else if (razdel == 2) tab = 10;
                else if (razdel == 3) tab = 14;
                else if (razdel == 4) tab = 13;
                else if (razdel == 5) tab = 12;
                else tab = 7;

            }
            else
            {
            //printf("%c", info[i].informations[j]);
                countlen++;
            }
        }
        printf("	|	|	|	|	|	|----\n");
    }
    fclose(file);

    printf("\033[35m\nClick ENTER\033[0m\n"); fgetc(stdin);
}

void outputdata_for_edit(struct InfoOfFlight *info, FILE *file, int idoutput)
{
    printf("\n\033[33mNumber|	Route	| Transfer |Time departure| Flight time |Waiting time| Cost\033[0m\n");
    printf("	|	|	|	|	|	|-\n");
    while (!feof(file)) // пока не конец файла
    {
        char bufline[MAXLEN]; // строка, в которой хранится строка из файла
        fread(bufline, sizeof(char), sizeof(bufline)/sizeof(bufline[0]), file); //считываем строку
        if (strcmp(bufline, "\n")!= 0) // если строка не пустая
        {
            strcpy(info[idoutput].informations, bufline); // копируем в структуру
            idoutput++;
        }
    }
    idoutput--;

    for (int i = 0; i < idoutput; i++)
    {
        int countlen = 0; int tab = 6;
        int razdel = 0;
        for (int j = 0; j < strlen(info[i].informations); j++)
        {
            if (info[i].informations[j] == ' ' || info[i].informations[j] == '\n')
            {

        //printf("%c", info[i].informations[j]);
                int center = (tab - countlen)/2;
                int bufcenter = 0; int bufrazdel = 0; int schet = 0;
        //printf("!%d! !%d! !%d!", center, tab, countlen);
                countlen = 0;
                while (bufcenter < center)
                {
                    printf(" "); bufcenter++; schet++;
                }

                for (int k = 0; k < strlen(info[i].informations); k++)
                {
                    if (info[i].informations[k] == ' ')
                    {
                        bufrazdel++;
                        if (bufrazdel > razdel)
                        {
                            while (schet < tab)
                            {
                                printf(" "); schet++;
                            }
                            printf("|"); break;
                        }
                    }

                    else
                    {
                        if (bufrazdel == razdel)
                        {
                            printf("%c", info[i].informations[k]); schet++;
                        }
                    }
                }
                razdel++;
                if (razdel == 1)
                {
                    tab = 20;
                }
                else if (razdel == 2) tab = 10;
                else if (razdel == 3) tab = 14;
                else if (razdel == 4) tab = 13;
                else if (razdel == 5) tab = 12;
                else tab = 7;
            }
            else
            {
        //printf("%c", info[i].informations[j]);
            countlen++;
            }
        }
        printf("	|	|	|	|	|	|----\n");
    }

    fclose(file);
}

    // функция удаления данных
void deletedata(struct InfoOfFlight *info, FILE *file, int number, int count)
{
    for (int i = 0; i < count; i++) // пребираем все элементы структур
    {
        if (i == number) // если нашли подходящую строчку
        {
            for (int j = i; j < count; j++) strcpy(info[j].informations, info[j+1].informations); // копируем в нее все последующие структуры
            // перезаписываем в файл новые структуры без последней
            for (int j = 0; j < count-1; j++) fwrite(info[j].informations, sizeof(char), sizeof(info[j].informations)/sizeof(info[j].informations[0]), file);
        }
    }
    fclose(file);
}

// функция редактирования данных
void editdata(struct InfoOfFlight *info, FILE *file, int count)
{
    int choise; // переменная выбора линии
    printf("\nSelect the line you want to edit: ");
    scanf("%d", &choise);

    int editchoise; // переменная выбора чего редактировать
    printf("\nIf you want to \033[91medit the line completely, enter 0\033[0m\n" "If you want to \033[91medit the flight number, enter 1\033[0m\n"
            "If you want to \033[91medit countries, enter 2\033[0m\n"
            "If you want to \033[91medit transfer country, enter 3\033[0m\n" "If you want to \033[91medit the departure time, enter 4\033[0m\n" "If you want to \033[91medit the flight time, enter 5\033[0m\n"
            "If you want to \033[91medit the transfer time, enter 6\033[0m\n"
            "If you want to \033[91medit the cost of the flight, enter 7\033[0m\n");
    scanf("%d", &editchoise);
    getchar();

    if (editchoise == 0) // если изменить всю строку
    {
        repeatenternewinformations(info, file, choise, count);
    }
    else if (editchoise == 1) // если изменить номер рейса
    {
        char bufline[MAXLEN]; // строка для копирования
        strcpy(bufline, info[choise].informations); // копируем даннуюструктуру новую строчку
        char *inbufline = bufline; // устанавливаем указатель
        char newbufline[MAXLEN]; // строка для копирования
        char N[MAXLEN]; // строка для ввода нового номера рейса
        printf("Enter a new number: ");
        fgets(N, MAXLEN, stdin);

        int id = 0; // id строки новой
        for (int i = 0; i < strlen(N)-1; i++)
        {
            newbufline[id] = N[i]; // копируем в начало строки новый номер
            id++;

        }
        for (int i = 0; i < strlen(bufline); i++)
        {
            if (bufline[i] == ' ') // если встретился пробел первый
            {
                do // копируем все после пробера в новую строку
                {
                    newbufline[id++] = *inbufline++;
                } while (*inbufline != '\0');
                break; // досрочно завершаем цикл
            }
        inbufline++; // двигаем указатель
        }
        int crct = correctinput(newbufline);
        if (crct)
        {
            strcpy(info[choise].informations, newbufline); // копируем новую строку в в структуру
            writedata(info, file, count); // сохраняем все в файле
        }
        else printf("\nINCORECTED\n");
    }
    else if (editchoise == 2) // если изменить страну
    {
        printf("Enter a new countries: ");
        changedata(info, file, choise, count, editchoise);
    }
    else if (editchoise == 3) // страну пересадки
    {
        printf("Enter a new transfer country: ");
        changedata(info, file, choise, count, editchoise);
    }
    else if (editchoise == 4) // если изменить время вылета
    {
        printf("Enter a new departure time: "); changedata(info, file, choise, count, editchoise);
    }
    else if (editchoise == 5) // если изменить время полета
    {
        printf("Enter a new flight time: "); changedata(info, file, choise, count, editchoise);
    }
    else if (editchoise == 6) // если изменить время пересадки
    {
        printf("Enter a new transfer time: "); changedata(info, file, choise, count, editchoise);
    }
    else if (editchoise == 7) // если изменить стоимость
    {
        char bufline[MAXLEN]; // строка для копирования
        strcpy(bufline, info[choise].informations); // копируем содержимое структуры в новую строку
        char *inbufline = bufline; // устанавливаем указатель
        char *start = bufline; // указатель на начало строки
        char newbufline[MAXLEN]; // новая строка
        char N[MAXLEN]; // ввод строки новых стран

        printf("Enter a new cost: "); fgets(N, MAXLEN, stdin);
        int found = 0; // флаг на 6 пробел

        int id = 0; // id новой строки
        for (int i = 0; i < strlen(bufline); i++) // перебираем все элементы строки
        {
        do
        {
            if (*inbufline == ' ') found++; newbufline[id++] = *inbufline++;
        } while (found<6);

        for (int i = 0; i<strlen(N); i++) newbufline[id++] = N[i]; break;
        }
        int crct = correctinput(newbufline);
        if (crct)
        {
            strcpy(info[choise].informations, newbufline); // копируем новую строку в в структуру
            writedata(info, file, count); // сохраняем все в файле
        }
        else printf("\nINCORECTED\n");
    }
}

// функция изменения данных
void changedata(struct InfoOfFlight *info, FILE *file, int choise, int count, int changechoise)
{
    char bufline[MAXLEN]; // строка для копирования
    strcpy(bufline, info[choise].informations); // копируем содержимое структуры в новую строку
    char *inbufline = bufline; // устанавливаем указатель
    char *start = bufline; // указатель на начало строки
    char newbufline[MAXLEN]; // новая строка
    char *N; // ввод строки новых данных
    N = (char*)malloc(MAXLEN*sizeof(char));

    fgets(N, MAXLEN, stdin);
    int found = 0; // флаг на cnahgechoise пробел
    int id = 0; // id новой строки
    for (int i = 0; i < strlen(bufline); i++) // перебираем все элементы строки
    {
        if (bufline[i] == ' ') // если пробел
        {
            found++; // увеличиваем счетчик
            if (found < changechoise) // если не cnahgechoise-1 пробел, то просто копируем содержимое до cnahgechoise-2 пробела пробела
            {
                do
                {
                    newbufline[id++] = *start++;
                } while (*start != ' '); newbufline[id++] = *start++;
            }
            else // если cnahgechoise
            {
                for (int i = 0; i < strlen(N)-1; i++) // копируем новую стоимость
                {
                    newbufline[id] = N[i]; id++;
                }
                do // копируем все после cnahgechoise
                {
                    newbufline[id++] = *inbufline++;
                } while (*inbufline != '\0');
                break; // досрочно завершаем цикл
            }
        }
        inbufline++; // двигаем указатель
    }
    int crct = correctinput(newbufline);
    if (crct)
    {
        strcpy(info[choise].informations, newbufline); // копируем новую строку в структуру
        writedata(info, file, count); // записываем в файл
    }
    else
    {
        printf("\nINCORECTED\n");
        if (changechoise == 1) printf("Enter a new number: ");
        else if (changechoise == 2) printf("Enter a new countries: ");
        else if (changechoise == 3) printf("Enter a new transfer country: ");
        else if (changechoise == 4) printf("Enter a new departure time: ");
        else if (changechoise == 5) printf("Enter a new flight time: ");
        else if (changechoise == 6) printf("Enter a new transfer time: ");
        else printf("Enter a new cost: ");
        changedata(info, file, choise, count, changechoise);
    }
}

// функция записи данных в файл
void writedata(struct InfoOfFlight *info, FILE *file, int count)
{
    file = fopen("CRS/info.bin", "wb");
    for (int i = 0; i < count; i++) fwrite(info[i].informations, sizeof(char), sizeof(info[i].informations)/sizeof(info[i].informations[0]), file);
    fclose(file);
}
void rewritedata(struct InfoOfFlight *info, FILE *file, int count)
{
    file = fopen("CRS/info.bin", "wb");
    for (int i = 0; i < count; i++) fwrite(info[i].informations, sizeof(char), sizeof(info[i].informations)/sizeof(info[i].informations[0]), file);
    close(file);
}
// функция подбора маршрута с наименьшей стоимостью
void minimumprice(struct InfoOfFlight *info, int count)
{
    char *country; // строка в которой будет хранится страна копирования
    char *countrybuf; // буферная строка
    char **msvcountry; // динамический массив подходящих строк
    char **massofcost; // динамический массив стоимости
    int id = 0; // id элементов в динамическом массиве
    int idmass = 0; // id элементов динамического массива со стоимостью
    country = (char*)malloc(MAXLEN*sizeof(char));
    printf("\n\033[30mEnter the country of\033[0m \033[31mdeparture andarrival\033[0m \033[30mseparated by a\033[0m \033[95m-\033[0m\n");
    fgets(country, MAXLEN, stdin); // вводим нужные страны
    printf("\n");
    countrybuf = (char*)malloc(strlen(country)*sizeof(char));

    strncpy(countrybuf, country, strlen(country)-1); // копируем страны без \n
    msvcountry = (char**)malloc(sizeof(info)*sizeof(char*)); // выделемпамять


    for (int i = 0; i < sizeof(info); i++) msvcountry[i] = (char*)malloc(strlen(info[i].informations)*sizeof(char)); // выделяем память

    for (int i = 0; i < count; i++)
    {
        if (strstr(info[i].informations, countrybuf))
        {
            strcpy(msvcountry[id++], info[i].informations); // копируем нужные нам строки из структуры в наш массив
        }
    }

    massofcost = (char**)malloc(sizeof(msvcountry)*sizeof(char*)); // выделяем память под цены

    for (int i = 0; i < sizeof(msvcountry); i++) massofcost[i] = (char*)malloc(7*sizeof(char)); // выделяем память

    for (int i = 0; i < id; i++)
    {
        int index = 0; // индекс для строки цен
        int razdelcount = 0; // счетчик пробелов
        char cost[7]; // строка для копирования цена

        for (int j = 0; j < strlen(msvcountry[i]); j++)
        {
            if (msvcountry[i][j] == ' ') razdelcount++;
            if (razdelcount == 6 && msvcountry[i][j] != '\0' && msvcountry[i][j] != ' ') cost[index++] = msvcountry[i][j]; // копируем символы
        }

        strcpy(massofcost[idmass++], cost); // копируем нашу стоимость в массив
    }

    int *masscostint; // динамический массив хранения цен в
    int masscostint = (int*)malloc(idmass*sizeof(int)); // выделение памяти

    for (int i = 0; i < idmass; i++) masscostint[i] = atoi(massofcost[i]); // заполняем массив преобразовывая char в int

    Quick_Sort(masscostint, idmass); // вызываем быструю сортировку

    char **outputmsv; int outid = 0;

    outputmsv = (char**)malloc(MAXLEN*sizeof(char*));

    for (int i = 0; i < MAXLEN; i++) outputmsv[i] = (char*)malloc(MAXLEN*sizeof(char));

    for (int i = 0; i < idmass; i++)
    {
        int countlen = 0;
        int cost = masscostint[i];

        while (cost != 0)
        {
            cost /= 10; countlen++;
        }
        cost = masscostint[i]; char *coststring;
        int idstr = 1;
        coststring = (char*)malloc((countlen+2)*sizeof(char));
        coststring[0] = ' ';
        coststring[countlen+1] = '\n';

        while (cost != 0)
        {
            coststring[idstr++] = cost%10 + '0';
            cost /= 10;
        }
        for (int i = 0; i < countlen/2; i++)
        {
            char replace = coststring[i+1];
            coststring[i+1] = coststring[countlen - i];
            coststring[countlen - i] = replace;
        }

        for (int i = 0; i < id; i++)
        {
            int flag = 0;
            if (strstr(msvcountry[i], coststring))
            {
                for (int j = 0; j < MAXLEN; j++)
                {
                    if (strstr(outputmsv[j], msvcountry[i])) flag = 1;
                }
                if (flag == 0)
                {
                    strcpy(outputmsv[outid++], msvcountry[i]);
                }
            }
        }
        free(coststring);
    };

    // вывод в виде таблицы
    printf("\n\033[33mNumber|	Route	| Transfer |Time departure| Flight time |Waiting time| Cost\033[0m\n");
    printf("	|	|	|	|	|	|-\n");
    for (int i = 0; i < outid; i++)
    {
        int countlen = 0; int tab = 6;
        int razdel = 0;
        for (int j = 0; j < strlen(outputmsv[i]); j++)
        {
            if (outputmsv[i][j] == ' ' || outputmsv[i][j] == '\n')
            {
            //printf("%c", info[i].informations[j]);
                int center = (tab - countlen)/2;
                int bufcenter = 0;
                int bufrazdel = 0; int schet = 0;
                //printf("!%d! !%d! !%d!", center, tab, countlen);
                countlen = 0;
                while (bufcenter < center)
                {
                    printf(" "); bufcenter++; schet++;
                }

                for (int k = 0; k < strlen(outputmsv[i]); k++)
                {
                    if (outputmsv[i][k] == ' ')
                    {
                        bufrazdel++;
                        if (bufrazdel > razdel)
                        {
                            while (schet < tab)
                            {
                                printf(" "); schet++;
                            }
                            printf("|"); break;
                        }
                    }
                    else
                    {
                        if (bufrazdel == razdel)
                        {
                            printf("%c", outputmsv[i][k]); schet++;
                        }
                    }
                }
                razdel++;
                if (razdel == 1)
                {
                tab = 20;
                }
                else if (razdel == 2) tab = 10;
                else if (razdel == 3) tab = 14;
                else if (razdel == 4) tab = 13;
                else if (razdel == 5) tab = 12;
                else tab = 7;

            }
            else
            {
            //printf("%c", info[i].informations[j]);
                countlen++;
            }
        }
    printf("	|	|	|	|	|	|----\n");
    }


    // очищаем память
    for (int i = 0; i < outid; i++) free(outputmsv[i]);

    for (int i = 0; i < id; i++) free(msvcountry[i]);
    for (int i = 0; i < idmass; i++) free(massofcost[i]); free(outputmsv);
    free(msvcountry); free(massofcost); free(masscostint);

    rintf("\033[35m\nClick ENTER\033[0m\n"); fgetc(stdin);
}

// функция подбора маршрута с наименьшем временем пересадки
void minimumtransfer(struct InfoOfFlight *info, int count)
{
    char *country; // ввод стран перелета
    char *countrybuf; // для копирования с обрезанием
    char **msvcountry; // массив строк с таким маршрутом
    char **msvtransfer; // массив времени пересадки
    int id = 0; // id массива стран
    int massid = 0;

    country = (char*)malloc(MAXLEN*sizeof(char)); printf("\n\033[30mEnter the country of\033[0m \033[31mdeparture and arrival\033[0m \033[30mseparated by a\033[0m \033[95m-\033[0m\n"); fgets(country, MAXLEN, stdin); // вводим нужные страны
    printf("\n");
    countrybuf = (char*)malloc(strlen(country)*sizeof(char));

    strncpy(countrybuf, country, strlen(country)-1); // копируем страны без \n
    printf("%s\n", countrybuf);

    msvcountry = (char**)malloc(sizeof(info)*sizeof(char*)); // выделем память

    for (int i = 0; i < sizeof(info); i++) msvcountry[i] = (char*)malloc(strlen(info[i].informations)*sizeof(char)); // выделяем память

    for (int i = 0; i < count; i++)
    {
        if (strstr(info[i].informations, countrybuf))
        {
            strcpy(msvcountry[id++], info[i].informations); // копируем нужные нам строки из структуры в наш массив
        }
    }

    msvtransfer = (char**)malloc(sizeof(msvcountry)*sizeof(char*)); // выделяем память под ожидание

    for (int i = 0; i < sizeof(msvcountry); i++) msvtransfer[i] = (char*)malloc(3*sizeof(char)); // выделяем память

    for (int i = 0; i < id; i++)
    {
        int index = 0; // индекс для строки пересадки
        int razdelcount = 0; // счетчик пробелов
        int len = 0;
        for (int j = 0; j < strlen(msvcountry[i]); j++)
        {
            if (msvcountry[i][j] == ' ') razdelcount++;

            if (razdelcount == 5 && msvcountry[i][j] != ' ') len++;
        }

        razdelcount = 0; char *transfer;
        transfer = (char*)malloc(len*sizeof(char));
        for (int j = 0; j < strlen(msvcountry[i]); j++)
        {
            if (msvcountry[i][j] == ' ') razdelcount++;
            if (razdelcount == 5 && msvcountry[i][j] != ' ') transfer[index++] = msvcountry[i][j];
        }

        strcpy(msvtransfer[massid++], transfer); // копируем наше время в массив
        free(transfer);
    }


    int *masstransint; // динамический массив хранения пересадки в int masstransint = (int*)malloc(massid*sizeof(int)); // выделение памяти

    for (int i = 0; i < massid; i++) masstransint[i] = atoi(msvtransfer[i]); // заполняем массив преобразовывая char в int

    Quick_Sort(masstransint, massid); // вызываем быструю сортировку

    char **outputmsv; int outid = 0;

    outputmsv = (char**)malloc(MAXLEN*sizeof(char*));

    for (int i = 0; i < MAXLEN; i++) outputmsv[i] = (char*)malloc(MAXLEN*sizeof(char));

    for (int i = 0; i < massid; i++)
    {
        int countlen = 0;
        int trans = masstransint[i];

        while (trans != 0)
        {
            trans /= 10; countlen++;
        }

        trans = masstransint[i];


        char *transstring; int idstr = 1;
        transstring = (char*)malloc((countlen+2)*sizeof(char)); transstring[0] = ' ';
        if (countlen == 0) transstring[countlen+2] = ' '; else transstring[countlen+1] = ' ';

        if (trans != 0)
        {
            while (trans != 0)
            {
                transstring[idstr++] = trans%10 + '0'; trans /= 10;
            }

            for (int i = 0; i < countlen/2; i++)
            {
                char replace = transstring[i+1]; transstring[i+1] = transstring[countlen - i]; transstring[countlen - i] = replace;
            }
        }
        else transstring[1] = trans + '0';


        for (int i = 0; i < id; i++)
        {
            int flag = 0;
            if (strstr(msvcountry[i], transstring))
            {
                for (int j = 0; j < MAXLEN; j++)
                {
                    if (strstr(outputmsv[j], msvcountry[i])) flag = 1;
                }
                if (flag == 0)
                {
                //printf("%s", msvcountry[i]);
                    strcpy(outputmsv[outid++], msvcountry[i]);
                }
            }
        }
        free(transstring);
    };

    // вывод в виде таблицы
    printf("\n\033[33mNumber|	Route	| Transfer |Time departure| Flight time |Waiting time| Cost\033[0m\n");
    printf("	|	|	|	|	|	|-\n");
    for (int i = 0; i < outid; i++)
    {
        int countlen = 0; int tab = 6;
        int razdel = 0;
        for (int j = 0; j < strlen(outputmsv[i]); j++)
        {
            if (outputmsv[i][j] == ' ' || outputmsv[i][j] == '\n')
            {
                //printf("%c", info[i].informations[j]);
                int center = (tab - countlen)/2;
                int bufcenter = 0; int bufrazdel = 0; int schet = 0;
                //printf("!%d! !%d! !%d!", center, tab, countlen);
                countlen = 0;
                while (bufcenter < center)
                {
                    printf(" "); bufcenter++; schet++;
                }
                for (int k = 0; k < strlen(outputmsv[i]); k++)
                {
                    if (outputmsv[i][k] == ' ')
                    {
                        bufrazdel++;
                        if (bufrazdel > razdel)
                        {
                            while (schet < tab)
                            {
                                printf(" "); schet++;
                            }
                            printf("|"); break;
                        }
                    }
                    else
                    {
                        if (bufrazdel == razdel)
                        {
                            printf("%c", outputmsv[i][k]); schet++;
                        }
                    }
                }
                razdel++;
                if (razdel == 1)
                {
                tab = 20;
                }
                else if (razdel == 2) tab = 10; else if (razdel == 3) tab = 14;

                else if (razdel == 4) tab = 13; else if (razdel == 5) tab = 12; else tab = 7;

            }
            else
            {
            //printf("%c", info[i].informations[j]); countlen++;
            }
        }
        printf("	|	|	|	|	|	|----\n");
    }

    for (int i = 0; i < outid; i++) free(outputmsv[i]);
    for (int i = 0; i < id; i++) free(msvcountry[i]);
    for (int i = 0; i < massid; i++) free(msvtransfer[i]); free(outputmsv);
    free(msvcountry); free(msvtransfer); free(masstransint);

    printf("\033[35m\nClick ENTER\033[0m\n"); fgetc(stdin);
}

// функция быстрой сортировки
int Quick_Sort(int *quickmsv, int size)
{
    int i = 0; // начало массива

    int j = size - 1; // конец массива
    int mid = quickmsv[size/2]; // середина массив

    do
    {
        while(*(quickmsv+i) < mid) i++; // если меньше середины, двигаемся вправо
        while (*(quickmsv+j) > mid) j--; // если больше середины, двигаемся влево

        if (i <= j) // если нашли два элемента отличающихся от середины - меняем их местами
        {
            int buf = *(quickmsv+i);
            *(quickmsv+i) = *(quickmsv+j);
            *(quickmsv+j) = buf;
            i++; j--;
        }
    } while (i <= j);

    if (i < size) Quick_Sort(&quickmsv[i], size - i); // если левый счетчик не дошел до конца, возвращаем адрес ? i элемента и элемент до которого идти
    if (j > 0) Quick_Sort(quickmsv, j+1); // если правый счетчик не дошел до начала, возвращаем массив и j + 1
    return 0;
}
