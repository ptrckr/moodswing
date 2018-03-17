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
  enum Instruction {
    // DEBUG
    PRINT_DEBUG_INFO = 0x1819,  // ;^@
  
    // INPUT_OUTPUT
    WRITE_MOOD_REGISTER_TO_STDOUT = 0x0e4a,  // :-O
    WRITE_STACK_TO_STDOUT = 0x0e4b,  // ;-O

    // MATH
    DIVIDE_STACK_VALUE = 0x0c1c,  // :'M
    MULTIPLY_STACK_VALUE = 0x0d06,  // :*M
    ADD_STACK_VALUE = 0x0d54,  // :+M
    SUBTRACT_STACK_VALUE = 0x0df0,  // :-M
    POW_STACK_VALUE = 0x1cde,  // :^M

    // MODES
    ENABLE_INT_OUTPUT = 0x1993,  // =^D
    ENABLE_ASCII_OUTPUT = 0x1f15,  // =^S

    // MOOD_REGISTER
    INCREASE_MOOD_REGISTER_VALUE = 0x0e2b,  // :+R
    DECREASE_MOOD_REGISTER_VALUE = 0x0ed1,  // :-R
    PUSH_MOOD_REGISTER_ON_STACK = 0x267c,  // :vR

    // NOOP
    NOOP_NEGATIVE = 0x076f,  // :-(
    NOOP_POSITIVE = 0x079c,  // :-)

    // STACK
    INCREMENT_STACK_VALUE = 0x0e56,  // :+S
    DECREMENT_STACK_VALUE = 0x0efe,  // :-S
    SUM_STACK_VALUE = 0x143e,  // :=S
    CLEAR_STACK = 0x1f66,  // :_S
    PUSH_ZERO_ON_STACK = 0x26f2,  // :vS
    POP_STACK = 0x2992,  // :~S

    // STATEMENTS
    LOOP_START = 0x0d29,  // :+L
    LOOP_END = 0x0dc3  // :-L
  };
  
  enum Flag {
    ASCII_MODE
  };
  
  enum Mood {
    POSITIVE = -1,
    NEUTRAL = 0,
    NEGATIVE = 1
  };
  
  class MoodSwing {
    std::vector<int> stack;
    int mood_register = 0;

    std::map<Flag, bool> flags = {
      {Flag::ASCII_MODE, false}
    };
    
    Mood GetInstructionMood(std::string instruction) {
      std::regex positive(R"((D|\)|))");
      std::regex neutral(R"((R|O|I|M))");
      std::regex negative(R"((S|L|\())");
      
      if (std::regex_search(instruction, positive)) {
        return Mood::POSITIVE;
      } else if (std::regex_search(instruction, neutral)) {
        return Mood::NEUTRAL;
      } else if (std::regex_search(instruction, negative)) {
        return Mood::NEGATIVE;
      }
      
      return Mood::NEUTRAL;
    }
    
    bool ExecInstruction(int instruction) {
      switch (instruction) {
        // DEBUG
        case Instruction::PRINT_DEBUG_INFO:
          std::cout << "\n>> DEBUG:";
          std::cout << "\n>> * STACK: ";
          
          if (!stack.empty()) {
            std::vector<int>::iterator i;
            for (i = stack.begin(); i != stack.end(); ++i) {
              std::printf("%#06x%s", *i, (i != --stack.end() ? " " : ""));
            }
          } else {
            std::cout << "Empty";
          }
          
          std::printf("\n>> * MOOD_REGISTER: %d\n", mood_register);
          
          break;
          
      
        // INPUT_OUTPUT
        case Instruction::WRITE_MOOD_REGISTER_TO_STDOUT:
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

        case Instruction::WRITE_STACK_TO_STDOUT:
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
      
      
        // MATH
        case Instruction::ADD_STACK_VALUE:
        {
          if (stack.size() < 2) break;
          
          int rhd = stack.back();
          stack.pop_back();
          
          int lhd = stack.back();
          stack.pop_back();
          
          stack.push_back(lhd + rhd);
          
          break;
        }

        case Instruction::SUBTRACT_STACK_VALUE:
        {
          if (stack.size() < 2) break;
          
          int rhd = stack.back();
          stack.pop_back();
          
          int lhd = stack.back();
          stack.pop_back();
          
          stack.push_back(lhd - rhd);
          
          break;
        }

        case Instruction::MULTIPLY_STACK_VALUE:
        {
          if (stack.size() < 2) break;
          
          int rhd = stack.back();
          stack.pop_back();
          
          int lhd = stack.back();
          stack.pop_back();
          
          stack.push_back(lhd * rhd);
          
          break;
        }

        case Instruction::DIVIDE_STACK_VALUE:
        {
          if (stack.size() < 2) break;
          
          int rhd = stack.back();
          stack.pop_back();
          
          int lhd = stack.back();
          stack.pop_back();
          
          stack.push_back(lhd / rhd);
          
          break;
        }
        
        case Instruction::POW_STACK_VALUE:
        {
          if (stack.size() < 2) break;
          
          int exponent = stack.back();
          stack.pop_back();
          
          int base = stack.back();
          stack.pop_back();
          
          stack.push_back(std::pow(base, exponent));
          
          break;
        }
    

        // MODES
        case Instruction::ENABLE_ASCII_OUTPUT:
          flags.at(Flag::ASCII_MODE) = true;
          break;

        case Instruction::ENABLE_INT_OUTPUT:
          flags.at(Flag::ASCII_MODE) = false;
          break;
    
    
        // MOOD_REGISTER
        case Instruction::INCREASE_MOOD_REGISTER_VALUE:
          mood_register += 1;
          break;

        case Instruction::DECREASE_MOOD_REGISTER_VALUE:
          mood_register -= 1;
          break;
          
        case Instruction::PUSH_MOOD_REGISTER_ON_STACK:
          stack.push_back(mood_register);
          break;
          
          
        // NOOP
        case Instruction::NOOP_POSITIVE:
          break;

        case Instruction::NOOP_NEGATIVE:
          break;
          
         
        // STACK
        case Instruction::INCREMENT_STACK_VALUE:
          stack.back() += 1;
          break;

        case Instruction::DECREMENT_STACK_VALUE:
          stack.back() -= 1;
          break;

        case Instruction::SUM_STACK_VALUE:
        {
          int sum = 0;
          
          for (std::vector<int>::iterator i = stack.begin(); i != stack.end(); ++i) {
            sum += *i;
          }
          
          stack.clear();
          stack.push_back(sum);
          
          break;
        }

        case Instruction::CLEAR_STACK:
          stack.clear();
          break;

        case Instruction::PUSH_ZERO_ON_STACK:
          stack.push_back(0);
          break;

        case Instruction::POP_STACK:
          stack.pop_back();
          break;


        // DEFAULT
        default:
          return false;
          break;
      }
      
      return true;
    }
    
  public:
    void ParseInput(std::ifstream &input) {
      std::regex token(R"((:|;|=)(\+|-|\*|\^|~|_|#|v|'|=)(S|R|O|I|D|M|L|\)|\()|@)");
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
            } else {
              mood_register += GetInstructionMood(buff);
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
    std::printf("I/O Error: Missing file argument.\n");
  }
}
