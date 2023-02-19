# Process-Hierarchy
To simulate process creation and destruction when implemented with linked lists.

Specification: 
The program creates/destroys child processes based on choosing from a menu of choices, where 
each choice calls the appropriate procedure, where the choices are:  
1) Initialize process hierarchy 
2) Create a new child process  
3) Destroy all descendants of a parent process  
4) Quit program and free memory 


This code defines a data structure for a process control block (PCB), which is used by operating systems to manage processes. The PCB contains information about a process, such as its parent process, children processes, and other relevant data. The code allows for the creation and destruction of child processes, as well as printing out the hierarchy of processes.

The code defines three structures: node, pcb, and linked_list. node is a structure used to create a linked list of child processes. linked_list is a typedef for node, which makes it easier to use the node structure as a linked list. pcb is a structure that contains information about a process, such as its parent process and its children processes.

The code also defines a global constant, MAX_PROCESSES, which is the maximum number of processes that can be managed by the operating system. It also declares an array of pcb_type pointers, pcb_array, which is used to store the PCBs of each process.

The code has four functions:

HierarchyPrint(): This function prints out the hierarchy of processes by iterating over the pcb_array and printing out the process ID, parent process ID, and children processes for each process in the array.

Initialize(): This function initializes the PCB for the root process, which is assigned index 0 in the pcb_array. It then calls HierarchyPrint() to print out the hierarchy of processes.

CreateNewChild(): This function prompts the user to enter the ID of a parent process and then creates a new child process for that parent. It does this by finding the first available index in the pcb_array, allocating memory for a new pcb_type and linked_list, and updating the parent process's children linked list with the new child process. It then calls HierarchyPrint() to print out the hierarchy of processes.

DestroyChildren(): This function is a recursive function that destroys all the child processes of a given process. It does this by iterating over the children of the process, calling itself recursively on each child, and then freeing the memory allocated for the child's PCB and linked_list. It also sets the corresponding index in pcb_array to NULL.
