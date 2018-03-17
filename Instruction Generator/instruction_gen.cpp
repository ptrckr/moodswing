//
//  Created by ptrckr on 15.03.18.
//  Copyright © 2018 Patrick Rügheimer. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

class InstructionGenerator {
  std::map<std::string, std::map<int, std::map<std::string, std::string>>> instructions;
  
  bool IsInstructionValid(std::string instruction) {
    std::regex instruction_regex(R"((:|;|=)(\+|-|\*|\^|~|_|#|v|'|=)(S|R|O|I|D|M|L|\)|\()|@)");
    return std::regex_search(instruction, instruction_regex);
  }
  
  int GetInstructionValue(std::string token) {
    return token[0] + token[1] + token[2] * token[1];
  }
  
public:
  InstructionGenerator() {
    PushInstruction("STACK",         "PUSH_ZERO_ON_STACK",            ":vS");
    PushInstruction("STACK",         "POP_STACK",                     ":~S");
    PushInstruction("STACK",         "CLEAR_STACK",                   ":_S");
    PushInstruction("STACK",         "INCREMENT_STACK_VALUE",         ":+S");
    PushInstruction("STACK",         "DECREMENT_STACK_VALUE",         ":-S");
    PushInstruction("STACK",         "SUM_STACK_VALUE",               ":=S");

    PushInstruction("MATH",          "ADD_STACK_VALUE",               ":+M");
    PushInstruction("MATH",          "SUBTRACT_STACK_VALUE",          ":-M");
    PushInstruction("MATH",          "MULTIPLY_STACK_VALUE",          ":*M");
    PushInstruction("MATH",          "DIVIDE_STACK_VALUE",            ":'M");
    PushInstruction("MATH",          "POW_STACK_VALUE",               ":^M");

    PushInstruction("MOOD_REGISTER", "INCREASE_MOOD_REGISTER_VALUE",  ":+R");
    PushInstruction("MOOD_REGISTER", "DECREASE_MOOD_REGISTER_VALUE",  ":-R");
    PushInstruction("MOOD_REGISTER", "PUSH_MOOD_REGISTER_ON_STACK",   ":vR");

    PushInstruction("INPUT_OUTPUT",  "WRITE_MOOD_REGISTER_TO_STDOUT", ":-O");
    PushInstruction("INPUT_OUTPUT",  "WRITE_STACK_TO_STDOUT",         ";-O");

    PushInstruction("MODES",         "ENABLE_ASCII_OUTPUT",           "=^S");
    PushInstruction("MODES",         "ENABLE_INT_OUTPUT",             "=^D");

    PushInstruction("NOOP",          "NOOP_POSITIVE",                 ":-)");
    PushInstruction("NOOP",          "NOOP_NEGATIVE",                 ":-(");

    PushInstruction("STATEMENTS",    "LOOP_START",                    ":+L");
    PushInstruction("STATEMENTS",    "LOOP_END",                      ":-L");

    PushInstruction("DEBUG",         "PRINT_DEBUG_INFO",              ";^@");

    PrintInstructions();
  }

  bool PushInstruction(std::string instruction_namespace, std::string name, std::string instruction) {
    if (IsInstructionValid(instruction)) {
      int instruction_value = GetInstructionValue(instruction);
      
      std::map<int, std::map<std::string, std::string>>::iterator dupe_key;
      if (instructions.find(instruction_namespace) != instructions.end() && !instructions.at(instruction_namespace).empty()) {
        dupe_key = instructions[instruction_namespace].find(instruction_value);
        
        if (dupe_key != instructions[instruction_namespace].end()) {
          std::printf("[ERROR: `%s' value is already in use by `%s'!]\n", name.c_str(), (*dupe_key).second.at("name").c_str());
          return false;
        }
      }
      
      instructions[instruction_namespace][instruction_value].insert(
        std::pair<std::string, std::string>(
          "name", name
        )
      );
      
      instructions[instruction_namespace][instruction_value].insert(
        std::pair<std::string, std::string>(
          "instruction", instruction
        )
      );

      return true;
    } else {
      std::printf("[ERROR: %s is not a valid instruction!]\n", instruction.c_str());
      
      return false;
    }
  }
  
  void PrintInstructions() {
    std::map<std::string, std::map<int, std::map<std::string, std::string>>>::iterator i;
    for (i = instructions.begin(); i != instructions.end(); ++i) {
      const std::string &instruction_namespace = i->first;
      const std::map<int, std::map<std::string, std::string>> &instruction_pair = i->second;
      
      std::printf("// %s\n", instruction_namespace.c_str());
      
      std::map<int, std::map<std::string, std::string>>::const_iterator j;
      for (j = instruction_pair.begin(); j != instruction_pair.end(); ++j) {
        const std::string &key = j->second.at("name");
        const std::string &value = j->second.at("instruction");
        
        std::printf(
          "%s = %#06x%s  // %c%c%c\n",
          key.c_str(),
          value[0] + value[1] + value[2] * value[1],
          ((j != --instruction_pair.end() || i != --instructions.end()) ? "," : ""),
          value[0], value[1], value[2]
        );
      }
      
      if (i != --instructions.end()) std::printf("\n");
    }
  }
};
