SRCS	:= $(addprefix src/, Tester.cpp Timer.cpp)
HEADERS	:= Tester.hpp Timer.hpp assert.hpp
TARGET	:= libcastorno.a

CC			:= clang++
CPP_FLAGS	:= -Wall -Wextra -Werror -Iinclude

OBJS		:=  $(SRCS:%.cpp=%.o)

RM			:= rm -rf

all: $(TARGET)

$(TARGET): $(OBJS)
	@ar rcs $(TARGET) $(OBJS)
	@printf "LD\t$(TARGET)\n"

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(TARGET)

re: fclean all

.PHONY: clean fclean re all

%.o: %.cpp
	@$(CC) $(CPP_FLAGS) -c $< -o $@
	@printf "CC\t$<\n"
