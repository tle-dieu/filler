# Filler #

Filler is the second project of the algorithmic branch at 42.
Two players are fighting on a map.

* On each turn, the current player receive a piece and have to put on the map.
* To put a piece, the player have to write its coordinates in the "Y X\n" format on the standard input.
* The game stops as soon as nothing has been added to the board.
* The winner is the one who controls the most space on the board

## Subjects ##

* [English](subjects/fillit.en.pdf)
* [French](subjects/fillit.fr.pdf)

## Compiling ##

Run `make` command and an executable called `fillit` should be created.

## Usage ##

```shell
./resources/filler_vm -f path [-i | -p1 path | -p2 path] [-s | -q | -t time]
    -f  --file           use a map file (required)
    -i  --interactive    interactive mode(default)
    -p1 --player1        use filler binary as a first player
    -p2 --player2        use filler binary as a second player
    -s  --seed           use the seed number (initialization random) (man srand)
    -q  --quiet          quiet mode
    -t  --time           set timeout in second
```

## Example ##

`$> ./filler_vm -f maps/map01 -p1 ./tle-dieu.filler -p2 players/hcao.filler`

## Notes ##

This code complies with the 42 school [norm](https://github.com/Binary-Hackers/42_Subjects/blob/master/04_Norme/norme_2_0_1.pdf)
