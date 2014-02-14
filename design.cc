#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

struct singleBox {
	int value;
	int faceUp;
	int show;
	singleBox(){
		faceUp=0;
		show=-1;
	}
};

struct player {
	int playerNum;
	singleBox** play;
	int nextPlayer;
	int lastPlayer;
	player(){}
};

void swap(singleBox &a, singleBox &b){
	int temp=a.value;
	a.value=b.value;
	b.value=temp;
	return;
}

void shuffle(singleBox** & table, int size){
	for (int i=0; i<size; i+=1){
		for (int j=0; j<size; j+=1){
			int x=rand()%size;
			int y=rand()%size;
			swap(table[x][y], table[i][j]);
		}
	}
}

// print table
void print(singleBox** table, int size){
	cout<<" ";
	for (int x=0; x<size; x+=1){		
		cout<<" "<<x;
	}
	cout<<endl;
	for (int i=0; i<size; i+=1){
		cout<<i;
		for (int j=0; j<size; j+=1){	
			int toPrint=table[i][j].show;
			if (toPrint==-1){
				cout<<" *";
			}
			else{
				cout<<" "<<table[i][j].show;	
			}
		}
		cout<<endl;
	}
}

int oneGame(int numPlayers, int dim){
	int counter=0;
	int div=dim/2*dim;
	singleBox** table;
	table=new singleBox*[dim];
	for (int r=0; r<dim; r+=1){
		table[r]=new singleBox[dim];
		for (int c=0; c<dim; c+=1){
			(table[r][c]).value=counter%div;
			counter+=1;
		}
	}
	shuffle(table, dim);
	// display the game board for players to select
	print(table, dim);
	// set up players order
	vector<player> Players(numPlayers);
	int y;
	if (numPlayers==1){	
		Players.at(0).playerNum=0;
		Players.at(0).play=table;
		Players.at(0).nextPlayer=0;
		Players.at(0).lastPlayer=0;
	}
	else{
		Players.at(0).playerNum=0;
		Players.at(0).play=table;
		Players.at(0).nextPlayer=1;
		Players.at(0).lastPlayer=numPlayers-1;
		
		for (y=0; y<Players.size(); y+=1){
			Players.at(y).playerNum=y;
			Players.at(y).play=table;
			Players.at(y).nextPlayer=y+1;
		}
		Players.at(0).lastPlayer=numPlayers-1;
		Players.at(y-1).nextPlayer=0;
	}
	// start to pick
	int x1;
	int y1;
	int x2;
	int y2;
	int i=0;
	int current_player;
	for (current_player=0; i<dim*dim && current_player<numPlayers; current_player=Players.at(current_player).nextPlayer){	
		cout<<"Player "<<current_player<<" play."<<endl;
		cout<<"Please enter the row and the column number you want to pick for the first card:"<<endl;
		

		while(cin>>x1>>y1,x1>=dim || y1>=dim)
		  {
		    cout<<"Too much !!"<<endl;
		    sleep(1);
		    cout<<"\033[3A";
		    cout<<"         \n"<<"        \n"<<"            \n";
		    cout<<"\033[3A";
		    cin.clear();
		  }


	    while(table[x1][y1].show!=-1){	
	      cout<<"Please enter another pair with unknown number:"<<endl;
	      cin>>x1>>y1;
	    }
	 

	table[x1][y1].faceUp=1;
	table[x1][y1].show=table[x1][y1].value;
	print(table, dim);
	cout<<"Please enter the row and the column number you want to pick for the second card:"<<endl;
	
	while(cin>>x2>>y2,x2>=dim || y2>=dim)
		  {
		    cout<<"Too much !!"<<endl;
		    sleep(1);
		    cout<<"\033[3A";
		    cout<<"         \n"<<"        \n"<<"            \n";
		    cout<<"\033[3A";
		    cin.clear();
		  }




	while (x1==x2 && y1==y2){	
		cout<<"Please enter a new pair:"<<endl;
		cin>>x2>>y2;
	}
	while(table[x2][y2].show!=-1){
		cout<<"Please enter another pair with unknown number:"<<endl;
		cin>>x2>>y2;
	}




		if (table[x2][y2].value==table[x1][y1].value){
			table[x2][y2].faceUp=1;
			table[x2][y2].show=table[x2][y2].value;
			print(table, dim);
			i+=2;
			current_player=Players.at(current_player).lastPlayer;
		}
		else {
			table[x1][y1].faceUp=0;
			table[x1][y1].show=-1;
			//print(table, dim);
			table[x2][y2].faceUp=1;
			table[x2][y2].show=table[x2][y2].value;
			print(table, dim);	
			table[x2][y2].faceUp=0;
			table[x2][y2].show=-1;
		}		
	}
	cout<<"Congratulations! Player "<<current_player<<" won the game!"<<endl;	
	// free memory
	for (int i=0; i<dim; i+=1){
		delete []table[i];
	}
	delete []table;
	return current_player;
}

int main(){	
	// fill in the game board 
	int numPlayers;
	cout<<"How many players in total?"<<endl;
	cin>>numPlayers;
	vector<int> scoreboard(numPlayers,0);

	/*
	for (int i=0; i<numPlayers; i+=1){
		scoreboard.at(i)=0;
	}
	*/
	while(true){
		
		cout<<"What dimension do you want?"<<endl;
		int dim;
		cin>>dim;
		int winner=oneGame(numPlayers, dim);
		scoreboard.at(winner)+=1;
		for (int i=0; i<numPlayers; i+=1){
			cout<<"Player "<<i<<" score "<<scoreboard.at(i)<<endl;
		}
		cout<<"Start a new game?"<<endl;
		int yes;
		cin>>yes;
		if (yes==1)continue;
		else break;
	}
	scoreboard.clear();
	return 0;
}

