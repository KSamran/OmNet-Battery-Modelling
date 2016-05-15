# OmNet-Battery-Modelling
Simulation Design:
Firstly, the structure of the simulation model is describes in the ‘Energy_consumption_model.ned’ file using NED
language. This helps to declare the connections between the sub modules and declare the simple module. Also
parameters, input and output gates are also declared in the same file. Parameters are variables that belong to a module.
Parameters can be used in building the topology (number of nodes, etc), and to supply input to C++ code that
implements simple modules and channels. In our network the channel between the sender and receiver is set with the
constant delay of 100 milliseconds.
Connections between the sub modules are defined in the connections section of simple modules. Connection is provided
using input gate of the sender to output gate of receiver. Input and output gates are connected with a normal arrow. After
that Configuration and input data for the simulation are in a configuration file usually called 'omnetpp.ini' and the
module is implemented using in ‘Energy_consumption_model.cc’ file.

How to compile?
- First Install Omnetpp
- Create new project
- Add three file as attached
