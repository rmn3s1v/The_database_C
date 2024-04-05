# База данных "Авиакасса"

Этот проект представляет собой программу для работы с базой данных "Авиакасса". Программа обладает следующими функциональностями:

1. Пополнение базы данных.
2. Редактирование базы данных.
3. Удаление записей.
4. Подбор маршрута с наименьшим временем ожидания при пересадке.
5. Подбор маршрута с наименьшей стоимостью.

## Входные данные

Программа получает поток данных в следующем формате: `N000_First-Second_Middle_00:00_2_1_100`. Где:

- `N000` – номер рейса.
- `First-Second` - First – страна вылета, Second – страна прилета.
- `Middle` - страна пересадки.
- `00:00` - время вылета.
- `2` - время всего полета.
- `1` - время пересадки.
- `100` - стоимость билета.

## Основные функции программы

- `Quick_Sort()`: Функция быстрой сортировки.
- `countingelements()`: Функция подсчета количества элементов.
- `enterdata()`: Функция ввода/дополнения данных.
- `repeatenternewinformations()`: Функция ввода данных при редактировании всей строки.
- `correctinput()`: Функция проверки корректности ввода данных.
- `outputdata()`: Функция вывода данных.
- `outputdata_for_edit()`: Функция вывода данных при редактировании данных.
- `delete()`: Функция удаления данных.
- `editdata()`: Функция редактирования данных.
- `changedata()`: Функция изменения данных.
- `writedata()`: Функция записи данных.
- `rewritedata()`: Функция перезаписи данных.
- `minimumprive()`: Функция подбора выбранного маршрута по стоимости (от низкого к высокому).
- `minimumtransfer()`: Функция подбора выбранного маршрута по времени пересадки (от наименьшей к наибольшему).

## Описание функций программы

- `Quick_Sort()`: Функция быстрой сортировки. Получает на вход указатель на массив и размер массива. Инициализируются индексы начала (левый индекс) массива и конца (правый индекс), а также середина. Затем идет цикл `do…while()` до тех пор пока левый индекс не станет больше правого. Внутри этого цикла находятся еще два цикла `while`, благодаря которым происходит нахождение элементов, больших и меньших серединного, после чего они меняются местами. Функция рекурсивная и будет выполняться до тех пор, пока левый индекс не дойдет до конца массива, а правый до начала. Благодаря этой рекурсии массив сортируется по возрастанию.

- `countingelements()`: Функция подсчета количества элементов. Получает на вход указатель на структуру, файл и переменную count, в которой будет храниться количество структур. Программа пробегается по всем строкам в бинарном файле, копирует строку в структуру и увеличивает `count` на 1. После выполнения возвращает `count`.

- `enterdata()`: Функция ввода/дополнения данных. Получает на вход файл, в который будет записываться введенная информация. Информация вводится с клавиатуры, проверяется на корректность ввода функцией `correctinput()` и записывается в файл, если все верно.

- `repeatenternewinformations()`: Функция ввода данных при редактировании всей строки. Получает на вход указатель на структуру, файл, переменную `choise` и `count`. Переменная `choise` отвечает за выбранную строку, в которой нужно изменить полностью информацию, а `count` - количество строк (структр).

- `correctinput()`: Функция проверки корректности ввода данных. Получает на вход строку, которую разбивает по частям и проверяет каждую часть на корректность ввода. Части разбиения: номер рейса, страна вылета и прилета, страна пересадки, время вылета, время полета, время пересадки, стоимость.

- `outputdata()`: Функция вывода данных. Получает на вход указатель на структуру, файл и переменную `idouput`, которая подсчитывает количество элементов в базе данных. Затем при помощи цикла выводится в виде таблички все данные.

- `outputdata_for_edit()`: Функция вывода данных при редактировании. Получает на вход аналогичные данные, что и функция `outputdata()`, и работает аналогичным способом, но без паузы для просмотра.

- `deletedata()`: Функция удаления данных. Получает на вход указатель на структуру данных, файл, переменную `number` и `count`. Переменная `number` отвечает за номер выбранной строки (индекс в массиве структур), которую нужно удалить, а `count` - количество структур. Удаление происходит путем сдвига всех последующих данных на одну ячейку в массиве структур влево, тем самым затирая выбранную строку.

- `editdata()`: Функция редактирования данных. Получает на вход указатель на структуру, файл и переменную `count` (в которой хранится количество структур). Выбирается строка, которую нужно изменить, и что нужно изменить. Отредактировать можно как всю строку, так и определенную информацию (номер рейса, страну пересадки, цену и т.д.). После выбора строки (за это отвечает переменная `choise`), которую нужно редактировать и что нужно редактировать (за это отвечает переменная `editchoise`), вызывается функция `changedata()`, в которой происходит изменение.

- `changedata()`: Функция изменения данных. Получает на вход указатель на структуру, файл, переменную `choise` (отвечает за редактирование выбранной строки), `count` (отвечает за количество структур) и `changechoise` (отвечает за выбор чего редактировать). Создается переменная, в которую копируется выбранная строка, переменная, в

## Организация данных

Все необходимые данные организованы в отдельном бинарном файле, из которого они будут записаны в массив структур данных в программе. Работа с данными происходит только через массив структур, что исключает возможность случайного удаления или изменения других данных в файле.

## Основные константы и размеры массивов

- Основная константа: `MAXLEN`, отвечающая за максимальную длину строки и размер основных массивов.
- Размер основных массивов: 1000 байт.

## Структура данных

Имеется структура данных `InfoOfFlight`. Данные в структуру записываются в одну строку через пробел. В каждой строке хранится информация о рейсе (номер полета, страна вылета-прилета, страна пересадки, время вылета, время в пути, время пересадки, стоимость билета).

## Представление выходной информации

Выходная информация представляется в виде таблицы, где каждая строка соответствует информации о рейсе, а оглавление столбцов соответствует следующим данным:

1. Номер рейса
2. Маршрут
3. Пересадка
4. Время отправления
5. Время полета
6. Время пересадки
7. Стоимость

## Тестовые примеры

![Снимок экрана 2024-04-05 в 17 02 22](https://github.com/rmn3s1v/The_database_C/assets/123352975/cffee14e-eccf-4ea4-882a-161bb752e7c5)


# Автор
[rmn3s1v](https://github.com/rmn3s1v)