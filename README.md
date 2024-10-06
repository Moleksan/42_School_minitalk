# 42_School_minitalk  
  
Minitalk is a small program that allows communication between a client and a server using UNIX signals. The project’s goal is to understand inter-process communication, signals, and handling errors effectively in C.  
  
# Project Structure  
  
The project consists of two main components:  
  
1. Server: Receives messages from the client and prints them.  
2. Client: Sends a string to the server using UNIX signals (SIGUSR1 and SIGUSR2). 
  
# Features  
  
- The server displays the PID (Process ID) upon startup.  
- The client sends a string to the server using the server’s PID.  
- The server prints the received string quickly and can handle messages from multiple clients without restarting.  
  
# Requirements  
  
- UNIX signals are used for communication (SIGUSR1 and SIGUSR2).  
- The project is written in C and follows the 42 Norm.  
  
# How I Built It  
  
I followed this [comprehensive guide on Minitalk](https://github.com/zelhajou/42cursus-minitalk) which helped me understand the structure and communication flow using signals. Here’s a quick breakdown of how I implemented it:  
  
  1.  Starting with Server:  
    - I used getpid() to get the server's PID and print it.  
    - The server receives signals from the client and reconstructs the message from the bitwise data sent.  
  
  2. Client Implementation:  
  
    - The client uses kill() to send signals (SIGUSR1 for 0, SIGUSR2 for 1) to the server, passing the string character by character in binary.  

  3. Error Handling:  

    - Properly handled signal interruptions using sigaction().  
    - Ensured that no memory leaks occur, and no undefined behavior like segmentation faults or double frees are present.  

  4. Bonus Features:  

    - I added a message acknowledgment system where the server confirms the message's receipt back to the client using signals.  
    - Support for Unicode characters was added, allowing extended character sets to be transmitted.  

### How to Use:  
  
1. Compile the project using make:  
  
    make  

2. Run the server:  
   
   ./server  

Note down the PID displayed by the server.  
3. Run the client, passing the server's PID and the message to be sent:  
  
  ./client [SERVER_PID] "Your message here"  
    
The server will print the message sent by the client.  


Conclusion  
  
This project was a great way to dive deep into how UNIX signals work and how we can use them for communication between processes. By following the guide and adding error-handling mechanisms, I was able to build a solid and functional communication system using C.  
