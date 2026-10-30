NAME = RPN

SRC =  main.cpp RPN.cpp

CPP = c++

FLAGS =	-Wall -Wextra -Werror -std=c++98

OBJS_DIR = objs

OBJS = $(SRC:%.cpp=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CPP) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CPP) $(FLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)
fclean: clean
	rm -f $(NAME)
re:
	$(MAKE) fclean
	$(MAKE) all
.PHONY: all clean fclean re
