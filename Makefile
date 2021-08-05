INCLUDE_DIRS := Includes
CC 			 := g++
CFLAGS 		 := -I$(INCLUDE_DIRS)


OBJS 		 := customErrorClass.o EmployeeRecords.o main.o 
DEPS 		 := ${INCLUDE_DIRS}/customErrorClass.h EmployeeRecords.h

.PHONY: clean all

all: Johnson_EmployeeFinal customErrorClass.o EmployeeRecords.o main.o


clean:
	rm $(OBJS) Johnson_EmployeeFinal

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

EmployeeRecords.o: EmployeeRecords.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

main.o: main.cpp
	$(CC) -c -o $@ $(CFLAGS) $<

Johnson_EmployeeFinal: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)