This is an example for semaphore.

In this example, the semaphore allows to manage the Serial port and ensure it is used only by the single active task.

Without the semaphore, text is scrambled.


* Without semaphore

0	: mySemaphore1    1
10	: mySemaphore2     2
30	: mySemaphore3      3
42	: mySemaphore2     2
72	: mySemaphore1    1
74	: mySemaphore2     2
106	: mySemaphore2     2
138	: mySemaphore2     2
144	: mySemaphore1    1
152	: mySemaphore3      3
170	: mySemaphore2     2
202	: mySemaphore2     2
216	: mySemaphore1    1
234	: mySemaphore2     2
266	: mySemaphore2     2
274	: mySemaphore3      3
288	: mySemaphore1    1
298	: mySemaphore2     2
330	: mySemaphore2     2
360	: mySemaphore1    1  362	: mySemaphore2     2
394	: mySemaphore2     2 396	: mySemaphore3      3
426	: mySemaphore2     2
432	: mySemaphore1    1
458	: mySemaphore2     2

* With semaphore

0	: mySemaphore1    1
10	: mySemaphore2     2
30	: mySemaphore3      3
82	: mySemaphore3      3
134	: mySemaphore3      3
186	: mySemaphore3      3
202	: mySemaphore1    1
238	: mySemaphore3      3
290	: mySemaphore3      3
312	: mySemaphore2     2
342	: mySemaphore3      3
394	: mySemaphore3      3
404	: mySemaphore1    1
446	: mySemaphore3      3
498	: mySemaphore3      3
550	: mySemaphore3      3
602	: mySemaphore3      3
606	: mySemaphore1    1
614	: mySemaphore2     2
654	: mySemaphore3      3
706	: mySemaphore3      3
758	: mySemaphore3      3
