This is an example for semaphore.

In this example, the semaphore allows to manage the Serial port and ensure it is used only by the single active task.

Without the semaphore, text is scrambled.


* Without semaphore

1262m .2 r  2  = G
1262m .3 r   3 = B
1262m .3 r   3 = B
1272m .3 r   3 = B
1272m .3 r   3 = B
1282m .1 r 1   = R
1282m .3 r   3 = B
1282m .3 or   3 = B
1292m .2 or  2  = G
1292m .3 r   3 = B
1292m .3 or   3 = B
1303m .1 or 1   = R
1303m .3 r   3 = B
1303m .3 or   3 = B
1313m .3 r   3 = B
1313m .3 or   3 = B
1323m .1 r 1   = R
1323m .2 r  2  = G
1323m .3 r   3 = B
1323m .3 r   3 = B
1333m .3 r   3 = B
1333m .3 r   3 = B
1343m .1 r 1   = R


* With semaphore

3632    : myEvent3.waitFor   3 = B
3637    : myEvent2.post     2
3639    : myEvent2.waitFor  2  = G
3645    : myEvent1.post    1
3647    : myEvent1.waitFor 1   = R
3682    : myEvent3.post      3
3684    : myEvent3.waitFor   3 = B
3734    : myEvent3.post      3
3736    : myEvent3.waitFor   3 = B
3786    : myEvent3.post      3
3788    : myEvent3.waitFor   3 = B
3838    : myEvent3.post      3
3840    : myEvent3.waitFor   3 = B
3847    : myEvent1.post    1
3849    : myEvent1.waitFor 1   = R
3890    : myEvent3.post      3
3892    : myEvent3.waitFor   3 = B
3939    : myEvent2.post     2
3941    : myEvent2.waitFor  2  = G
3944    : myEvent3.post      3
3947    : myEvent3.waitFor   3 = B
3997    : myEvent3.post      3
3999    : myEvent3.waitFor   3 = B

