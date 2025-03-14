#include <bitset>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

const long long MAX_TAPE_SIZE = 4000000010;
const long long TAPE_OFFSET = 2000000000;

std::bitset<MAX_TAPE_SIZE> tape;

std::pair<int, int> interpret(std::string p, long long max_steps = 2000000000) {
  int n = (int)p.length();

  tape.reset();
  std::vector<int> jump_addr(n + 1, 0);
  std::vector<int> pstack;

  for (int i = 0; i < n; i++) {
    if (p.at(i) == '(') {
      jump_addr[i] = -1;
      pstack.push_back(i);
    } else if (p.at(i) == ')') {
      if (!pstack.empty()) {
        int openidx = pstack.back();
        pstack.pop_back();
        jump_addr[openidx] = i;
        jump_addr[i] = openidx;
      } else {
        jump_addr[i] = -1;
      }
    }
  }

  long long idx = 0;
  long long min_idx = idx;
  long long max_idx = idx;
  int pc = 0;
  long long scount = 0;

  while (pc != n) {
    switch (p.at(pc)) {
    case '*':
      tape[idx + TAPE_OFFSET].flip();
      pc++;
      break;
    case '<':
      idx--;
      pc++;
      break;
    case '>':
      idx++;
      pc++;
      break;
    case '(':
      if (!tape[idx + TAPE_OFFSET]) {
        if (jump_addr[pc] != -1) {
          pc = jump_addr[pc] + 1;
        } else {
          std::cout << "closing jump not found" << std::endl;
          exit(1);
          return {-2, scount};
        }
      } else {
        pc++;
      }
      break;
    case ')':
      if (tape[idx + TAPE_OFFSET]) {
        if (jump_addr[pc] != -1) {
          pc = jump_addr[pc] + 1;
        } else {
          std::cout << "open jump not found" << std::endl;
          exit(1);
          return {-2, scount};
        }
      } else {
        pc++;
      }
      break;
    }
    if (idx < min_idx)
      min_idx = idx;
    if (idx > max_idx)
      max_idx = idx;

    scount++;
    if (scount > max_steps) {
      return {-1, scount};
    }
  }
  return {max_idx - min_idx + 1, scount};
}

double score(int S) {
  if (1 <= S && S <= 50)
    return 5.0;
  else if (51 <= S && S <= 23100)
    return 6.9 * log2l(S - 49);
  else if (23101 <= S)
    return 100.0;
  return 0.0;
}

int main() {
  std::string program;
  std::cin >> program;
  if (program.size() > 49) {
    std::cout << "The program is too long." << std::endl;
    exit(1);
  }
  auto result = interpret(program);
  if (result.first == -1) {
    std::cout << "Too many instructions." << std::endl;
    exit(1);
  }
  std::cout << "Number of reached cells: " << result.first << std::endl;
  std::cout << "Instruction count: " << result.second << std::endl;
  std::cout << "Score: " << std::fixed << std::setprecision(2)
            << score(result.first) << std::endl;
  return 0;
}
/*

-------------------------------------------------

*<<<<<<*(>*)*(>>(*>(>)>(>)*>*>*>*(<)<(<)>)*(<*)<)

*<<<<<<<<<<*(>*)*(>>(*>(>)>(>)*>*(<)<(<)>)*(<*)<)

*/
