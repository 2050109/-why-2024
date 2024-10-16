all: query
	./query

query: query.cpp
	g++ query.cpp -o query -O2 -L ~/share/openssl/lib64 -lcrypto

build: builder
	./builder < table1.csv > grades.txt

builder: build.cpp
	g++ build.cpp -o builder -O2 -L ~/share/openssl/lib64 -lcrypto

clean:
	rm query