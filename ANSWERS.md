Lab 11: Debugging and Testing (EECS 348)

ANSWERS
Q1: Yes, there is a fault. In fail_lecture, the loop initializer "int i = 1" should be "int i = 0". Index 0 (lecture 1) is never checked, so an absence at lecture 1 is never counted.

Q2: Impossible. The faulty statement is the for-loop initializer, which runs on every call no matter what the input is (even an empty vector). So no test can avoid executing the fault.

Q3: Impossible. The faulty statement sets i = 1 where it should be 0, so the internal state (the loop counter) is wrong immediately after the fault runs. Executing the fault always creates an error state.

Q4: Test case 1 (all present). Error state: i starts at 1 instead of 0. But attendance[0] is 1 (present), so skipping it does not change absent_count. True count 0, actual count 0, both give "no fail". The error state never reaches the output, so there is no failure.

Q5: Test case 2 (absent at lectures 1, 2, 3). True count is 3, so the student should fail. The buggy loop skips index 0 and counts only 2, so it returns false. Wrong output seen by the user, so this is a failure.