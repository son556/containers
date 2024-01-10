NAME = STL

## ANSI escape code
CYAN  := \033[1;36;40m
RESET := \033[0m
LOG   := printf "[$(CYAN)INFO$(RESET)] %s\n"

INC_DIRS += iterator vector test priority_queue deque queue stack list

vpath %.hpp $(INC_DIRS)

## file
HEADERS += iterator_traits.hpp reverse_iterator.hpp vector.hpp vector_test.hpp Number.hpp random_access_iterator.hpp
HEADERS += type_traits.hpp algorithm.hpp priority_queue.hpp deque.hpp deque_iterator.hpp deque_test.hpp
HEADERS += stack_test.hpp queue.hpp list.hpp
SRCS = test_container.cpp 
OBJS = $(SRCS:.cpp=.o)

## compile
# CXX= c++ -fsanitize=address -g
CXX= c++ -g
CXXFLAGS = -std=c++98 $(addprefix -I,$(INC_DIRS))
#
.PHONY: clean, fclean, re, all

all: $(NAME)

$(NAME): $(OBJS)
	@$(LOG) "Link"
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) 

$(OBJS): %.o: %.cpp $(HEADERS)
	@$(LOG) "Compile"
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	@$(LOG) "clean"
	@rm -f std_out
	@rm -f ft_out
	@rm -f $(OBJS) 

fclean: clean
	@$(LOG) "fclean"
	@rm -f std_out
	@rm -f ft_out
	@rm -f $(NAME)

re:
	@$(LOG) "re"
	@make fclean
	@make all
