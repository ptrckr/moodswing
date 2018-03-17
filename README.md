# moodswing
A simple take on an esoteric programming language.

## Hello World
```
=^S :vS :+S :+S :+S :vS :+S :+S :+S :+S
:^M :-S :-S :-S :-S :-S :-S :-S :-S :-S
;-O :vS :+S :+S :vS :+S :+S :+S :+S :+S
:^M :-S :-S :-S :=S ;-O :+S :+S :+S :+S
:+S :+S :+S ;-O ;-O :+S :+S :+S ;-O :_S
:vS :+S :+S :vS :+S :+S :+S :+S :+S :^M
;-O :vS :+S :+S :+S :*M :-S :-S :-S :-S
:-S :-S :-S :-S :-S ;-O :vS :+S :+S :+S
:+S :vS :+S :+S :+S :+S :+S :+S :*M :=S
;-O :+S :+S :+S ;-O :-S :-S :-S :-S :-S
:-S ;-O :-S :-S :-S :-S :-S :-S :-S :-S
;-O :vS :+S :+S :+S :'M ;-O :vS :+S :+S
:vS :+S :+S :+S :^M :+S :+S ;-O

Outputs: Hello World!
```
## Available Instructions

#### DEBUG
`;^@` PRINT_DEBUG_INFO<br/>
  
#### INPUT_OUTPUT
`:-O` WRITE_MOOD_REGISTER_TO_STDOUT<br/>
`;-O` WRITE_STACK_TO_STDOUT<br/>

#### MATH
`:'M` DIVIDE_STACK_VALUE<br/>
`:*M` MULTIPLY_STACK_VALUE<br/>
`:+M` ADD_STACK_VALUE<br/>
`:-M` SUBTRACT_STACK_VALUE<br/>
`:^M` POW_STACK_VALUE<br/>

#### MODES
`=^D` ENABLE_INT_OUTPUT<br/>
`=^S` ENABLE_ASCII_OUTPUT<br/>

#### MOOD_REGISTER
`:+R` INCREASE_MOOD_REGISTER_VALUE<br/>
`:-R` DECREASE_MOOD_REGISTER_VALUE<br/>
`:vR` PUSH_MOOD_REGISTER_ON_STACK<br/>

#### NOOP
`:-(` NOOP_NEGATIVE<br/>
`:-)`  NOOP_POSITIVE<br/>

#### STACK
`:+S` INCREMENT_STACK_VALUE<br/>
`:-S` DECREMENT_STACK_VALUE<br/>
`:=S` SUM_STACK_VALUE<br/>
`:_S` CLEAR_STACK<br/>
`:vS` PUSH_ZERO_ON_STACK<br/>
`:~S` POP_STACK<br/>

#### STATEMENTS
`:+L` LOOP_START<br/>
`:-L` LOOP_END
