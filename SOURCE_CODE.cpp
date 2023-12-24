#include <bits/stdc++.h>
using namespace std;

string hexToBinary(string hex){

    string bin = "";
    for (int i = 0; i < hex.length(); i++)
    {
            if( hex[i] == '0'){
                bin += "0000";
            }
                
            else if( hex[i] == '1'){
                bin += "0001";
            }
            else if( hex[i] =='2'){
                bin += "0010";
            }  
            else if( hex[i] =='3'){
                bin += "0011";
            }    
            else if( hex[i] =='4'){
                bin += "0100";
            }    
            else if( hex[i] =='5'){
                bin += "0101";
            }  
            else if( hex[i] =='6'){
                bin += "0110";
            }
            else if( hex[i] =='7'){
                bin += "0111";
            }
            else if( hex[i] =='8'){
                bin += "1000";
            }
            else if( hex[i] =='9'){
                bin += "1001";
            }
            else if( hex[i] == 'A' || hex[i] == 'a'){
                bin += "1010";
                }
            else if( hex[i] == 'B' || hex[i] == 'b'){
                bin += "1011";
                }
            else if( hex[i] == 'C' || hex[i] == 'c'){
                bin += "1100";
                }
            else if( hex[i] == 'D' || hex[i] == 'd'){
                bin += "1101";
                }
            else if( hex[i] == 'E' || hex[i] == 'e'){
                bin += "1110";
                }
            else if( hex[i] == 'F' || hex[i] == 'f'){
                bin += "1111";
            }
    }
            
        return bin;
}

string binToHex(string bin){
    int moreZeroes = (4-(bin.length())%4);
    if (moreZeroes == 4)
    {
        moreZeroes = 0;
    }
    
    for (int i = 0; i < moreZeroes; i++)
    {
        bin = "0" + bin;
    }

    string hex = "";
    for (int i = 0; i < bin.length(); i+=4)
    {
        if (bin.substr(i,4) == "0000")
        {
            hex = hex + "0";
        }
        else if (bin.substr(i,4) == "0001")
        {
            hex = hex + "1";
        }
        else if (bin.substr(i,4) == "0010")
        {
            hex = hex + "2";
        }
        else if (bin.substr(i,4) == "0011")
        {
            hex = hex + "3";
        }
        else if (bin.substr(i,4) == "0100")
        {
            hex = hex + "4";
        }
        else if (bin.substr(i,4) == "0101")
        {
            hex = hex + "5";
        }
        else if (bin.substr(i,4) == "0110")
        {
            hex = hex + "6";
        }
        else if (bin.substr(i,4) == "0111")
        {
            hex = hex + "7";
        }
        else if (bin.substr(i,4) == "1000")
        {
            hex = hex + "8";
        }
        else if (bin.substr(i,4) == "1001")
        {
            hex = hex + "9";
        }
        else if (bin.substr(i,4) == "1010")
        {
            hex = hex + "A";
        }
        else if (bin.substr(i,4) == "1011")
        {
            hex = hex + "B";
        }
        else if (bin.substr(i,4) == "1100")
        {
            hex = hex + "C";
        }
        else if (bin.substr(i,4) == "1101")
        {
            hex = hex + "D";
        }
        else if (bin.substr(i,4) == "1110")
        {
            hex = hex + "E";
        }
        else if (bin.substr(i,4) == "1111")
        {
            hex = hex + "F";
        }
    }
    
    return hex;
}

int binaryToDecimal(string input) 
{   
    int decimalValue = 0;
    
    for (int i = input.length(); i >=0 ; i--)        
    {
        if(input[i] == '1'){
            decimalValue = decimalValue + pow(2,input.length()-i-1);
        }
    }  
  
    return decimalValue; 
}

int main(){

    ifstream config;
    ifstream address;
    config.open("cache.config");
    address.open("cache.access");

    int cacheSize;
    int blockSize;
    int associativity;
    string policy;
    string wbPolicy;
    string l;

    getline(config, l);
    cacheSize = stoi(l);

    getline(config, l);
    blockSize = stoi(l);

    getline(config, l);
    associativity = stoi(l);

    getline(config, policy);
    getline(config, wbPolicy);
    
    config.close();
    int count = 0;
    while (getline(address, l))
    {
        count++;
    }

    address.close();

    address.open("cache.access");

    string input[count]; 
    int t = 0;
    while (getline(address, input[t]))
    {   
        t++;
    }

    if(associativity == 0){
        associativity = cacheSize/blockSize;
    }

    int index = (log2(cacheSize/(blockSize*associativity)));
    int offset = (log2(blockSize));
    srand(time(NULL));

    string idx[cacheSize/(blockSize*associativity)][associativity] = {""};

    int lruClock[cacheSize/(blockSize*associativity)][associativity] = {0};

    int h = -1;
    for (int i = 0; i < sizeof(input)/sizeof(input[0]); i++)
    {   
        string address = input[i].substr(5,8);
        string addressBin = hexToBinary(address);
        string tag = binToHex(addressBin.substr(0,32-offset-index));
        string set = binToHex(addressBin.substr(32 - index - offset, index));
        if (associativity == cacheSize/blockSize)
        {
            set = "00";
        }
        
        int indexNum = binaryToDecimal(addressBin.substr(32 - index - offset, index));

        if(input[i].substr(0,1) == "R" || (input[i].substr(0,1) == "W" && wbPolicy == "WB")){
            
               if (policy == "FIFO")
               {    

                int c = 0;

                    for (int i = 0; i < associativity; i++)
                    {
                        if (idx[indexNum][i] == tag)
                        {   
                            c = 1;
                            cout << "Address: 0x" << address << ", Set: 0x" << set << ", Hit, Tag: 0x" << tag << endl;
                            break;
                        }    
                    }  
                    
                    if (c == 0)
                    {      
                        h = (h+1)%associativity;
                        idx[indexNum][h] = tag;
                        cout << "Address: 0x" << address << ", Set: 0x" << set << ", Miss, Tag: 0x" << tag << endl;
                    }
                    
               }
               else if (policy == "LRU")
               {
                int c = 0;

                    for (int i = 0; i < associativity; i++)
                    {
                        if (idx[indexNum][i] == tag)
                        {   
                            c = 1;
                            lruClock[indexNum][i] = 0;
                            cout << "Address: 0x" << address << ", Set: 0x" << set << ", Hit, Tag: 0x" << tag << endl;
                            break;
                        }    
                    } 
                    if (c == 0)
                    {
                    for (int i = 0; i < associativity; i++)
                    {
                        if (idx[indexNum][i] == "")
                        {   
                            c = -1;
                            idx[indexNum][i] = tag;
                            cout << "Address: 0x" << address << ", Set: 0x" << set << ", Miss, Tag: 0x" << tag << endl;
                            break;
                        }    
                    }
                    if(c == 0){
                        int max = lruClock[index][0];
                        int j = 0;
                        for (int i = 1; i < associativity; i++)
                        {
                            if (lruClock[indexNum][i] > max)
                            {
                                max = lruClock[indexNum][i];
                            }    
                        }
                        lruClock[indexNum][j] = 0;
                        idx[indexNum][j] = tag;
                        cout << "Address: 0x" << address << ", Set: 0x" << set << ", Miss, Tag: 0x" << tag << endl;
                    }    
                    }
                    for (int i = 0; i < cacheSize/(blockSize*associativity); i++)
                    {
                        for (int j = 0; j < associativity; j++)
                        {
                            if (idx[indexNum][i] != "")
                            {
                                lruClock[i][j] ++ ;
                            }
                        }
                    }
                    
               }
               else if (policy == "RANDOM")
               {
                int c = 0;

                    for (int i = 0; i < associativity; i++)
                    {
                        if (idx[indexNum][i] == tag)
                        {   
                            c = 1;
                            cout << "Address: 0x" << address << ", Set: 0x" << set << ", Hit, Tag: 0x" << tag << endl;
                            break;
                        }    
                    }
                if (c == 0)
                    {
                    for (int i = 0; i < associativity; i++)
                    {
                        if (idx[indexNum][i] == "")
                        {   
                            c = -1;
                            idx[indexNum][i] = tag;
                            cout << "Address: 0x" << address << ", Set: 0x" << set << ", Miss, Tag: 0x" << tag << endl;
                            break;
                        }    
                    }
                    if(c == 0){
                        idx[indexNum][rand()%associativity] = tag;
                        cout << "Address: 0x" << address << ", Set: 0x" << set << ", Miss, Tag: 0x" << tag << endl;
                    }    
                    }
               }
               
        }
        else if ((input[i].substr(0,1) == "W" && wbPolicy == "WT"))
        {   
            int c = 0;
            for (int i = 0; i < associativity; i++)
                    {
                        if (idx[indexNum][i] == tag)
                        {   
                            c = 1;
                            lruClock[indexNum][i] = 0;
                            cout << "Address: 0x" << address << ", Set: 0x" << set << ", Hit, Tag: 0x" << tag << endl;
                            break;
                        }    
                    }
            if (c == 0)
            {
                cout << "Address: 0x" << address << ", Set: 0x" << set << ", Miss, Tag: 0x" << tag << endl;    
            }    
        }    
    }    
}