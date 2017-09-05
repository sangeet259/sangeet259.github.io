---
layout: post
title: "Greedy Algorithms"
permalink: "/greedy-algos"
tags: ["wnccsoc","algorithms","summers"]
subtitle: In quest for the optimal solution
---

Hey there! This is a late post, thanks to the cold I had caught and my procrastinating habits. As a part of <a href="http://wncc-iitb.org/soc/" target="_blank">WnCC Seasons of Code</a>, I had taken Competitive Coding and so far I have learnt quite a few things. So, basically Algorithms and Data Structures are about solving real-life problems with low space and time limits. Hence, efficient (and non-trivial) algorithms are required and efficient data structures to implement those algorithms. In the initial part, I read a little about handling large inputs and the time limits in contests like ACM ICPC and IOIs. One more thing that I learnt was Greedy Algorithms.

<h3>Greedy Algorithms? </h3>

<div class="row">
	<div class="col-md-8">
		So, basically, Greedy algorithms is a algorithm design technique which looks for an optimal 'local' solution in order to find the 'global' solution. What does this mean? In other words, a greedy algorithm looks for the best possible choice in a current state and those choices lead to the optimal state. Greedy Algorithms are usually the solution to 'optimization' problems (minimize this, or maximize that, we will look at some examples), and if a greedy algorithm is a solution, then perhaps it is the best solution. It is because in greedy algorithms, there is no going back. Once you find the optimal choice, you simply move on to find the next optimal choice. Enough small talk, time for some code!		
	</div>
	<div class="col-md-4">
		<img src="https://upload.wikimedia.org/wikipedia/commons/d/da/Greedy_algorithm_36_cents.svg" alt="greedy" class="img-responsive"><br>
		<center>
			Greedy algorithm used to solve the Coin Change Problem <br>
			<i>Source: Wikipedia</i>
		</center>
	</div>
</div>

<h3>The interval covering problem</h3>
Given a list of intervals and a 'universe' (which is basically the biggest interval) , what is the minimum number of intervals that are required to cover the entire universe ? In layman's terms, that is the basic problem statement. For example, given the intervals [1,2], [3,5], [1,5], [2,4], [4,5], [3,6], [2,7], [7,9], [4,8], [1,3], we need the choice of intervals such that we can cover the entire interval [1,9]. How do we go about doing that ? Think on it.
One way is to try out all the combinations, and check which one of them covers the universe, and then find the minimum (brute-force). This method will give you a TLE (time limit exceeded) verdict in most cases. Now, let's discuss the greedy approach.

First, we sort the elements in order of increasing endPoints and in case of ties, sort by decreasing startPoints. Then, we "greedily" select the first element. Then we see which element has the highest endPoint, and the startPoint of that element is less than or equal to our current endPoint (to completely cover the interval). This way, we continue till the end. Now, time for a real example.

<h3>UVa 10382 - Watering Grass</h3>
This problem is a slight variant of the Greedy Algorithm. Before moving on to (my) solution, I recommend you to try your hands on it. Here is the <a href="https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1323" target="_blank">link</a>.

What I did for this problem is, first convert the areas into intervals. How? If the diameter of a sprinkler is less than the width of the lawn, the sprinkler can't cover the lawn. So we remove it. Then, we convert the remaining sprinklers into intervals (see code) and apply the greedy approach. Here is the full C++ code (the code is actually lesser, but to explain things, the code is written more explicitly) - 
{% highlight cpp %}
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
    sort(v,v+n,mySort);       
    //sorted intervals

    int count = 0;
    double curLeft,curRight=0,bestRight;
    curLeft = numeric_limits<int>::min();

    for(int i=0;i<n;i++) {

      bestRight = minusInf;
      if(v[i].l > curRight) {      
      //next left is disjoint set
        count = -1;
        break;
      }
      else if(v[i].r < curRight) {   
      //this one is 'covered' by the previous sprinkler
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
{% endhighlight %}

This is an AC solution. Feel free to implement more improvements to it. Let me know through the comments.

On a final note, greedy algorithms are probably the best, but only if it is correct. An incorrectly implemented Greedy algorithm can give you a WA. There are more problems to try and implement. 

Happy Coding!!