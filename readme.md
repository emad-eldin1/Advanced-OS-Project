# Contiguous Memory Allocation Project

**Author:**  عماد الدين عادل محمود رزق اسماعيل

**Level:** 4

**Student ID:** 2000650

**Demo Video For Project:** https://drive.google.com/file/d/1PxW9RXtcS7hRrEQ-unW8KfhOPI0zkFw2/view?usp=sharing 

## Project Description

This project implements a contiguous memory allocation simulator. It allows users to request and release contiguous blocks of memory, compact unused memory holes, and report the status of free and allocated memory regions. The program supports First-fit, Best-fit, and Worst-fit allocation strategies.

## Requirements

* A C++ compiler (e.g., g++)
* A terminal or command prompt to execute the program.
* A text editor (e.g., VS Code) to view and modify the source code (optional).

## Implementation Steps

1.  **Create the Source File:**
    * Open your preferred text editor or IDE (like VS Code).
    * Create a new file named `allocator.cpp`.
    * Copy and paste the provided C++ code into this file.
    * Save the file.

2.  **Compile the Code:**
    * Open your terminal or command prompt.
    * Navigate to the directory where you saved `allocator.cpp`.
    * Use the g++ compiler to compile the code:
        ```bash
        g++ allocator.cpp -o allocator
        ```
        This command will create an executable file named `allocator` in the same directory.

3.  **Run the Program:**
    * Execute the compiled program, providing the initial total memory size in bytes as a command-line argument. For example, to simulate 1 MB (1048576 bytes):
        ```bash
        ./allocator 1048576
        ```
    * The program will start and display the `allocator>` prompt, waiting for your commands.

4.  **Interact with the Allocator:**
    * You can now enter commands to interact with the memory allocator. The available commands are:
        * `RQ <process_name> <size> <strategy>`: Request a contiguous block of memory.
            * `<process_name>`: A string to identify the process (e.g., P1).
            * `<size>`: The amount of memory to request in bytes (e.g., 10000).
            * `<strategy>`: The allocation strategy to use:
                * `F` for First-fit
                * `B` for Best-fit
                * `W` for Worst-fit
            * Example: `RQ P1 10000 F`
        * `RL <process_name>`: Release the memory allocated to a specific process.
            * `<process_name>`: The name of the process to release (e.g., P1).
            * Example: `RL P1`
        * `C`: Compact unused holes of memory into a single block.
            * Example: `C`
        * `STAT`: Report the regions of free and allocated memory, including their addresses and sizes.
            * Example: `STAT`
        * `X`: Exit the program.
            * Example: `X`

## Example Scenario (for Demonstration)

To demonstrate the required scenario involving external fragmentation and compaction, you can use the following sequence of commands after running the program:

1.  **Allocate three processes:**
    ```
    allocator> RQ P1 10000 F
    allocator> RQ P2 20000 F
    allocator> RQ P3 15000 F
    ```

2.  **Check the memory status:**
    ```
    allocator> STAT
    ```

3.  **Release the middle process:**
    ```
    allocator> RL P2
    ```

4.  **Check the memory status again (showing a free hole):**
    ```
    allocator> STAT
    ```

5.  **Attempt to allocate a new process that is larger than any single free block (causing external fragmentation):**
    ```
    allocator> RQ P4 25000 F
    ```
    You should see an error message indicating that there is not enough contiguous memory.

6.  **Perform memory compaction:**
    ```
    allocator> C
    ```

7.  **Check the memory status after compaction (showing a single larger free block):**
    ```
    allocator> STAT
    ```

8.  **Allocate the previously failed process again (now it should succeed):**
    ```
    allocator> RQ P4 25000 F
    ```

9.  **Check the final memory status:**
    ```
    allocator> STAT
    ```

10. **Exit the program:**
    ```
    allocator> X
    ```

By following these steps, you can successfully run the contiguous memory allocation simulator and demonstrate its functionality, including handling memory requests, releases, external fragmentation, and compaction.