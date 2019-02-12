void editmenu(){
	if(makeCNT<=0){
		PlaySound("sound/error_xpstartup.wav", NULL, SND_ASYNC|SND_FILENAME);
		gotoxy(0,24);
		color(12);
		center("ERROR");
		color(7);
		center("There are no user-created levels. Refer to trouble.txt in the root directory if the problem persists.");
		cout<<endl;
		center("Returning to the main screen in 5 seconds...");
		for(int i=4;i>=0;i--){
			Sleep(1000);
			gotoxy(70,27);
			cout<<i;
			if(i==1){
				gotoxy(78,27);
				cout<<" ";
			}
		}
		return;
	}
	playsong("sound/stage_select.wav");
	cin.get();
}
