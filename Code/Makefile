build:
	gcc process_generator.c -o gggg.out
	gcc clk.c -o cccc.out
	gcc scheduler.c -o ss.out -lm
	gcc scheduler_RR.c -o ssrr.out -lm
	gcc scheduler_HPF.c -o sshp.out -lm
	gcc scheduler_SRTN.c -o ssrn.out -lm
	gcc process.c -o process.out
	gcc process2.c -o process2.out
	gcc test_generator.c -o test_generator.out

clean:
	rm -f *.out  processes.txt

all: clean build

run:
	./test_generator.out
	./gggg.out