NAME = bpack
FILES = $(NAME).c
FLAGS = -std=c99 -Wall -pedantic -o
COMPILER = gcc
EXE = $(NAME)

TEST_FOLD = Test-Cases
TEST_FILE_1 = ascii-compress-size56-test
TEST_FILE_2 = $(TEST_FILE_1)--COMPRESSED
TEST_FILE_3 = QUESTION--ascii-compressed
TEST_RESULT_1 = test1-c.txt
TEST_RESULT_2 = test2-d.txt
TEST_RESULT_3 = test3-d.txt
TEST_PRINT = xxd -b

TARBALL = bpacker.tar.gz

DIVIDER = ===========================================================

all: $(EXE)

$(EXE): $(FILES)
	$(COMPILER) $(FLAGS) $(EXE) $(FILES)

test1:
	@echo "Test 1 $(DIVIDER)"
	./$(EXE) -c $(TEST_FOLD)/$(TEST_FILE_1) $(TEST_RESULT_1)
	$(TEST_PRINT) $(TEST_RESULT_1)
	@echo "Checking differences"
	diff -c $(TEST_FOLD)/$(TEST_FILE_2) $(TEST_RESULT_1)

test2:
	@echo "Test 2 $(DIVIDER)"
	./$(EXE) -d $(TEST_FOLD)/$(TEST_FILE_2)  $(TEST_RESULT_2)
	$(TEST_PRINT) $(TEST_RESULT_2)
	@echo "Checking differences"
	diff -c $(TEST_FOLD)/$(TEST_FILE_1) $(TEST_RESULT_2) 

test3:
	@echo "Test 3 $(DIVIDER)"
	./$(EXE) -d $(TEST_FOLD)/$(TEST_FILE_3) $(TEST_RESULT_3)
	$(TEST_PRINT) $(TEST_RESULT_3) | head -n 10

tests:	test1 test2 test3

tar:
	tar -cvf $(TARBALL) $(TEST_FOLD) $(FILES) makefile

clean:
	@[ -f ./$(EXE) ] && rm $(EXE) || true
	@[ -f ./$(TEST_RESULT_1) ] && rm $(TEST_RESULT_1) || true
	@[ -f ./$(TEST_RESULT_2) ] && rm $(TEST_RESULT_2) || true
	@[ -f ./$(TEST_RESULT_3) ] && rm $(TEST_RESULT_3) || true
	@[ -f ./$(TARBALL) ] && rm $(TARBALL) || true
