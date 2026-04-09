# Compiler1

직접 정의한 C 유사 언어를 자체 바이트코드로 컴파일하고, 내장 인터프리터로 실행하는 미니 컴파일러 프로젝트입니다.

언어 규칙, 재귀 하강 파서, AST 기반 코드 생성기, 정적 메모리 기반 단순 VM을 사용하는 바이트코드 실행기 등을 구현했습니다.

## 프로젝트 개요

- 입력 언어: C 문법과 닮은 자체 언어
- 출력 대상: 별도 명령 집합을 갖는 자체 바이트코드
- 실행 방식: 생성된 바이트코드를 내장 인터프리터가 즉시 실행
- 구현 방식: 재귀 하강 파서 + AST + 단순 코드 생성기
- 개발 환경: Visual Studio C++ 프로젝트 (`.sln`, `.vcxproj`)
- 외부 소스 파일을 읽지 않고, [`Compiler1/test_programs.h`](/C:/Users/mkkim/myfolder/mainfolder/projects/source/repos/Compiler1/Compiler1/test_programs.h)의 `test1`, `test2`, `test3` 중 하나를 `main`에서 선택해 입력으로 사용합니다.

## 타겟 언어 설명

### 언어 특성

- 자료형은 `int` 하나만 사용합니다.
- 모든 변수는 주소를 명시적으로 선언합니다.
- 실행 시 하나의 선형 메모리 공간만 존재합니다.
- 스택, 힙, 데이터 세그먼트가 분리되어 있지 않습니다.

### 주요 문법

- 선언: `int x : 1;` (`n`은 메모리 주소 `1`을 사용합니다.)
- 블록: `{ ... }`
- 라벨: `label LOOP:`
- 대입: `x = expr;`
- 조건문: `if (...) ... else ...`
- 반복문: `while (...) ...`, `for (...) ...`
- 입출력: `read x;`, `write expr;`, `writec expr;`
- 분기: `goto expr;`
- 단항 연산자  `*`, `&`로 포인터 연산을 지원합니다.
- 함수 선언/호출/재귀는 지원하지 않습니다.

### 예제

```c
int a : 1;
int b : 2;
a = 3;
b = a * 3;
for (int c : 3; c = 1; c <= 10; c = c + 1) {
    b = b + 1;
    write b;
    writec 10;
}
if (a == 3) writec 65;
else writec 66;
```

## 타겟 바이트코드

바이트코드 명세는 [`Compiler1/target_byte_code.txt`](/C:/Users/mkkim/myfolder/mainfolder/projects/source/repos/Compiler1/Compiler1/target_byte_code.txt)에 정리되어 있습니다.

대표 명령 예시

- `MOC A C`: 상수 `C`를 주소 `A`에 저장
- `MOV A B`: 주소 `B`의 값을 주소 `A`로 복사
- `MOP A B`: `A = *B`
- `MOA A B`: `*A = B`
- `JMC C`: 상수 주소 `C`로 점프
- `JNC C B`: `B`가 0이면 `C`로 점프
- `WRI A`: 정수 출력
- `WRC A`: 문자 출력

## 소스 파일 가이드

- [`Compiler1/Compiler1.cpp`](/C:/Users/mkkim/myfolder/mainfolder/projects/source/repos/Compiler1/Compiler1/Compiler1.cpp): 전체 파이프라인 실행 진입점
- [`Compiler1/LexialAnalyzer.cpp`](/C:/Users/mkkim/myfolder/mainfolder/projects/source/repos/Compiler1/Compiler1/LexialAnalyzer.cpp): 어휘 분석
- [`Compiler1/Parser.cpp`](/C:/Users/mkkim/myfolder/mainfolder/projects/source/repos/Compiler1/Compiler1/Parser.cpp): 재귀 하강 파싱
- [`Compiler1/ParseTreeComponents.h`](/C:/Users/mkkim/myfolder/mainfolder/projects/source/repos/Compiler1/Compiler1/ParseTreeComponents.h): AST 정의
- [`Compiler1/Instructor.cpp`](/C:/Users/mkkim/myfolder/mainfolder/projects/source/repos/Compiler1/Compiler1/Instructor.cpp): AST -> 바이트코드 변환
- [`Compiler1/InstructedProgram.cpp`](/C:/Users/mkkim/myfolder/mainfolder/projects/source/repos/Compiler1/Compiler1/InstructedProgram.cpp): 생성된 바이트코드 저장과 라벨 후처리
- [`Compiler1/Interpreter.cpp`](/C:/Users/mkkim/myfolder/mainfolder/projects/source/repos/Compiler1/Compiler1/Interpreter.cpp): 바이트코드 실행기
- [`Compiler1/Language Rule.txt`](/C:/Users/mkkim/myfolder/mainfolder/projects/source/repos/Compiler1/Compiler1/Language%20Rule.txt): 언어 문법 초안
- [`Compiler1/target_byte_code.txt`](/C:/Users/mkkim/myfolder/mainfolder/projects/source/repos/Compiler1/Compiler1/target_byte_code.txt): VM 명령 집합 설명
