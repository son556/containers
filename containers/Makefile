NAME = STL

## ANSI escape code
# CYAN  := \033[1;36;40m
# RESET := \033[0m

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
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) 

$(OBJS): %.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	@erase std_out
	@erase ft_out
	@erase $(OBJS) 

fclean: clean
	@erase std_out
	@erase ft_out
	@erase $(NAME).exe

re:
	@make fclean
	@make all
