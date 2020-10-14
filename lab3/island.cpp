//program to find out no of islands using disjoint set 
#include<iostream>
#include<algorithm>
#include<bits/stdc++.h>
#include<vector>
using namespace std;
class Island 
{
		int parent[100];
	public: 
		int count;
		Island(int n) 
		{
			for(int i = 0; i < n; i++)
			parent[i] = i;
			count = 0;
		}
		int findparent(int x) 
		{
			if(parent[x] == x) 
				return x;
			else
				return parent[x] = findparent(parent[x]);
		}
		void perform_union(int x, int y) 
		{
			int xroot = findparent(x);
			int yroot = findparent(y);
			if(xroot != yroot) 
			{
				parent[xroot] = yroot;
				count--;
			}
		}
		
};
int no_of_islands(vector<vector<int>>matrix) 
{
	int count = 0;
	int a = matrix.size();
	int b = matrix[0].size();
	
	for(int i = 0; i < a; i++) 
	{
		for(int j = 0; j < b; j++)
		{
			if(matrix[i][j] != 0)
				count++;
		}
	}
	Island ill(a*b);
	ill.count=count;
	for(int i = 0; i < a; i++)
	{
		for(int j = 0; j < b; j++)
		{
			if(matrix[i][j] != 0)
			{
				if(i > 0 && matrix[i-1][j] != 0) 
					ill.perform_union(b*i+j, b*(i-1)+j);
				if(i < a-1 && matrix[i+1][j] != 0) 
					ill.perform_union(b*i+j, b*(i+1)+j);
				if(j > 0 && matrix[i][j-1] != 0) 
					ill.perform_union(b*i+j, b*i+(j-1));
				if(j < b-1 && matrix[i][j+1] != 0) 
					ill.perform_union(b*i+j, b*i+(j+1));
				if(i > 0 && j > 0 && matrix[i-1][j-1] != 0) 
					ill.perform_union(b*i+j, b*(i-1)+(j-1));
				if(i > 0 && j < b-1 && matrix[i-1][j+1] != 0) 
					ill.perform_union(b*i+j, b*(i-1)+(j+1));
				if(i < a-1 && j > 0 && matrix[i+1][j-1] != 0) 
					ill.perform_union(b*i+j, b*(i+1)+(j-1));
				if(i < a-1 && j < b-1 && matrix[i+1][j+1] != 0) 
					ill.perform_union(b*i+j, b*(i+1)+(j+1));
			}
		}
	}
	return ill.count;
}
int main() 
{
	int r,c,k;
	vector<vector<int>>matrix;
	cout<<"Enter the dimension (Rows and columns) :"<<endl;
	cin>>r>>c;
	cout<<"Enter 0 or 1 for each position in the matrix: "<<endl;
	for(int i = 0; i < r; i++) 
	{
		vector<int>m1;
		for(int j = 0; j < c; j++) 
		{
			cin>>k;
			m1.push_back(k);
		}
		matrix.push_back(m1);
	}
	cout<<"The number of Islands in the entered matrix = "<<no_of_islands(matrix)<<endl;
	return 0;
}
