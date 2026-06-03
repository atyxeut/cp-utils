a: sol.cpp
	g++ -o a sol.cpp -std=c++11 -O2

a23: sol.cpp
	g++ -o a sol.cpp -std=c++23 -O2

clean:
	rm -f a
	rm -f a23
