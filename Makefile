### @author:314638669, Barak10101998@gmail.com
#!make -f

CXX=c++
CXXFLAGS=-std=c++11 -Werror
VALGRIND_FLAGS==-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Demo.cpp Board.cpp Catan.cpp Graph.cpp Player.cpp Property.cpp
SOURCES_TESTS= Board.cpp Catan.cpp Graph.cpp Player.cpp Property.cpp TestCounter.cpp Test.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))
OBJECTS_TESTS = $(subst .cpp,.o,$(SOURCES_TESTS))

runCatan: catan
	./$^

runTest: test
	./$^

catan: Catan.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o Catan


test: TestCounter.o Test.o $(OBJECTS_TESTS)
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: catan test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test