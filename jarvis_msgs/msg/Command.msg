# types of commands
uint8 NAVIGATION     = 0
uint8 MANIPULATION   = 1
uint8 SIMPLE         = 2
uint8 BOOL           = 3
uint8 TRANSPORTATION = 4 # for later
uint8 ANSWER         = 5 # for later -> yes or no 

std_msgs/UInt16 command_type
std_msgs/String[] arguments
