#include<string>
#include<iostream>
#include<fstream>

using namespace std;

class edcode {
    public:
    string* files;
    int argc;
    char** argv;
    char c;
    int key = 20;
    
    
    
    edcode(int c, char** v){
        argc = c;
        argv = v;
        files = new string[argc];
        for (int i = 1; i < argc; i++)
        {
            files[i] = (string)argv[i];
            cout<<files[i] << i << endl;
        }

    }

    void encrypt(string file_name){
        string file = file_name;
        string new_file = "encrypted_"+ file;

        fstream fin,fout;

        fin.open(file,fstream::in);
        if (fin.is_open()){
            fout.open(new_file,fstream::out);

            while (fin >> noskipws >> c)
            {
                int temp = ( c + key);
                fout << (char)temp;
            }

            fin.close();
            fout.close();

            remove(file_name.c_str());
        }
        

    }

    void decrypt(string file_name){
        fstream fin;
        fstream fout;
        string old_name = file_name;
        file_name.erase(0,10);
        fin.open(old_name,fstream::in);
        if (fin.is_open()){

        
            fout.open(file_name,fstream::out);


            while (fin >> noskipws >> c){
                int temp = (c - key);
                fout << (char)temp;
            }

            fin.close();
            fout.close();

            remove(old_name.c_str());
        }

    }

    void encrypt_all(){
        cout<<"asdf";
        for (int i = 1; i < argc; i++)
        {
            cout<<i;
            cout<<files[i];
        }
        
    }

};


int main(int argc, char* argv[]){
    edcode edcrypter(argc,argv);

    cout << sizeof(edcrypter.files)/sizeof(edcrypter.files[0]) + "\n";

    char c;
    cout << "\n";
    cout << "Enter Your Choice : -> \n";
    cout << "1. encrypt \n";
    cout << "2. decrypt \n";
    cout << "3. encryptall \n";
    cin >> c;
    cin.ignore();
 
    switch (c) {
        case '1': {
            string file_name;
            cout << "enter name";
            cin >> file_name;
            edcrypter.encrypt(file_name);
            break;
        }
        case '2': {
            string file_name;
            cout << "enter name \n";
            cin >> file_name;
            edcrypter.decrypt(file_name);
            break;
        }
        case '3':{
            edcrypter.encrypt_all();
        }
    }

}