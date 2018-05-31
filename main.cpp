//
//  main.cpp
//  move constructor
//
//  Created by swtak_Apple_iMac on 2018. 5. 29..
//  Copyright © 2018년 CG2014.pnu.cse. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

class MyString
{
private:
    char* Buffer;
    
public:
    
    MyString(): Buffer(NULL) {
        cout << "Default constructor called" << endl;
    }
    
    MyString(const char* InitialInput) {
        
        cout << "Constructor called for: " << InitialInput << endl;
        
        if (InitialInput != NULL) {
            Buffer = new char[strlen(InitialInput) + 1];
            strcpy(Buffer, InitialInput);
        } else
            Buffer = NULL;
    }
  
    
    //Copy constructor
    MyString(const MyString& CopySource) {
        
        cout << "Copy constructor to copy from: " << CopySource.Buffer << endl;
        if(CopySource.Buffer != NULL)
        {
            // ensure deep copy by first allocating own buffer
            Buffer = new char [strlen(CopySource.Buffer) + 1];
            
            // copy from the source into local buffer
            strcpy(Buffer, CopySource.Buffer);
        }
        else
            Buffer = NULL;
    }
    
    // move constructor
    MyString(MyString&& MoveSource)
    {
        cout << "Move constructor to move from: " << MoveSource.Buffer << endl;
        if(MoveSource.Buffer != NULL)
        {
            Buffer = MoveSource.Buffer; // take ownership i.e.  'move'
            MoveSource.Buffer = NULL;   // free move source
        }
    }
    
    MyString& operator= (const MyString& CopySource) {

        cout<<"Copy assignment operator to copy from: "<<CopySource.Buffer<<endl;
        
        if ((this != &CopySource) && (CopySource.Buffer != NULL)) {
            
            if (Buffer != NULL)
                delete[] Buffer;
            
            Buffer = new char[strlen(CopySource.Buffer) + 1];
            
            strcpy(Buffer, CopySource.Buffer);
            
        }

        return *this;
    }
    
    
    // move assignment operator
    MyString& operator= (MyString&& MoveSource)
    {
        cout<<"Move assignment operator to move from: "<<MoveSource.Buffer<<endl;
        if((MoveSource.Buffer != NULL) && (this != &MoveSource))
        {
            delete Buffer; // release own buffer
            
            Buffer = MoveSource.Buffer; // take ownership i.e.  'move'
            MoveSource.Buffer = NULL;   // free move source
        }
        
        return *this;
    }
    
    int GetLength() const {
        return (int)strlen(Buffer);
    }
    
    const char *GetString()
    {
        return Buffer;
    }

    const char& operator[] (int index) const {
        
        cout << "operator [] is called" << endl;
        
        if (index < GetLength())
            return Buffer[index];
        else
            cerr << index << " is out of index: " << GetLength() << endl;
        exit(-1);
    }
    
    MyString operator+ (const MyString& AddThis) {
        
        cout << "operator + is called" << endl;
        MyString NewString;
        
        if (AddThis.Buffer != NULL) {
            NewString.Buffer = new char[GetLength() + strlen(AddThis.Buffer) + 1];
            strcpy(NewString.Buffer, Buffer);
            strcat(NewString.Buffer, AddThis.Buffer);
        }
        return NewString;
    }
    
    operator const char* () {
        return Buffer;
    }
    
    ~MyString() {
        if (Buffer != NULL)
            delete[] Buffer;
    }
};

void printString(MyString inputMyString)
{

    cout << inputMyString << endl;
}

int main()
{
    
    MyString Hello("Hello");
    printString(Hello);
    
    MyString World("World");
    MyString CPP("CPP");
    
    MyString sayHelloAgain("overwrite this");
    
    sayHelloAgain = Hello + World + CPP;
    
    cout << sayHelloAgain << endl;

    
    return 0;
}

123.45567788
