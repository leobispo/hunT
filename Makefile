all:
	clang++ -ggdb -std=c++11 -stdlib=libc++ -c statemachine.cpp
	clang++ -ggdb -std=c++11 -stdlib=libc++ -c hit.cpp
	clang++ -ggdb -std=c++11 -stdlib=libc++ -c hunt.cpp
	clang++ -ggdb -std=c++11 -stdlib=libc++ -c summary.cpp
	clang++ -ggdb -std=c++11 -stdlib=libc++ -c output.cpp
	clang++ -ggdb -std=c++11 -stdlib=libc++ -o hunT main.cpp statemachine.o hit.o hunt.o summary.o output.o
clean:
	rm -rf *.o hunt *.html hunT.dSYM
