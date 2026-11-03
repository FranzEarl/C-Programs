# C-Programs

A collection of small C programs.

## Contact book

The contact book can add, list, search, edit, and delete contacts. It saves
contacts in `contacts.txt` in the current working directory.

Compile and run with GCC:

```sh
gcc contact_book.c -o contact_book
./contact_book
```

## To-do list

The to-do list can add, view, complete, and delete tasks. It saves tasks in
`tasks.txt` in the current working directory.

Compile and run with GCC:

```sh
gcc todo_list.c -o todo_list
./todo_list
```

## Quiz game

The quiz game loads multiple-choice questions from `quiz_questions.txt`,
shuffles their order, and displays the final score. Each line in the questions
file must contain a question, four answer options, and the correct option
number, separated by `|`.

Compile and run with GCC:

```sh
gcc quiz_game.c -o quiz_game
./quiz_game
```

You can also pass a different questions file as the first argument:

```sh
./quiz_game my_questions.txt
```

## Sudoku solver

Enter a Sudoku puzzle one row at a time, using digits `1`-`9` for clues and
`0` or `.` for empty cells. The program checks for duplicate clues and solves
valid puzzles using backtracking.

Compile and run with GCC:

```sh
gcc sudoku_solver.c -o sudoku_solver
./sudoku_solver
```
