Written Comparison:
Lines of code:
Part A needs about 30 lines just for memory management. Part B needs 0 lines of memory management code. unique_ptr handles all of it automatically.

Safety:
Part A has multiple ways to go wrong; you can forget a delete (memory leak), delete something twice (double free), or read memory after deleting it (use-after-free). All three were proved.  Part B can't have any of those bugs because unique_ptr automatically deletes memory when it's done, and the compiler won't even let you accidentally copy it.

Complexity:
Part A forces you to implement the Rule of Three correctly or your program will crash or leak. If you forget even one of the three functions, things go wrong in subtle ways that are hard to debug. Part B doesn't need the Rule of Three at all;the compiler handles everything.

**Note** : "- Clean compilation with -Wall -Wextra -fsanitize=address" since the asignment said this I added main function for part a and b, to prove they can compile with that code