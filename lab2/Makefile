TARGET = $(SOURCE:.c=)

lfcopy : lfcopy.o line_functions.o
	clang $^ -Wall -Werror -o $@

%.o : %.c
	clang -Wall -Werror -c $<
 
$(TARGET) : $(SOURCE)
	clang $(SOURCE) -Wall -Werror -o $(TARGET)
	echo $(SOURCE)

