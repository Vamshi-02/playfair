#include<bits/stdc++.h>
using namespace std;
string remspaces(string str){
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}
string makeven(string str){
	int n = str.size();
	if(n%2 != 0)
		str.push_back('x');
	return str;
}
char km[5][5] = {{0,0,0,0,0},
				 {0,0,0,0,0},
				 {0,0,0,0,0},
				 {0,0,0,0,0},
				 {0,0,0,0,0}};
void matrixgen(string key){
	unordered_map<char, int> mp;
	vector<char> li;
	for(auto &ch : key){
		if(mp[ch] == 0)
			li.push_back(ch);
		mp[ch]++;
	}
	for(char ch = 'a'; ch <= 'z'; ch++){
		if(ch == 'j')
			continue;
		if(mp[ch] == 0){
			li.push_back(ch);
			mp[ch]++;
		}
	}
	int k = 0;
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			km[i][j] = li[k];
			k++;
		}
	}
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			cout << km[i][j] << "\t";
		}
		cout << endl;
	}
}
vector<pair<char, char>> di;
void genpairs(string str){
	int n = str.size();
	int i = 0;
	while(i < n-1){
		if(str[i] == str[i+1]){
			di.push_back(make_pair(str[i],'x'));
			i++;
		}
		else{
			di.push_back(make_pair(str[i], str[i+1]));
			i = i+2;
		}
	}
}
void search(pair<int, int> p, int s[]){
	if(p.first == 'j')	
		p.first = 'i';
	if(p.second == 'j')
		p.second = 'i';
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			if(km[i][j] == p.first){
				s[0] = i;
				s[1] = j;
			}
			if(km[i][j] == p.second){
				s[2] = i;
				s[3] = j;
			}
		}	
	}
}
int mod5(int a){
	return (a%5);
}
string encrypt(){
	int s[4];
	string cip;
	for(int i = 0; i < di.size(); i++){
		search(di[i], s);
		if(s[0] == s[2]){
			cip.push_back(km[s[0]][mod5(s[1]+1)]);
			cip.push_back(km[s[0]][mod5(s[3]+1)]);
		}
		else if(s[1] == s[3]){
			cip.push_back(km[mod5(s[0]+1)][s[1]]);
			cip.push_back(km[mod5(s[2]+1)][s[1]]);
		}
		else{
			cip.push_back(km[s[0]][s[3]]);
			cip.push_back(km[s[2]][s[1]]);
		}
	}
	return cip;
}
string playfair(string txt, string key){
	int ts = txt.size();
	txt = remspaces(txt);
	txt = makeven(txt);
	genpairs(txt);
	int ks = key.size();
	key = remspaces(key);
	matrixgen(key);
	string cip = encrypt();
	return cip;
}
int main(){
	string key;
	cout << "Enter key:" << endl;
	getline(cin, key);
	string txt;
	cout << "Enter plain text:" << endl;
	getline(cin,txt);	
	string cip = playfair(txt, key);
	cout << cip << "\n";
	return 0;
}
