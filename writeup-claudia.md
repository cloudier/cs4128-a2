[2006 North America East Central NA Regional](https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=261)
Claudia Tu z3459448

# 3726 They go to the regionals
Use counting sort on the length of the strings. Then go through the array
containing the results of the counting sort from smallest number to
largest number, and assign strings to groups by length. For example, if
you have a group size of 3 and the array says you have 3 group members
with string length 3, one with string length 7, one with string length 8
and one with string length 9, the ones with string length 3 go into the
first group and the rest go into a second group. Then check that each
of these groups satisfy the condition that each member of the group has
a name with a length that is within 2 of the group average.

# 3724 Caterpillar
Use union find to check that graph is acyclic and connected. If it is,
then remove all the nodes with only one outgoing edge and check the
remaining graph to make sure at most two nodes have 1 outgoing edge and
the rest have 2.

One problem I ran into with this problem was that I added a break when
taking in input if we found that the graph had a cycle. This meant that
the program didn't correctly process subsequent input.

# 3730 Snakes on a plane
For each snake, find the head and the tail. Use union find to check if
lengthening the head or tail will cause the snake to touch another snake
or loop back on itself.

# 3727 The mastermind master's mind
Not attempted.
