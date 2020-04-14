#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <ctype.h>
#include <stdio.h>
using namespace std;

double lat;

void KeyPress(char key){
	INPUT kib;
	bool yah = false;
	
	if(key == ']') return;
	
	if(isalpha(key) and isupper(key)){
		yah = true;
		kib.type = INPUT_KEYBOARD;
		kib.ki.time = 0;
		kib.ki.dwFlags = KEYEVENTF_SCANCODE;
		kib.ki.wScan = 0x2A;
		kib.ki.wVk = 0;
		kib.ki.dwExtraInfo = 0;
		SendInput(1, &kib, sizeof(INPUT));
	}
	
	if(ispunct(key)){
		yah = true;
		kib.type = INPUT_KEYBOARD;
		kib.ki.time = 0;
		kib.ki.dwFlags = KEYEVENTF_SCANCODE;
		kib.ki.wScan = 0x2A;
		kib.ki.wVk = 0;
		kib.ki.dwExtraInfo = 0;
		SendInput(1, &kib, sizeof(INPUT));
	}
	
	char vkey = VkKeyScan(key);
	UINT mkey = MapVirtualKey(LOBYTE(vkey),0);
	
	kib.type = INPUT_KEYBOARD;
	kib.ki.time = 0;
	kib.ki.dwFlags = KEYEVENTF_SCANCODE;
	kib.ki.wScan = mkey;
	kib.ki.wVk = 0;
	kib.ki.dwExtraInfo = 0;
	
	SendInput(1, &kib, sizeof(INPUT));
	Sleep(lat);
	kib.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	SendInput(1, &kib, sizeof(INPUT));

	kib.type = INPUT_KEYBOARD;
	kib.ki.time = 0;
	kib.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	kib.ki.wScan = 0x2A;
	kib.ki.wVk = 0;
	kib.ki.dwExtraInfo = 0;
	SendInput(1, &kib, sizeof(INPUT));
	
}

int main(){
	fstream input;
	string a;
	input.open("input.txt", ios::in);
	cout<<"Enter key latency: ";
	cin>>lat;
	cout<<"Program will launch in: 5s."<<endl;
	Sleep(5000);
	while(!input.eof()){
		getline(input, a);
		for(int i=0; i<a.length(); i++){
			if(a[i]=='['){
				Sleep(lat); 
				int j=0;
				while(true){
					if(a[i+j]==']') break;
					else j++;
				}
				
				if(a[i+2]==' '){
					for(int f=0; f<j; f++){
						if(a[i+f+1]!=' ')KeyPress(a[i+f+1]);
						else Sleep(lat/2);
					}
					break;
				}
				
				thread main[j];
				
				for(int f=0; f<j; f++){
					main[f] = thread(KeyPress,a[i+f+1]);
				}
				
				for(int f=0; f<j; f++){
					main[f].join();
				}
				
				i+=j;
			}
			else if(a[i]==']');
			else if(a[i]==' '){
				Sleep(lat*2);
			}
			else if(a[i]=='|'){
				Sleep(lat*4);
			} else{
				Sleep(lat);
				KeyPress(a[i]);
			}
		}
		Sleep(lat*2);
	}
	input.close();
	cout<<"You can now close the program.";
	return 0;
}
