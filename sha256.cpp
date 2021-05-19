#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream>
using namespace std;

typedef unsigned int uint;

template <typename... T>
auto pr(T... t){
	std::initializer_list<int>{([&]{cout<<t<<" ";}(),0)...};
	cout<<endl;
}


uint genC2(double x){
	double y=x-int(x);
	uint z;
	uint s=0;
	for(int i=0;i<8;i++){
		y*=16;
		z=uint(y);
		y-=z;
		s*=16;
		s+=z;
	}
	return s;
}


bool isPrime(int a){
	for(int i=2;i<=sqrt(a);i++){
		if(a%i==0)
			return false;
	}
	return true;
}

vector<int> getPrimes(int n){
	vector<int> s;
	int sn=0;
	int I=2;
	while(sn<n){
		if(isPrime(I)){
			s.push_back(I);
			sn++;
		}
		I++;
	}
	return s;
}


vector<uint> genP0(){
	vector<uint>s;
	for(int i:getPrimes(8))
        s.push_back(genC2(pow(i,1/2.)));
	return s;
}


vector<uint> genP1(){
	vector<uint>s;
	for(int i:getPrimes(64))
        s.push_back(genC2(pow(i,1/3.)));
	return s;
}

vector<uint> H=genP0();
vector<uint> K=genP1();


string getBitData(string da){	
	string s;
	for(auto i:da){
		s+=bitset<8>(i).to_string();
	}
	int n=s.size();
	s+='1';
	s+=string(448-((n+1)%512%448),'0');
	s+=bitset<64>(n).to_string();

	return s;
}

vector<string>spl(string d,int n){
	vector<string>s;
	for(int i=0;i<d.size();i+=n){
		s.push_back(d.substr(i,n));
	}
	return s;
}

uint R(uint x,int n){
	return x>>n;
}

uint S(uint x,int n){
	return (x<<(32-n))|(x>>n);
}


uint Ch(uint x,uint y,uint z){
	return (x&y)^((~x)&z);
}

uint Maj(uint x,uint y,uint z){
	return (x&y)^(x&z)^(y&z);
}

uint E0(uint x){
	return S(x,2)^S(x,13)^S(x,22);
}

uint E1(uint x){
	return S(x,6)^S(x,11)^S(x,25);
}

uint g0(uint x){
	return S(x,7)^S(x,18)^R(x,3);
}
uint g1(uint x){
	return S(x,17)^S(x,19)^R(x,10);
}

auto gen(string data){
	string x=getBitData(data);
	vector<string> M0=spl(x,512);
	vector<vector<string>>M;
	for(auto i:M0)
		M.push_back(spl(i,32));
	
	int N=M.size();
	vector<vector<uint>>HS;
	HS.push_back(H);
	for(int i=1;i<=N;i++){
		
		vector<uint>W;
		
		for(int j=0;j<16;j++){
			W.push_back(bitset<32>(M[0][j]).to_ulong());
		}
		for(int j=16;j<64;j++){
			W.push_back(g1(W[j-2])+W[j-7]+g0(W[j-15])+W[j-16]);
		}	
			
		uint a,b,c,d,e,f,g,h,T1,T2;
		a=HS[i-1][0];
		b=HS[i-1][1];
		c=HS[i-1][2];
		d=HS[i-1][3];
		e=HS[i-1][4];
		f=HS[i-1][5];
		g=HS[i-1][6];
		h=HS[i-1][7];

		for(int j=0;j<64;j++){
			T1=h+E1(e)+Ch(e,f,g)+K[j]+W[j];
			T2=E0(a)+Maj(a,b,c);
			h=g;
			g=f;
			f=e;
			e=d+T1;
			d=c;
			c=b;
			b=a;
			a=T1+T2;
		}	
		HS.push_back({
		HS[i-1][0]+a,
		HS[i-1][1]+b,
		HS[i-1][2]+c,
		HS[i-1][3]+d,
		HS[i-1][4]+e,
		HS[i-1][5]+f,
		HS[i-1][6]+g,
		HS[i-1][7]+h
		});
	}
	//cout<<hex;
	//for(auto i:HS[N])
	//	cout<<i;
	//cout<<endl;
	//return HS[N];
	stringstream ss;
	string ostr;
	for(auto i:HS[N])
		ss<<hex<<i;
	ss>>ostr;
	return ostr;
}


int main(){
	string s;
	while(cin>>s)
		cout<<gen(s)<<endl;	
	return 0;
}

