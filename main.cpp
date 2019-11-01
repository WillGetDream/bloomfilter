#include <iostream>
#include <math.h>
#include <vector>
#include <string>
using namespace std;

class BloomFilter{

public:
    float falseRateApproximately(int k,int n,int m);
    vector<bool> filVec(vector<bool> v,int size);
    unsigned int mrkHash(char a[],int n);
    unsigned int MurmurHash2 ( const void * key, int len, unsigned int seed );
    int addNCount(string* str,int n,int m,vector<bool> v);

 };

int main() {
    srand(static_cast<unsigned int>(time(0)));
    int k,m,n;
    BloomFilter bloomFilter;
    int count; //how many trues position in vector
    vector<bool> v;
    k=2; // how many hash
    m=15; //how many bits
    n=4;  //how many names data

    //declare variables,input
    string str[n];
    int inputName=0;
    while(inputName<n){
        cin>>str[inputName];
        inputName++;
    }


    //fill vector =0
    v=bloomFilter.filVec(v,m);

    //hash by using mrkHash, get the numbers of bits are true -> count
    count =bloomFilter.addNCount(str,n,m,v);

    //Prob of false positive
    float p=pow(1.0f*count/m,k);
    cout<<"Prob of false positive: "<<p<<endl;
    cout<<"false Rate Approximately calculated :"<<bloomFilter.falseRateApproximately(k,n,m)<<endl;

    return 0;
}

//falseRateApproximately
float BloomFilter::falseRateApproximately(int k,int n,int m){
    return  pow((1-exp(-1.0f*k*n/m)),k);

}

vector<bool> BloomFilter::filVec(vector<bool> v,int size){
    for(int i=0;i<size;i++){
        v.push_back(false);
    }
    return v;
}



unsigned int BloomFilter::mrkHash(char a[],int n){
    unsigned int sum=0,prod=1;
    char c;
    for(int i=0;i<n;i++){
        if(a[i]<=91)c=a[i]-65;
        else c=a[i]-71;
        sum+=(sum+c*prod);
        prod*=52;
        prod%=9999991;
        sum%=999999991;
    }
    return sum;
}

unsigned int BloomFilter::MurmurHash2 ( const void * key, int len, unsigned int seed )
{
    // 'm' and 'r' are mixing constants generated offline.
    // They're not really 'magic', they just happen to work well.

    const unsigned int m = 0x5bd1e995;
    const int r = 24;

    // Initialize the hash to a 'random' value

    unsigned int h = seed ^ len;

    // Mix 4 bytes at a time into the hash

    const unsigned char * data = (const unsigned char *)key;

    while(len >= 4)
    {
        unsigned int k = *(unsigned int *)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    // Handle the last few bytes of the input array

    switch(len)
    {
        case 3: h ^= data[2] << 16;
        case 2: h ^= data[1] << 8;
        case 1: h ^= data[0];
            h *= m;
    };

    // Do a few final mixes of the hash to ensure the last few
    // bytes are well-incorporated.

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}


int BloomFilter::addNCount(string* str,int n,int m,vector<bool> v){
    BloomFilter bloomFilter;
    for(int i=0;i<n;i++){
        char c1[str[i].size()+1];
        strcpy(c1,str[i].c_str());
        v[bloomFilter.mrkHash(c1,str[i].size()+1)%m]= true;
        v[bloomFilter.MurmurHash2(c1,str[i].size()+1,rand()%10000)%m]=true;
    }
    int count=0;
    for(int j=0;j<v.size();j++){
        if(v.at(j)==true){
            count++;
        }
    }
    return count;
}
