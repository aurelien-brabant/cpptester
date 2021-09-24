SRCS	:= Tester.cpp Timer.cpp
HEADERS	:= Tester.hpp Timer.hpp assert.hpp
TARGET	:= libcpptester.a

CC			:= clang++
CPP_FLAGS	:= -Wall -Wextra -Werror

OBJS		:=  $(SRCS:%.cpp=%.o)

RM			:= rm -rf

all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $(TARGET) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

.PHONY: clean fclean re all

%.o: %.cpp
	$(CC) $(CPP_FLAGS) -c $< -o $@
