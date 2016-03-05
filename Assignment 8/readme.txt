The multithreading performance was definitely faster but it was not faster by a factor of 2, 4 or 8.
The issue I had was that when I first attempted to assign a skip value(every nth number), the number
was created within the for loop and therefore it was GC'd half way through every thread's execution,
which caused blank lines and confusion for debugging. I eventually found out the reason and used an
array of gaps which helped the process(since the values now persist). 

 The implementation worked for 2 and 4 threads pretty well, but when it got to 8, it was actually slower because it was "mimic"-ing multithreading since my MacBook only has 4 cores. 
