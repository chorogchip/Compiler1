#pragma once
#include<string>


static std::string test1(R"pro%gram(
int a : 1;
int b : 2;
a = 3;
b = a * 3;
for (int c : 3; c = 1;  c <= 10; c = c + 1) {
    b = b + 1;
    write b;
    writec 10;
}
if (a == 3) writec 65;
else writec 66;
)pro%gram");

static std::string test2(R"pro%gram(
int n : 1;
read n;
for (int i : 2; i = 2; i * i < n; i = i + 1) {
	if (n % i == 0) 
		goto NO;
}
write 1;
goto E;
label NO:
write 0;
label E:
)pro%gram");

static std::string test3(R"pro%gram(
int n : 1;
read n;
int C : 100;
int Cend : 1000;
for (int i : 2; i = 0; i <= n; i = i + 1) {
	int p : 3;
	p = 100 + i;
	p = &0;
}
for (int i : 2; i = 2; i * i <= n; i = i + 1)
	if (*(100 + i) == 0) {
		for (int j : 3; j = i * i; j <= n; j = j + i) {
			int p : 4;
			p = 100 + j;
			p = &1;
		}
		write i;
		writec 10;
	}
writec 65 + 4;
writec 65 + 13;
writec 65 + 3;
writec 10;
)pro%gram");