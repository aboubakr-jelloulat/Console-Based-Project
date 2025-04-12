GREEN 	= \033[1;32m
RED 	= \033[1;31m
BLUE 	= \033[1;34m
RESET 	= \033[0m

NAME 	= Bank

CXX 	= c++
CXXFLAGS = -std=c++11 -Wno-return-type -Wno-switch -fdeclspec # -Wno-return-type -Wno-switch -fdeclspec __declspec -> visual code Microsoft


SRC_DIR = src
INC_DIR = includes

SRCS 	= $(wildcard $(SRC_DIR)/*.cpp) Main.cpp
OBJS 	= $(SRCS:.cpp=.o)
HEADERS = $(wildcard $(INC_DIR)/*.h)

all: $(NAME) 

$(NAME): $(OBJS)
	@echo "$(BLUE)🎯 Compiling $(NAME)...$(RESET)"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ Compilation successful! Run with ./$(NAME)$(RESET)"

%.o: %.cpp $(HEADERS)
	@echo "$(BLUE)🔄 Compiling $<...$(RESET)"
	@$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	@echo "$(RED)❌ Removing object files...$(RESET)"
	@rm -f $(OBJS)

fclean: clean
	@echo "$(RED)❌ Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)

clear :
	clear

re: fclean all 

practice : all clean  clear

.PHONY : clean clear
