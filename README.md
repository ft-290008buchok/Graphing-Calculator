# graphic-calculator
  
Это приложение имеет минимальный интерфейс (по сути оно является чистым бэкэндом), оно будет интересно тем, кто хочер познакомиться с одним из способов реализации графического калькулятора и разобраться в алгоритме его работы. Графический калькулятор это приложение, которое строит график математической зависимости. Данный калькулятор строит график двухмерной кривой, заданной уравнением с двумя неизвестными. Например, график уравнения x^4 + y^4 = x^2 + y * sin(x), построенного в этой программе, будет выглядеть вот так.   
![изображение](https://user-images.githubusercontent.com/71639489/179047367-d927d737-da6e-4fe4-89bb-2d73f7dd7794.png)   

# Установка   

Для крмпиляции этого проекта предпочтительно использовать MS Visual Studio не старше VS-2015. Достаточно создать пустой проект консольного приложения C++. В папке code содержатся 4 файла arial.ttf, calc.cpp, calc.h и main.cpp, все эти файлы необходимо скопировать в корневой каталог проекта. Файл main.cpp содержит код основной программы, calc.h и calc.cpp это файл загаловка и файл реализации вспомогательного модуля программы, а arial.ttf является служебным файлом программы. Когда все файлы скопированны в проект, можно запускать процесс компиляции через меню Visual Studio или комбинацией "Ctrl + F5".   

# Использование   

Когда компиляция завершится, появится простое окно консоли, в котором можно ввести выражение кривой и нажать "Enter". Выражение может содержать только латинские символы "x", "y", цифпы, разделительную точку для вещественных чисел ".", знаки "+", "-", "*", "/", круглые скобки "(", ")", знак равно "=" и обозначения стандартных тригонометрических функций sin, cos, tg, ctg. Выражение не должно содержать пробелы.   
В новом окне отобразится график кривой. График масштабируется колёсиком мыши   
