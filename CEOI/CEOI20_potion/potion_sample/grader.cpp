#include <bits/stdc++.h>

void init(int N, int D, int F[]);
void curseChanges(int U, int A[], int B[]);
int question(int X, int Y, int V);

int main() {
  int N, D, U, Q;
  freopen("sample-in.txt","r",stdin);
  std::cin >> N >> D >> U >> Q;

  int *F = new int[N];
  for (int i=0; i<N; i++)
    std::cin >> F[i];
  init(N, D, F);

  int *A = new int[U], *B = new int[U];
  for (int i=0; i<U; i++) {
    std::cin >> A[i] >> B[i];
  }
  curseChanges(U, A, B);

  bool correct = true;
  for (int i=0; i<Q; i++) {
    int X,Y,V,CorrectAnswer;
    std::cin >> X >> Y >> V >> CorrectAnswer;
    int YourAnswer = question(X,Y,V);
    if (YourAnswer != CorrectAnswer) {
      std::cout << "WA! Question: " << i
		<< " (X=" << X << ", Y=" << Y << ", V=" << V << ") "
		<<  "Your answer: " << YourAnswer
                << " Correct Answer: " << CorrectAnswer << std::endl;
      correct = false;
    } else {
      std::cerr << YourAnswer << " - OK" << std::endl;
    }
  }

  if (correct) {
    std::cout << "Correct." << std::endl;
  } else std::cout << "Incorrect." << std::endl;
  return 0;
}
