int mode=-1;

bool abt_modevalid(int pageNum){
	if(mode<0) return 0;
	if(mode==0&&pageNum==1) return 0;
	if(mode==1&&pageNum==4) return 0;
	return 1;
}

void abtscr(int pageNum=1){
	playsong("sound/about.wav");
	gotoxy(100,1);
	color((pageNum==1?8:10));
	cout<<" < ";
	color(7);
	cout<<" "<<pageNum<<" ";
	color((pageNum==4?8:10));
	cout<<" > ";
	cout<<"   ";
	color(139);
	cout<<" BACK ";
	color(7);
	gotoxy(0,0);
	
	cout<<endl;
	
//	Header
	displaytxt("text/about/header_"+to_string(pageNum)+".txt",11,'c');
	cout<<endl;
	
//	Message
	displaytxt("text/about/body_"+to_string(pageNum)+".txt",7,'l',0,2);
	

//	sample picross
	if(pageNum==1) displaypicross("text/about/add_1.txt");
	
	Sleep(500);
	mode=-1;
	while(!abt_modevalid(pageNum)) mode=button_setting(3564,100,102,1,1,106,108,1,1,112,117,1,1);
	
	if(mode==0) abtscr(pageNum-1);
	else if(mode==1) abtscr(pageNum+1);
	else return; 
}
