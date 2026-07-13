a: sol.cpp
	g++ -o a sol.cpp -std=c++11 -O2

a23: sol.cpp
	g++ -o a sol.cpp -std=c++23 -O2

1: 1.cpp
	g++ -o a 1.cpp -std=c++11 -O2

2: 2.cpp
	g++ -o a 2.cpp -std=c++11 -O2

3: 3.cpp
	g++ -o a 3.cpp -std=c++11 -O2

4: 4.cpp
	g++ -o a 4.cpp -std=c++11 -O2

5: 5.cpp
	g++ -o a 5.cpp -std=c++11 -O2

clean:
	rm -f a
	rm -f a23
