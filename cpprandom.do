* set up a blank variable
clear
set obs 10000
gen u = .

* load the C++ plugin (this assumes that "cpprandom.plugin" is in the current ado path
program cpprandom, plugin

* generate the uniform variables in u
plugin call cpprandom u

* summarize the variables
summ u

* draw a histogram for sanity check
hist u

* check that "if .." works
li if _n < 10
plugin call cpprandom u if _n < 5
li if _n < 10

* check the error handling (no variable specified)
plugin call cpprandom

* check if invalid variable specified
plugin call cpprandom nonexistentvariable

* unload the plugin
program drop cpprandom
