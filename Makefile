NAME = webserv

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = HttpRequest.cpp HttpResponse.cpp main.cpp Router.cpp

OBJS = $(SRC:.cpp=.o)

INC = HttpRequest.hpp HttpResponse.hpp Router.hpp

RM = rm -rf

%.o: %.cpp $(INC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

all : $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
