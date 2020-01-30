Link to github -https://github.com/ofekbr/ex4

In this project we created a parallel server based on SOLID principles and design patters like bridge, object adapter and open-closed.
Our server recieves a problem from a client and send back a solution.
In this milestone we recieved a matrix with cost for each point with start\end coordinates and we returned the shorthest path with its cost.

The algorithms we tested : BFS, DFS, Best First Search and A Star.
We conducted an expirement with 10 different matrixes for each algorithm and found out that A Star is the best, so we used A Star for our server.

The flow of the program :
- a client connects to the server and sends a problem.
- ClientHandler searches for an old solution that already exists in cache, or solve the problem to create a new solution.
- Store the new solution in a file.
- Send the solution to the client.

Use c++14 in order to compile our code, and run it with the server's port as the 1st argument.
For example "./a.out 12345"