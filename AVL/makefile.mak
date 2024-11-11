run:
	g++ test.cpp -std=c++20 -o test
	./test

report:
	xelatex report.tex

clean:
	rm -f test report.pdf *.aux *.log
