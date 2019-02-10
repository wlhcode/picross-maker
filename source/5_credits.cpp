void staff_roll(){
	playsong("sound/credits.wav"); 
	cout<<endl;
	displaytxt("text/credits/credits_header.txt",11,'c',0);
	cout<<endl;
	displaytxt("text/credits/credits.txt",7,'c',1000);
	cout<<endl;
	Sleep(1000);
	for(int i=0;i<50;i++){
		cout<<endl;
		Sleep(50);
	}
}
