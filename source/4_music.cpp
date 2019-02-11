string library[100];
int songNum;
int crtMusic;

void MUSIC_easyselecting(int, int, int);

void music_list(){
//	break to next page, every 8
	int y=0;

	playsong("sound/music_menu.wav");
	
	cout<<endl; y++;
	displaytxt("text/music/header.txt",10,'c');
	
	ifstream songdata("text/music/ported_music.txt");
	
	songdata>>songNum;
	getline(songdata,library[0]); // Unknown error: somehow fixes it. Half-working
	
	for(int i=0;i<songNum;i++){
		for(int j=0;j<3;j++) getline(songdata,library[3*i+j]);
	}
	
	songdata.close();
	crtMusic=6;
	
	for(int i=0;i<songNum;i++){
		color(7);
		if(i!=0){
			cout<<endl;
			y++;
		}
		cout<<endl<<endl; y++;
		if(i==crtMusic) color(62);
		else color(27);
		
		y++;
		gotoxy(20,y);
		space(80);
		
		y++;
		gotoxy(20,y);
		int spaceNum=(80-library[i*3+1].length())/2;
		space(spaceNum);
		cout<<library[i*3+1];
		space(80-spaceNum-library[i*3+1].length());
		
		y++;
		gotoxy(20,y);
		spaceNum=(72-library[i*3+2].length())/2;
		space(spaceNum);
		cout<<"Used in "<<library[i*3+2];
		space(72-spaceNum-library[i*3+2].length());
		
		y++;
		gotoxy(20,y);
		space(80);
	}
	
	gotoxy(110,48);
	color(139);
	cout<<" BACK ";
	
	color(7);
//	show_point();
	
	while(true){
		int oldMusic=crtMusic;
		crtMusic=button_setting(9,20,99,3,6,20,99,9,12,20,99,15,18,20,99,21,24,20,99,27,30,20,99,33,36,20,99,39,42,20,99,45,48,110,115,48,48);
		if(crtMusic==8) return;
		MUSIC_easyselecting(oldMusic,crtMusic,27);
	}
}

void MUSIC_easyselecting(int original, int change, int ignore=27){
	color(ignore);
	int recY=6*original+3;
	
	gotoxy(20,recY);
	space(80);
	
	gotoxy(20,recY+1);
	int spaceNum=(80-library[original*3+1].length())/2;
	space(spaceNum);
	cout<<library[original*3+1];
	space(80-spaceNum-library[original*3+1].length());
	
	gotoxy(20,recY+2);
	spaceNum=(72-library[original*3+2].length())/2;
	space(spaceNum);
	cout<<"Used in "<<library[original*3+2];
	space(72-spaceNum-library[original*3+2].length());
	
	gotoxy(20,recY+3);
	space(80);
	
	if(ignore==27){
		original=change;
		MUSIC_easyselecting(original,0,62);
	}
	
	else{
		playsong("sound/"+library[3*crtMusic]);
		color(7);
		return;
	}
}
