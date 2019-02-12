void create_interface(int);
int puzzle_hitbox(int, int, int, int, int);

void make_menu(){
	playsong("sound/make_sizeselect.wav");
	displaytxt("text/make/logo.txt",14,'c',0);
	cout<<endl;
	displaytxt("text/make/size_menuwarning.txt",12,'c',0);
	cout<<endl;
	displaytxt_colors("text/make/size_menu.txt","text/make/size_menucolr.txt");
//	show_point();

	int size=button_setting(6,51,67,18,20,51,67,22,24,51,67,26,28,51,67,30,32,51,67,34,36,51,67,38,40);
	cout<<endl;
	if(size==0) size=5;
	else if(size==1) size=8;
	else if(size==2) size=10;
	else if(size==3) size=12;
	else if(size==4) size=18;
	else size=20;
	center("You chose: "+to_string(size)+"x"+to_string(size)+".");
	Sleep(1000);

	system("CLS");
	create_interface(size);
}

void create_interface(int size){
	playsong("sound/makeui_bgm.wav");
	cout<<endl;
    displaytxt("text/make/ui_header.txt",10,'c');
    center("PUZZLE SIZE: "+to_string(size)+"x"+to_string(size));
	cout<<endl;
	for(int i=0;i<5;i++) cout<<endl;
	
	int rectSIZE=min((win_height-10)/size*size,(win_width-5)/size*size);
	drawrect(rectSIZE,rectSIZE,3);
	
	ifstream colr("text/make/ui_colorpadcolr.txt");
	ifstream txt("text/make/ui_colorpad.txt");
	
	string tmp;
	int y=9;
	
	while(getline(txt,tmp)){
		gotoxy(105,y);
		int colorNum=7;
		for(int i=0;i<tmp.length();i++) {
			colr>>colorNum;
			color(colorNum);
			cout<<tmp.at(i);
		}
		y++;
	}
	
	colr.close();
	txt.close();
	tmp.clear();
	
//	show_point();
	
	color(7);
	
	char board[30][30];
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++) board[j][i]=32;
	}
	
	char curcolr=32;
	while(true){
		int mode=puzzle_hitbox(33,rectSIZE,size,105,9);
		if(mode==2){
//			Exit warning

			ifstream colr("text/make/really_cancelcolr.txt");
			ifstream txt("text/make/really_cancel.txt");
			
			y++;
			int index=y;
			
			while(getline(txt,tmp)){
				gotoxy(103,y);
				int colorNum=7;
				for(int i=0;i<tmp.length();i++) {
					colr>>colorNum;
					color(colorNum);
					cout<<tmp.at(i);
				}
				y++;
			}
			
			colr.close();
			txt.close();
			tmp.clear();
			
			int confirm=button_setting(2541,103,108,y-3,y-1,110,115,y-3,y-1,0);
			color(7);
			if(confirm==0){
				PlaySound("sound/select_coin.wav", NULL, SND_SYNC | SND_NODEFAULT);
				return;
			}
			else {
				for(int i=index;i<y;i++){
					gotoxy(103,i);
					space(13);
				}
				y-=6;
			}
			
		}
		else if(mode==1) break;
		
		else if(mode<=47) curcolr=char(mode);
		
		else{
			mode-=100;
			int column=mode%size;
			mode-=column;
			int row=mode/size;
			board[column][row]=curcolr;
			
			int cox=(win_width-2*rectSIZE)/2 +column*2*rectSIZE/size, coy=10+rectSIZE/size*row;
			
			color((int(curcolr)-32)*17);
			for(int i=0;i<rectSIZE/size;i++){
				gotoxy(cox, coy);
				space(rectSIZE/size*2);
				coy++;
			}
		}
	}
	
	color(7);
	
	system("CLS");
	
//	savescreen
	
	y=22;
	ifstream charfile("text/make/save_entername.txt");
	ifstream colrfile("text/make/save_enternamecolr.txt");
	
	while(getline(charfile,tmp)){
		gotoxy(37,y);
		int colorNum;
		for(int i=0;i<tmp.length();i++){
			colrfile>>colorNum;
			color(colorNum);
			cout<<tmp.at(i);
		}
		y++;
	}
	
	tmp.clear();
	charfile.close();
	colrfile.close();
	
//	show_point();
	color(7);
	gotoxy(45,26);
	
	string puzzName;
	bool escape=false;
	
	while(true){
		SetWindow(win_width,win_height);
		
		if(kbhit() != 0) {
			char t=getch();
			if(wherex()>=80){
				cout<<"\b \b";
				puzzName.erase(puzzName.length()-1,1);
			}
			else if(wherex()<=45&&t==8) continue;
			
			if(t==8){
				puzzName.erase(puzzName.length()-1,1);
				cout<<"\b \b";
			}
			else{
				puzzName+=t;
				cout<<t;
			}
		}
		
		if(GetConsoleWindow() == GetForegroundWindow() && (GetKeyState(VK_LBUTTON) & 0x100) != 0){
			GetCursorPos(&curPOS);
			ScreenToClient(hwnd, &curPOS);
			double x=curPOS.x, y=curPOS.y;
			curCOL=x/win_widthpx*win_width;
			curROW=y/win_heightpx*win_height;

			if(curCOL>=72&&curCOL<=80&&curROW==28){
				PlaySound("sound/select_coin.wav", NULL, SND_SYNC | SND_NODEFAULT);
				Sleep(500);
				break;
			}
		}
	}
	
	ofstream newboard("user/board_"+to_string(makeCNT)+".txt");
	newboard<<puzzName<<endl;
	newboard<<size<<endl;
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++) newboard<<board[j][i]<<" ";
		newboard<<endl;
	}
	newboard.close();
	makeCNT++;
	ofstream lvlC("user/levelCount.txt");
	lvlC<<makeCNT<<endl;
	lvlC.close();
	
	gotoxy(0,31);
	center("New picross saved.");
	Sleep(1000);
}

int puzzle_hitbox(int SaveT, int RectSize, int size, int PadTopleftX, int PadTopleftY){
	while(true){
		SetWindow(win_width,win_height);
		if(GetConsoleWindow() == GetForegroundWindow() && (GetKeyState(VK_LBUTTON) & 0x100) != 0){
			GetCursorPos(&curPOS);
			ScreenToClient(hwnd, &curPOS);
			double x=curPOS.x, y=curPOS.y;
			curCOL=x/win_widthpx*win_width;
			curROW=y/win_heightpx*win_height;

			if(curROW>=PadTopleftY&&curCOL>=PadTopleftX&&curCOL<=PadTopleftX+7){
				if(curROW>=SaveT&&curROW<=SaveT+2) return 1;
				else if(curROW>=SaveT+4&&curROW<=SaveT+6) return 2;
				else if(curROW>=PadTopleftY&&curROW<=PadTopleftY+2) return 32;
				else{
					for(int i=33;i<=46;i++){
						if(i%2==1&&curCOL>=PadTopleftX+4) continue;
						else if(i%2==0&&curCOL<=PadTopleftX+3) continue;
						
						if(curROW<=PadTopleftY+(i%2==1?i+1:i)-30) return i;
					}
					if(curROW<=PadTopleftY+18) return 47;
				}
			}
			
			else{
				int xcoor=(win_width-2*RectSize)/2+1, ycoor=10;
				
				for(int i=0;i<size;i++){
					for(int j=0;j<size;j++){
						if(curCOL<xcoor+2*RectSize/size*(j+1)&&curROW<ycoor+RectSize/size*(i+1)) return (100+i*size+j);
					}
				}
			}
		}
	}
}
