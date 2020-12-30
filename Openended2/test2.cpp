#include <bits/stdc++.h>
using namespace std;
vector<int> sol;

void calculate_repeat(string s)
{
  int n=s.length();
  vector<int> mp(10,0);
  for(char i:s)
    mp[i-'0']++;
 for(int i=0;i<10;i++)
  {
      if(mp[i]>=2)
        return;
  }
  
  sol.push_back(stoi(s));
}


int main() {
   int l,r;
   cout<<"\nEnter range l and r\n";
   cin>>l>>r;
   for(int i=l;i<=r;i++)
   {
       string s=to_string(i);
       calculate_repeat(s);
   }
   
   for(int i:sol)
   cout<<i<<" ";
   cout<<"\n";

}