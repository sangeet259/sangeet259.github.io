#include <bits/stdc++.h>
using namespace std;
#define infinity numeric_limits<int>::max()
#define minusInf numeric_limits<int>::min()

struct interval{
  double l;
  double r;
};

bool mySort(interval a, interval b) {
  if(a.l < b.l)
    return true;
  else if(a.l > b.l) 
    return false;
  else if(a.l == b.l) {
    if(a.r > b.r)
      return true;
    return false;
  }
}

int main() {
  int n,l,w;
  while(cin>>n>>l>>w) {
    int *r,*pos;
    interval *v;
    v = new interval[n];
    r = new int[n];
    pos = new int[n];
    for(int i=0;i<n;i++) {
      cin>>pos[i]>>r[i];
      if(double(r[i])>double(w)/2.00) {
        double dx = sqrt( pow(r[i],2) - pow((double(w)/2.00),2) );
        v[i].l = pos[i] - dx;
        v[i].r = pos[i] + dx;
      }
      else {
        v[i].l = v[i].r = pos[i];
      }
    }
    sort(v,v+n,mySort);       //sorted intervals

    int count = 0;
    double curLeft,curRight=0,bestRight;
    curLeft = numeric_limits<int>::min();

    for(int i=0;i<n;i++) {

      bestRight = minusInf;
      if(v[i].l > curRight) {      //next left is disjoint set
        count = -1;
        break;
      }
      else if(v[i].r < curRight) {    //this one is 'covered' by the previous sprinkler
        continue;
      }
      else {
        int j;
        for(j=i;j<n;j++) {
          if(v[j].l > curRight) {
            i = j-1;
            curRight = bestRight;
            break;
          }
          else {
            bestRight = max(bestRight,v[j].r);
          }
        }
        if(j==n) {
          if(bestRight < l) {
            count=-1;
            break;
          }
          else {
            curRight = bestRight;
            count++;
            break;
          }
        }
        count++;
        if(bestRight >= l) break;
      }
    }
    cout<<count<<endl;

    delete[] v,r,pos;
  }
}