# Minesweeper
Projekt z wstępu do programowania w C

Tematem projektu jest gra ,,Saper". Na prostokątnej planszy ukryta jest pewna ilość bomb. Jeśli dane pole nie jest bombą, to cyfra na nim oznacza ilość bomb wokół tego pola. Zadaniem gracza jest odnalezienie wszystkich bomb w jak najkrótszym czasie poprzez odkrywanie kolejnych bezpiecznych pól. 


### How to install:
First, install ncurses:
>sudo apt-get install libncurses5-dev libncursesw5-dev

Clone this repository to your computer:
>git clone https://github.com/jkciesluk/minesweeper.git

Then compile using:
>gcc -o minesweeper ncmine.c time_records.c gboard.c simpleui.c -lncurses

And run:
>./minesweeper
