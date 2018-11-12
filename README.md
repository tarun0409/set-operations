# set-operations


This project aims at:
Providing efficient data structures for representing set and performing fundamental set operations
Comparison of the data structure used with other contemporary data structures and visualizing the differences
Analysis of performance and justification for our choice of data structure
Using sets in a real application and understand how it solves some complex problems in that application

For using the set data structure, include "Set.h" in the cpp file and compile as follows

g++ Set.cpp your_file.cpp -o obj_file


How to run the social network application application

g++ Set.cpp Social_network.cpp -o output


This will give a menu using which:
1. Users can be added to the social network
2. Connections can be made between users
3. Mutual friends can be found (intersection operation)
4. Exclusive friends can be found (difference operation)
5. Friend suggestions (uses union operation)

How to run the test cases

cd Testing
g++ set.cpp RunTestCases.cpp -o output


Analysis
Data obtained by running various test cases are plotted and analysed in the report.
1. Comparison graph with STL insertion
2. Graphs to prove O(n) time complexity of the operations union, intersection and difference.


Conclusion
We conclude with the above as supporting data, that with some optimizations in the operations, our implementation of sets using AVL Tree is performing better than the standard STL implementation of an ordered set in all of the operations for all sized inputs. By extension, due to its logarithmic time insertion and deletion and linear time set operations, it performs better than arrays and standard STL vectors.


