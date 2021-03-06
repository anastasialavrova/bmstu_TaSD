# Типы и структуры данных  

МГТУ им. Баумана, 3 семестр, 2018 год  
Вариант №11

[**Лабораторная работа №1**](https://github.com/anastasialavrova/bmstu_TaSD/tree/master/lab_1)

Смоделировать операцию умножения действительного числа в форме (-)m.n Е (-)K, где суммарная длина мантиссы (m+n) - до 30 значащих цифр, а величина порядка K - до 5 цифр, на целое число длиной до 30 десятичных цифр. Результат выдать в форме (-)0.m1 Е (-)K1, где m1 - до 30 значащих цифр, а K1 - до 5 цифр.

[**Лабораторная работа №2**](https://github.com/anastasialavrova/bmstu_TaSD/tree/master/lab_2)

Создать таблицу, содержащую не менее 40 записей с вариантной частью. Произвести поиск информации по вариантному полю. Упорядочить таблицу, по возрастанию ключей (где ключ – любое невариантное поле по выбору программиста), используя: а) исходную таблицу; б) массив ключей, используя 2 разных алгоритма сортировки. Оценить эффективность этих алгоритмов (по времени и по используемому объему памяти) при различной реализации программы, то есть в случаях а) и б). Обосновать выбор алгоритма сортировки. Оценка эффективности должна быть относительной (в %).  
Имеются описания:  

     Type жилье = (дом, общежитие);  

     Данные:  
  
     имя, пол (м, ж), возраст, средний балл за сессию, дата  
     поступления
     адрес:
         дом : (улица, №дома, №кв );
         общежитие : (№общ., №комн.);

Ввести общий список студентов группы.
Вывести список студентов, живущих в общежитии указанного года
поступления.

[**Лабораторная работа №3**](https://github.com/anastasialavrova/bmstu_TaSD/tree/master/lab_3)

Разреженная (содержащая много нулей) матрица хранится в форме 3-х объектов:  

- вектор A содержит значения ненулевых элементов;  

- вектор IA содержит номера строк для элементов вектора A;  

- связный список JA, в элементе Nk которого находится номер компонент в A и IA, с которых начинается описание столбца Nk матрицы A.  

1.Смоделировать операцию умножения  вектора-строки и матрицы, хранящихся в этой форме, с получением результата в той же форме.  
2. Произвести операцию умножения, применяя  стандартный алгоритм работы с матрицами.  
3. Сравнить время выполнения операций и объем памяти при использовании этих 2-х алгоритмов при различном проценте заполнения матриц.  

[**Лабораторная работа №4**](https://github.com/anastasialavrova/bmstu_TaSD/tree/master/lab_4)

Разработать программу работы со стеком, реализующую операции добавления и удаления элементов из стека и отображения текущего состояния стека. Реализовать стек: а) массивом; б) списком.  

Все стандартные операции со стеком должны быть оформлены отдельными подпрограммами. В случае реализации стека в виде списка при отображении текущего состояния стека предусмотреть возможность просмотра адресов элементов стека и создания дополнительного собственного списка свободных областей (адресов освобождаемой памяти при удалении элемента, который можно реализовать как списком, так и массивом) с выводом его на экран. Список свободных областей необходим для того, чтобы проследить, каким образом происходит выделение памяти менеджером памяти при запросах на нее и убедиться в возникновении или отсутствии фрагментации памяти.  

Используя стек, определить, является ли строка, состоящая из скобочек вида (), {}, [], правильной скобочной последовательностью.

[**Лабораторная работа №5**](https://github.com/anastasialavrova/bmstu_TaSD/tree/master/lab_5)

Заявки 1-го и 2-го типов поступают в "хвосты" своих очередей по случайному закону с интервалами времени Т1 и Т2. В ОА они поступают из "головы" очереди по одной и обслуживаются также равновероятно за времена Т3 и Т4, после чего покидают систему.  

Заявка 2-го типа может войти в ОА, если в системе нет заявок 1-го типа. Если в момент обслуживания заявки 2-го типа в пустую очередь входит заявка 1-го типа, то она немедленно поступает на обслуживание; обработка заявки 2-го типа прерывается и она возвращается в "хвост" своей очереди.  

Смоделировать процесс обслуживания первых 1000 заявок 1-го типа, выдавая после обслуживания каждых 100 заявок 1-го типа информацию о текущей и средней длине каждой очереди, а в конце процесса – общее время моделирования и количестве вошедших в систему и вышедших из нее заявок обоих типов, среднем времени пребывания заявок в очереди, количестве «выброшенных» заявок второго типа. Обеспечить по требованию пользователя выдачу на экран адресов элементов очереди при удалении и добавлении элементов. Проследить, возникает ли при этом фрагментация памяти.  

[**Лабораторная работа №6**](https://github.com/anastasialavrova/bmstu_TaSD/tree/master/lab_6)

Построить ДДП, в вершинах которого находятся слова из текстового файла. Вывести его на экран в виде дерева. Сбалансировать полученное дерево и вывести его на экран. Построить хеш-таблицу из слов текстового файла. Использовать метод цепочек для устранения коллизий. Осуществить поиск введенного слова в ДДП, в сбалансированном дереве, в хеш-таблице и в файле. Сравнить время поиска, объем памяти и количество сравнений при использовании различных (4-х) структур данных. Если количество сравнений 
в хеш-таблице больше указанного, то произвести реструктуризацию таблицы, выбрав другую функцию.

[**Лабораторная работа №7**](https://github.com/anastasialavrova/bmstu_TaSD/tree/master/lab_7)

Обработать графовую структуру. Ввод данных осуществить на усмотрение программиста. Результат выдать в графической форме.  

Задана система двусторонних дорог. Определить, можно ли, закрыв какие-нибудь три дороги, добиться того, чтобы из города А нельзя было попасть в город В.


