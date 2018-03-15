//
//  Created by ptrckr on 15.03.18.
//  Copyright © 2018 Patrick Rügheimer. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <regex>

namespace moodswing {
  enum Token {
    // STACK
    PUSH_ZERO_ON_STACK = 9970,  // :vS
    POP_STACK = 10642,  // :~S
    CLEAR_STACK = 8038,  // :_S
    INCREASE_STACK_VALUE = 3670,  // :+S
    DECREASE_STACK_VALUE = 3838,  // :-S
    MULTIPLY_STACK_VALUE = 3586,  // :*S
    DIVIDE_STACK_VALUE = 2998,  // :#S
    POWER_STACK_VALUE = 7954,  // :^S
    SUM_STACK_VALUE = 5182,  // :=S
    
    // MOOD_REGISTER
    INCREASE_MOOD_REGISTER_VALUE = 3627,  // :+R
    DECREASE_MOOD_REGISTER_VALUE = 3793,  // :-R
    
    // INPUT_OUTPUT
    WRITE_MOOD_REGISTER_TO_STDOUT = 3658,  // :-O
    WRITE_STACK_TO_STDOUT = 3659,  // ;-O
    
    // MODES
    ENABLE_ASCII_OUTPUT = 7957,  // =^S
    ENABLE_INT_OUTPUT = 6547  // =^D
  };
  
  enum Flag {
    ASCII_MODE
  };
  
  class MoodSwing {
    std::vector<int> stack;
    int mood_register = 0;

    std::map<Flag, bool> flags = {
      {Flag::ASCII_MODE, false}
    };
    
    bool ExecInstruction(int token) {
      switch (token) {
        // STACK
        case Token::PUSH_ZERO_ON_STACK:
          stack.push_back(0);
          break;

        case Token::POP_STACK:
          stack.pop_back();
          break;

        case Token::CLEAR_STACK:
          stack.clear();
          break;
          
        case Token::INCREASE_STACK_VALUE:
          stack.back() += 1;
          break;

        case Token::DECREASE_STACK_VALUE:
          stack.back() -= 1;
          break;

        case Token::MULTIPLY_STACK_VALUE:
        {
          if (stack.size() < 2) break;
          
          int rhd = stack.back();
          stack.pop_back();
          
          int lhd = stack.back();
          stack.pop_back();
          
          stack.push_back(lhd * rhd);
          
          break;
        }

        case Token::DIVIDE_STACK_VALUE:
        {
          if (stack.size() < 2) break;
          
          int rhd = stack.back();
          stack.pop_back();
          
          int lhd = stack.back();
          stack.pop_back();
          
          stack.push_back(lhd / rhd);
          
          break;
        }
          
        case Token::POWER_STACK_VALUE:
        {
          if (stack.size() < 2) break;
          
          int exponent = stack.back();
          stack.pop_back();
          
          int base = stack.back();
          stack.pop_back();
          
          stack.push_back(std::pow(base, exponent));
          
          break;
        }
          
        case Token::SUM_STACK_VALUE:
        {
          int sum = 0;
          
          for (std::vector<int>::iterator i = stack.begin(); i != stack.end(); ++i) {
            sum += *i;
          }
          
          stack.clear();
          stack.push_back(sum);
          
          break;
        }

        // MOOD_REGISTER
        case Token::INCREASE_MOOD_REGISTER_VALUE:
          mood_register += 1;
          break;

        case Token::DECREASE_MOOD_REGISTER_VALUE:
          mood_register -= 1;
          break;

        // INPUT_OUTPUT
        case Token::WRITE_MOOD_REGISTER_TO_STDOUT:
          if (flags.at(Flag::ASCII_MODE)) {
            char o = static_cast<char>(mood_register);
            
            if (o == 68) {
              std::cout << (mood_register > 0 ? ":" : "") << o << (mood_register <= 0 ? ":" : "");
            } else {
              std::cout << o;
            }
          } else {
            std::cout << mood_register;
          }
          
          break;

        case Token::WRITE_STACK_TO_STDOUT:
          if (flags.at(Flag::ASCII_MODE)) {
            char o = static_cast<char>(stack.back());
            
            if (o == 68) {
              std::cout << (mood_register > 0 ? ":" : "") << o << (mood_register <= 0 ? ":" : "");
            } else {
              std::cout << o;
            }
          } else {
            std::cout << stack.back();
          }
          
          break;

        // MODES
        case Token::ENABLE_ASCII_OUTPUT:
          flags.at(Flag::ASCII_MODE) = true;
          break;

        case Token::ENABLE_INT_OUTPUT:
          flags.at(Flag::ASCII_MODE) = false;
          break;
          
        default:
          return false;
          break;
      }
      
      return true;
    }
    
  public:
    void ParseInput(std::ifstream &input) {
      std::regex token(R"((:|;|=)(\+|-|\*|\^|~|_|#|v|=)(S|R|O|I|D|\)|\())");
      int current_line = 1;
      char buff[4] = {'\0'};
      
      while (input.peek() != std::char_traits<char>::eof()) {
        while (std::isspace(input.peek())) {
          if (input.get() == 10) current_line += 1;
        }
        
        input.read(buff, 3);
        
        if (input.gcount() == 3) {
          if (std::regex_search(buff, token)) {
            if (!ExecInstruction(buff[0] + buff[1] + buff[2] * buff[1])) {
              std::printf("Parse Error: Token `%s' does not exist on line %d.\n", buff, current_line);
              return;
            }
          } else {
            std::printf("Parse Error: Token `%s' contains invalid characters on line %d.\n", buff, current_line);
            return;
          }
        } else if (input.gcount() != 0) {
          std::printf("Parse Error: Reached EOF mid instruction.\n");
          return;
        }
      }
    }
  };
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    std::ifstream input(argv[1], std::ios::in);
    
    if (input.is_open()) {
      moodswing::MoodSwing ms;
      ms.ParseInput(input);
      input.close();
    } else {
      std::printf("I/O Error: Input file could not be opened.\n");
    }
  } else {
    std::printf("I/O Error: Missing file argument.");
  }
}
