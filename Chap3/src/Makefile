CC=g++
CFLAGS=-O3 -std=c++17 -Wall

simple_mutex: mutex.cpp
	@$(CC) $(CFLAGS) mutex.cpp -o mutex -lpthread
	
run_simple_mutex: simple_mutex
	@./mutex

mutex_issue: flaw.cpp
	@$(CC) $(CFLAGS) flaw.cpp -o flaw -lpthread

run_mutex_issue: mutex_issues
	@./flaw

clean: 
	rm -rf main

