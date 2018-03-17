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
`;^@` PRINT_DEBUG_INFO
  
#### INPUT_OUTPUT
`:-O` WRITE_MOOD_REGISTER_TO_STDOUT
`;-O` WRITE_STACK_TO_STDOUT

#### MATH
`:'M` DIVIDE_STACK_VALUE
`:*M` MULTIPLY_STACK_VALUE
`:+M` ADD_STACK_VALUE
`:-M` SUBTRACT_STACK_VALUE
`:^M` POW_STACK_VALUE

#### MODES
`=^D` ENABLE_INT_OUTPUT
`=^S` ENABLE_ASCII_OUTPUT

#### MOOD_REGISTER
`:+R` INCREASE_MOOD_REGISTER_VALUE
`:-R` DECREASE_MOOD_REGISTER_VALUE
`:vR` PUSH_MOOD_REGISTER_ON_STACK

#### NOOP
`:-(` NOOP_NEGATIVE
`:-)`  NOOP_POSITIVE

#### STACK
`:+S` INCREMENT_STACK_VALUE
`:-S` DECREMENT_STACK_VALUE
`:=S` SUM_STACK_VALUE
`:_S` CLEAR_STACK
`:vS` PUSH_ZERO_ON_STACK
`:~S` POP_STACK

#### STATEMENTS
`:+L` LOOP_START
`:-L` LOOP_END
