void color(int colorNum){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetWindow(win_width, win_height);
	SetConsoleTextAttribute(hConsole, colorNum);
}

void space(int number){
	for(int i=0;i<number;i++) cout<<" ";
}

void center(string s){
	space((win_width-s.length())/2);
	cout<<s<<endl;
}

void right(string s){
	space((win_width-s.length()));
	cout<<s<<endl;
}

void displaytxt(string filename, int colorNum, char alignment,int wait=0){
	string temp;
	ifstream file(filename);
	color(colorNum);
	while(getline(file,temp)){
		if(alignment=='r') right(temp);
		else if(alignment=='c') center(temp);
		else cout<<temp<<endl;
		Sleep(wait);
	}
	temp.clear();
	file.close();
	color(7);
}

void displaytxt_colors(string charFilename, string colorFilename){ // slower! only use if needed
	string charf;
	int colrf[100];
	ifstream charfile(charFilename);
	ifstream colrfile(colorFilename);
	while(getline(charfile,charf)){
		for(int i=0;i<charf.length();i++) colrfile>>colrf[i];
		space((win_width-charf.length())/2);
		for(int i=0;i<charf.length();i++){
			color(colrf[i]);
			cout<<charf.at(i);
		}
		cout<<endl;
	}
	charf.clear();
	charfile.close();
	colrfile.close();
	color(7);
}

void drawrect(int row, int column, int colorNum){
	color(colorNum);
	column*=2;
	string strA, strB;
	strA+="+";
	strA.insert(strA.end(),column,'-');
	strA+="+";
	strB+="|";
	strB.insert(strB.end(),column,' ');
	strB+="|";
	center(strA);
	for(int i=0;i<row;i++) center(strB);
	center(strA);
	strA.clear();
	strB.clear();
	color(7);
}

void screencenter(string char_filename,string colr_filename){
	string str[100];
	int i=0;
	ifstream file(char_filename);
	while(getline(file,str[i])) i++;
	for(int j=(win_height-i)/2;j>0;j--) cout<<endl;
	file.close();
	displaytxt_colors(char_filename,colr_filename);
	color(7);
}
