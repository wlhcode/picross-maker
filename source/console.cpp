void SetWindow(int Width, int Height) {
// Credits: Software_Designer
// Original post: https://stackoverflow.com/a/12901833

    _COORD coord;
    coord.X = Width;
    coord.Y = Height;

    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(Handle, coord);
    SetConsoleWindowInfo(Handle, TRUE, &Rect);
}

void playsong(string filename){
	LPSTR s = const_cast<char *>(filename.c_str());
	PlaySound(s, NULL, SND_LOOP | SND_ASYNC);
}

void check_res(bool print){
	if(print==1) cout<<"Checking console resolution... ";
	SetWindow(win_width,win_height);
	hwnd = GetConsoleWindow();

	if(GetClientRect(hwnd, &rect)){
		win_widthpx = rect.right;
		win_heightpx = rect.bottom;
	}

	if(print==0) return;
	cout<<"Complete!"<<endl;
	cout<<"Window size (px): "<<win_widthpx<<"x"<<win_heightpx<<endl;
}

int button_setting(int buttonNum, ...){
//	hardcode
	bool sound=1;
	if(buttonNum==3564){
		buttonNum=3;
		sound=0;
	}
	else if(buttonNum==2541){
		buttonNum=2;
		sound=0;
	}
//	hardcode stops here

	va_list vl;

	while(true){
		SetWindow(win_width,win_height);
		if(GetConsoleWindow() == GetForegroundWindow() && (GetKeyState(VK_LBUTTON) & 0x100) != 0){
			GetCursorPos(&curPOS);
			ScreenToClient(hwnd, &curPOS);
			double x=curPOS.x, y=curPOS.y;
			curCOL=x/win_widthpx*win_width;
			curROW=y/win_heightpx*win_height;

			va_start(vl,buttonNum);

			for(int i=0;i<buttonNum;i++){
				int left=va_arg(vl,int);
				int right=va_arg(vl,int);
				int top=va_arg(vl,int);
				int bottom=va_arg(vl,int);

				if(curCOL>=left&&curCOL<=right&&curROW>=top&&curROW<=bottom){
					if(sound) PlaySound("sound/select_coin.wav", NULL, SND_SYNC | SND_NODEFAULT);
//					Sleep(500);
					return i;
				}
			}
		}
	}
}

void show_point(){ // Development-purposes.
	while(true){
		SetWindow(win_width,win_height);
		if(GetConsoleWindow() == GetForegroundWindow() && (GetKeyState(VK_LBUTTON) & 0x100) != 0){
			GetCursorPos(&curPOS);
			ScreenToClient(hwnd, &curPOS);
			double x=curPOS.x, y=curPOS.y;
			curCOL=x/win_widthpx*win_width;
			curROW=y/win_heightpx*win_height;

			cout<<curCOL<<" "<<curROW<<endl;
			Sleep(100);
		}
	}
}

void gotoxy(int x, int y){
// Credits: Benjamin Lindley
// Original post: https://stackoverflow.com/a/7955343

	static HANDLE h = NULL;  
	if(!h) h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };  
	SetConsoleCursorPosition(h,c);
}

// wherex() and wherey()
// Credits: Duthomhas
// Original post: http://www.cplusplus.com/forum/beginner/4234/#msg18563

int wherex(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(
			GetStdHandle( STD_OUTPUT_HANDLE ),
			&csbi
			))
		return -1;
	return csbi.dwCursorPosition.X;
}

int wherey(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(
			GetStdHandle( STD_OUTPUT_HANDLE ),
			&csbi
			))
		return -1;
	return csbi.dwCursorPosition.Y;
}
