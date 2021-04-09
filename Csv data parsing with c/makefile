MAKE = gcc
FILENAME = topcgpas.c
TARGET = topcgpas

compile:
	$(MAKE) $(FILENAME) -o $(TARGET)

run: compile
	./$(TARGET) students.csv a.csv

testAll: compile test1 test2 test3 test4 test5 test6
	@echo "All done"

test1:
	@echo "TEST: Incorrect number of arguments"
	./$(TARGET) 1 2 3

test2:
	@echo "TEST: Incorrect input/output filename"
	./$(TARGET) no.csv output.csv

test3:
	@echo "TEST: Incorrect file extension"
	./$(TARGET) a.txt b.txt

test4:
	@echo "TEST: Empty file"
	./$(TARGET) empty.csv output.csv

test5:
	@echo "TEST: Header only"
	./$(TARGET) header.csv output.csv

test6:
	@echo "TEST: Proper file with expected output"
	./$(TARGET) students.csv output.csv
