#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Данный код проверяет правильность ввода информации о фигурах типа "окружность" в файле "circle.txt". Он считывает строки из этого файла и передает их в функцию checkerrors, которая проверяет каждую строку на наличие ошибок во вводе информации. //
#define SIZE 100

int checker(char* str) //Функция checker проверяет правильность ввода названия фигуры, которое должно начинаться с "circle ". Если это условие не выполнено, возвращает значение 1, что говорит, что название введено неверно.//
{
    int ret = 1;
    char rec[SIZE];
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != '(')
            rec[i] = str[i];
        else
            break;
    }
    char figure[] = "circle ";
    if (strcmp(rec, figure) == 0) {
        ret = 0;
    }
    return ret;
}

int checkarg(char* str) //Функция checkarg проверяет правильность ввода аргументов, которые указывают координаты центра фигуры и её радиус. Она проверяет положение запятых, точек и пробелов в строке и считает количество этих символов. Если количество этих символов не соответствует требуемому, возвращает значение 1, указывая на наличие ошибки в координатах или радиусе. //
{
    int ret = 0;
    int count = 0;
    for (int i = 8; str[i] != ',' && i < strlen(str); i++) {
        if ((str[i] != '.' && str[i] != ' ')
            && !(str[i] >= 48 && str[i] <= 57)) {
            printf("Figure coordinates entered incorrectly\n\n");
            ret++;
            return 1;
        }
        if (str[i] >= 48 && str[i] <= 57 && str[i + 1] == ' ')
            count++;
        if (str[i] == '.' && str[i + 1] == ')')
            count += 2;
    }
    if (count + 1 != 2) {
        printf("Figure coordinates entered incorrectly\n\n");
        ret++;
        return ret;
    }
    int index = 0;
    for (int i = 0; i != strlen(str); i++) {
        if (str[i] == ',') {
            index = i + 1;
            i = strlen(str) - 1;
        }
    }
    for (; str[index] != ')' && index < strlen(str); index++) {
        if ((str[index] != '.' && str[index] != ' ')
            && !(str[index] >= 48 && str[index] <= 57)) {
            printf("Figure radius entered incorrectly\n\n");
            ret++;
            return 1;
        }
        if (str[index] >= 48 && str[index] <= 57 && str[index + 1] == ' ')
            count++;
        if (str[index] == '.' && str[index + 1] == ' ')
            count += 2;
    }
    if (count != 1) {
        printf("Figure radius entered incorrectly\n\n");
        ret++;
    }
    return ret;
}

int checkarguments(char* str) //Функция checkarguments проверяет наличие правильного окончания строки. Оно должно заканчиваться на символ ')' и если это условие не выполняется, возвращает значение 1. //
{
    int ret = 1, firstBracket = 0;
    int endingSymbol;
    if (str[strlen(str) - 1] == '\n')
        endingSymbol = strlen(str) - 2;
    else
        endingSymbol = strlen(str) - 1;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ')') {
            firstBracket = i;
            break;
        }
    }
    if (firstBracket == endingSymbol)
        ret = 0;
    return ret;
}

int checkerrors(char* str, int countFigures) //Функция checkerrors вызывает предыдущие три функции для каждой строки файла и выводит на экран номер проверяемой фигуры и саму строку. Если какая-то из функций возвращает значение, отличное от нуля, то функция checkerrors не выводит сообщение об ошибке. //
{
    printf("Figure %d:\n", countFigures);
    printf("%s", str);
    if (checker(str))
        printf("Incorrect input of figure name\n\n");
    else if (checkarg(str))
        return 0;
    else if (checkarguments(str))
        printf("Wrong final symbol\n\n");

    return 0;
}

int main() //В конечном итоге, программа проверяет все строки в файле и выводит сообщение об ошибке при наличии каких-либо ошибок в их содержании. Если все строки файлы были проверены успешно, программа завершается.//
{
    FILE* file;
    file = fopen("circle.txt", "r");
    if (file == NULL) {
        printf("Error of oppening file!\n");
        return 1;
    }
    char str1[SIZE];
    int countFigures = 0;
    while (fgets(str1, SIZE, file)) {
        countFigures++;
        checkerrors(str1, countFigures);
    }
    fclose(file);
    return 0;
}
