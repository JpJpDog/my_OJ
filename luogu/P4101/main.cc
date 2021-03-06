//错误！！

//发现玩家可以每轮使一个堆的数量+2
//假如m>=n，如果n为奇数，后玩的必胜，否则先玩的必胜
//再考虑m<n
//假设A先玩，如果m为偶数，A可以在m/2轮时把堆数量变为m强制让B开始，此时n减小m
//那么假设m为偶数，接下来A后玩，则A也可以每次使堆+2，m/2-1轮后轮到B时堆大小为m-1
// B如果继续加原来的堆则可以强制A先玩
//如果B新开一个堆，则A可以继续堆满原来的堆，下一步将新开的堆变为4，相当于A先玩一轮以后（前提是m>=4）
//所以A仍然可以在两个堆后让自己先开始
//假如m为奇数，在m/2-1轮时A面对的情况相当于m为偶数时的第二个堆（m>=4），所以可以永远使自己先开始

//所以如果m为偶数，A可以在堆完奇数个堆时让B先玩，堆完偶数个堆时在让自己先玩
//所以k = n/m，当k为奇数时，A后玩，当n%m为奇数时可以必胜，否则k为偶数时，A先玩n%m为偶数时必胜
//同理 反之则B必胜
//再考虑m<4，则m=2，显然也成立
//如果m为奇数（>4）,则A可以永远先玩，n%m为偶数时必胜
//考虑m=1，A直接输
// m=3，若n%3=0 或 n%3=1 后玩的必胜 因为后玩的可以永远把个数为2的堆填满
//若n%3=2 先玩必胜，假设A先玩，先新开一个2的堆，如果B将它变为3则继续新开，这样最终A必胜。
//如果B也新开，如果只剩下1个则自己合并一下就赢了，因为B也新开的话用用掉的个数肯定为3k+2+2（n>=4），模3为1，所以不可能剩下两个或不剩下。
//剩下3个以上的话填满一个堆又回到了上一种情况。若n<4，则n=2，A也必胜。

#include <cstdio>

bool A_win(int n, int m) {
  if (m == 1 || m == 3 && m % 3 != 2) return false;
  if (m == 3) return true;
  if (m & 1) return (n % m ^ 1);
  return !((n / m & 1) ^ (n % m ^ 1));
}

int main() {
  int T;
  scanf("%d", &T);
  for (int i = 0; i < T; i++) {
    int n, m;
    scanf("%d %d", &n, &m);
    if (A_win(n, m)) {
      printf("0\n");
    } else {
      printf("1\n");
    }
  }
}