#include "source/picross.h"
#include "source/console.cpp"
#include "source/text.cpp"
#include "source/0_play.cpp"
#include "source/1_make.cpp"
#include "source/2_edit.cpp"
#include "source/3_about.cpp"
#include "source/4_music.cpp"
#include "source/5_credits.cpp"

string s;

int main(){
//	set window title
	system("TITLE Picross Maker");
	
//	get screen data
	check_res(0);
	Sleep(100);
	check_res(1);

//	music
	playsong("sound/titlescr.wav");

//	logo
	displaytxt("text/titlescr/logo.txt",14,'c',0);
	displaytxt("text/titlescr/subtitle.txt",6,'c',0);
	cout<<endl<<endl;

//	menuGUI
	displaytxt_colors("text/titlescr/title_btn.txt","text/titlescr/title_btncolr.txt");
	cout<<endl;

//	footer
	displaytxt("text/titlescr/copyright.txt",7,'c',0);

//	get make mode statistics
	ifstream lvlC("user/levelCount.txt");
	if(lvlC.fail()){
		lvlC.close();
		ofstream lvlC("user/levelCount.txt");
		lvlC<<0<<endl;
		lvlC.close();
    }
    else{
    	lvlC>>makeCNT;
		lvlC.close();
	}

//	button
	int mode=button_setting(7,46,57,18,24,61,72,18,24,51,67,26,28,51,67,30,32,51,67,34,36,51,67,38,40,51,67,42,44);

//	selected
	system("CLS");

	if(mode==0) select_lvl();
	else if(mode==1) make_menu();
	else if(mode==2) ;
	else if(mode==3) abtscr();
	else if(mode==4) music_list();
	else if(mode==5) staff_roll();
	else if(mode==6) return 0;
	
	system("CLS");
	main();
}
