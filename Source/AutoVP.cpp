#define WINVER 0x0500
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <ctype.h>
#include <stdio.h>
#include <mutex>
using namespace std;

double lat;
mutex mi;

void KeyPress(char key){
	INPUT kib;
	bool yah = false;
	kib.type = INPUT_KEYBOARD;
	kib.ki.time = 0;
	kib.ki.wVk = 0;
	kib.ki.dwExtraInfo = 0;
	mi.lock();
	
	if(isupper(key) or ispunct(key)){
		yah = true;
		kib.ki.dwFlags = KEYEVENTF_SCANCODE;
		kib.ki.wScan = 0x2A;
		SendInput(1, &kib, sizeof(INPUT));
	}
	
	kib.ki.dwFlags = KEYEVENTF_SCANCODE;
	kib.ki.wScan = MapVirtualKey(LOBYTE(VkKeyScan(key)),0);
	SendInput(1, &kib, sizeof(INPUT));
	
	kib.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	SendInput(1, &kib, sizeof(INPUT));

	if(yah){
		kib.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		kib.ki.wScan = 0x2A;
		SendInput(1, &kib, sizeof(INPUT));
	}
	mi.unlock();
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
				repeat:
				int j=0;
				while(true){
					if(a[i+j+1]==']' or a[i+j+1]==' ') break;
					j++;
				}
				
				vector<thread> mainth;
				
				for(int f=0; f<j; f++){
					mainth.push_back(thread(KeyPress,a[i+f+1]));
				}
				
				for(auto& thread : mainth){
					thread.join();
				}
				
				if(a[i+j+1]==' '){
					Sleep(lat/2);
					i+=j+1;
					goto repeat;
				} 
				
				i+=j+1;
				Sleep(lat);
			}
			else if(a[i]==' '){
				Sleep(lat*2);
			}
			else if(a[i]=='|'){
				Sleep(lat*4);
			} else{
				Sleep(lat);
				KeyPress(a[i]);
				Sleep(lat);
			}
		}
	}
	input.close();
	cout<<"You can now close the program."<<endl;
	system("pause");
	return 0;
}
