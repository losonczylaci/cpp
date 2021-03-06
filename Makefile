buildDir := build
libDir := lib
testDir := test

include makefiles/tools.mk
include makefiles/utils.mk
include makefiles/production.mk
include makefiles/test.mk

start: all
	@./$(buildDir)/main

all: $(buildDir)/main

clean: 
	rm -rf $(buildDir)

cleanlib:	
	rm -rf $(libDir)

test: $(buildDir)/testmain
	@echo -e "\nRunning unit-tests..."
	@./$(buildDir)/testmain

qa: memcheck lint

memcheck: $(buildDir)/testmain
	valgrind --leak-check=yes $(buildDir)/testmain --gtest_brief=1

lint: 
	@echo -e "\nRunning linter..."
	$(CLANG-TIDY) --header-filter='.*' $(sources) -- -Iinclude

cppcheck:
	@echo -e "\nRunning cppcheck..."
	cppcheck --enable=all $(sources)

coverage: $(buildDir)/coverageFilt.info
	@lcov --summary $(lcovConfig) $<

coverageHtml: $(buildDir)/coverageFilt.info
	@genhtml $< -o $(buildDir) -q $(lcovConfig)
	@echo HTML report has been generated, see $(buildDir)/index.html 