power: test-power.o power.o
	gcc -pedantic -std=gnu99 -Wall -Werror test-power.o power.o -o power
test-power.o: test-power.c
	gcc -std=gnu99 -Wall -Werror -c test-power.c
power.o: power.c
	gcc -pedantic -std=gnu99 -Wall -Werror -c power.c
