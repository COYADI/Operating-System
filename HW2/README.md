1. gcc os-hw2-1.c –lpthread –o os-hw2-1
	./os-hw2-1 and enter the numbers.

	這一題是用 thread 去做尋找 max, min, avg 的數字，在三個 thread 中都傳入 一個陣列之後，陣列第一個數字是 argc，代表有幾個數字，而後面則為 argv[]存取數字的陣列，最後執行緒分別回傳我們要的 max, min, avg 值。

2. gcc os-hw2-2.c-lpthread –o os-hw2-2
	./os-hw2-2

	這一題是用執行緒估算 pi的值，使用執行緒產生很多 x, y 分別介在-1 到 1 之間的座標，並用蒙地卡羅法估算。
