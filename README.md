# moodswing
A simple take on an esoteric programming language.

## Hello World
```
=^S :vS :+S :+S :+S :vS :+S :+S :+S :+S
:^S :-S :-S :-S :-S :-S :-S :-S :-S :-S
;-O :vS :+S :+S :vS :+S :+S :+S :+S :+S
:^S :-S :-S :-S :=S ;-O :+S :+S :+S :+S
:+S :+S :+S ;-O ;-O :+S :+S :+S ;-O :_S
:vS :+S :+S :vS :+S :+S :+S :+S :+S :^S
;-O :vS :+S :+S :+S :*S :-S :-S :-S :-S
:-S :-S :-S :-S :-S ;-O :vS :+S :+S :+S
:+S :vS :+S :+S :+S :+S :+S :+S :*S :=S
;-O :+S :+S :+S ;-O :-S :-S :-S :-S :-S
:-S ;-O :-S :-S :-S :-S :-S :-S :-S :-S
;-O :vS :+S :+S :+S :#S ;-O :vS :+S :+S
:vS :+S :+S :+S :^S :+S :+S ;-O

Outputs: Hello World!
```
## Available Instructions

#### STACK<br/>
`:vS` PUSH_ZERO_ON_STACK<br/>
`:~S` POP_STACK<br/>
`:_S` CLEAR_STACK<br/>
`:+S` INCREASE_STACK_VALUE<br/>
`:-S` DECREASE_STACK_VALUE<br/>
`:*S` MULTIPLY_STACK_VALUE<br/>
`:#S` DIVIDE_STACK_VALUE<br/>
`:^S` POWER_STACK_VALUE<br/>
`:=S` SUM_STACK_VALUE<br/>

#### MOOD_REGISTER<br/>
`:+R` INCREASE_MOOD_REGISTER_VALUE<br/>
`:-R` DECREASE_MOOD_REGISTER_VALUE<br/>

#### INPUT_OUTPUT<br/>
`:-O` WRITE_MOOD_REGISTER_TO_STDOUT<br/>
`;-O` WRITE_STACK_TO_STDOUT<br/>

#### MODES
`=^S` ENABLE_ASCII_OUTPUT<br/>
`=^D` ENABLE_INT_OUTPUT<br/>
