#include <cstdio>

int main() {
  int k1, k2;
  int n1[10], n2[10];
  double a1[10], a2[10];
  scanf("%d", &k1);
  for (int i = 0; i < k1; i++) {
    scanf("%d %lf", &(n1[i]), &(a1[i]));
  }
  scanf("%d", &k2);
  for (int i = 0; i < k2; i++) {
    scanf("%d %lf", &(n2[i]), &(a2[i]));
  }
  int n3[20], i = 0, j = 0, k = 0;
  double a3[20];
  while (i < k1 && j < k2) {
    if (n1[i] > n2[j]) {
      n3[k] = n1[i];
      a3[k++] = a1[i++];
    } else if (n1[i] < n2[j]) {
      n3[k] = n2[j];
      a3[k++] = a2[j++];
    } else {
      double sum = a1[i] + a2[j];
      if (sum <= -0.05 || sum >= 0.05) {
        n3[k] = n1[i];
        a3[k++] = sum;
      }
      i++;
      j++;
    }
  }
  while (i < k1) {
    n3[k] = n1[i];
    a3[k++] = a1[i++];
  }
  while (j < k2) {
    n3[k] = n2[j];
    a3[k++] = a2[j++];
  }
  if (!k) {
    printf("0\n");
    return 0;
  }
  printf("%d ", k);
  for (int i = 0; i < k - 1; i++) {
    printf("%d %.1lf ", n3[i], a3[i]);
  }
  printf("%d %.1lf\n", n3[k - 1], a3[k - 1]);
  return 0;
}
