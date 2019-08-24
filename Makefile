.PHONY: all clean practice log

all:
	@gcc nq.c -o a.out

log: all
	@./a.out > log.txt

practice:
	@gcc practice.c -o p.out

clean:
	@rm *.out
