#ifndef ASYMETRIC_KEY_GET_H // include guard
#define ASYMETRIC_KEY_GET_H
#include <stdlib.h>
#include<time.h>
#include<vector>
#include<string>
#include<fstream>
#include<iostream>
//#include <bits/stdc++.h>
class asymetric_key_gen
{
private:

    double prime_numbers[168] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293,307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};



public:
    asymetric_key_gen(/* args */);
    ~asymetric_key_gen();
    double* generate_key_pair();
    std::vector<int> encoder(int key,std::string message,int n);
    std::string decoder(int priv_key,std::vector<int> encoded,int n);
    long long int encrypt(int key,double message,int n);
    long long int decrypt(int priv_key,int encrpyted_text,int n);
    int encrypt_file(int key,std::string fileName, int n);

    int GCD(int x, int y);
};

asymetric_key_gen::asymetric_key_gen(/* args */)
{
    srand(time(NULL));
}

asymetric_key_gen::~asymetric_key_gen()
{
}

double* asymetric_key_gen::generate_key_pair(){

    double p;
    double q;
    double n;
    int random1 = rand() % 168;
    int random2 = rand() % 168;

    p = prime_numbers[random1];
    q = prime_numbers[random2];
    n = p * q;
    int phi = (p-1) * (q-1);
    int e = rand()%100;

    while (true)
    {
        if (GCD(e,phi) == 1)
        {
            break;
        }
        e++;
        
    }


    int d = rand()%100;

    while (1) {
        if ((d * e) % phi == 1)
            break;
        d++;
    }


    static double keys[3] = {e,d,n};

    //std::cout<<keys[0]<<std::endl;
    //std::cout<<keys[1];


    //public,private,n
    return keys;


}

int asymetric_key_gen::GCD(int x,int y){
    int temp;
    while (true)
    {
        temp = x % y;
        if(temp == 0){
            return y;
        }
        x = y;
        y = temp;
    }
    
}


int asymetric_key_gen::encrypt_file(int key,std::string fileName, int n){
    std::fstream fin,fout;

    fin.open(fileName);
    std::string message;


    if (fin.is_open()){
        char c;
        std::string message;
        while (fin >> std::noskipws >> c){
            message +=c;
        }

        std::vector<int> encoded_message = encoder(key,message,n);


        std::cout<<std::endl << "encoded" << std::endl;
        for (auto& i : encoded_message)
        {
            std::cout << i;
        }
        

        fin.close();

        fout.open("security", std::ios::out | std::ios::trunc);

        for (auto& p : encoded_message)
            fout << p;
        
        return 1;
    

    }else
    return 0;
}


std::vector<int> asymetric_key_gen::encoder(int key,std::string message, int n)
{
    std::vector<int> form;
    // calling the encrypting function in encoding function
    for (auto& letter : message)
        form.push_back(this->encrypt(key,(int)letter,n));
    return form;
}
std::string asymetric_key_gen::decoder(int priv_key,std::vector<int> encoded,int n)
{
    std::string s;

    cout<<endl<<"decoder"<<endl;
    for (auto& i: encoded)
    {
        std::cout<<i << ',';
    }
    
    // calling the decrypting function decoding function
    for (auto& num : encoded)
        s += this->decrypt(priv_key, num, n);
    return s;
}




long long int asymetric_key_gen::encrypt(int key,double message,int n){
    int  l = key;
    long long int encrypted_text = 1;
    while (l--) {
        encrypted_text *= (message);
        encrypted_text %= n;
    }
    return encrypted_text;
}

long long int asymetric_key_gen::decrypt(int priv_key,int encrypted_text,int n){
    int k = priv_key;
    long long int decrypted = 1;
    while (k--) {
        decrypted *= encrypted_text;
        decrypted %= n;
    }
    return decrypted;
}



#endif
