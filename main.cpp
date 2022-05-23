/**------------------------------------------
    Prog 5: March Madness Frenzy
    The dataset covers ranges of the basketball game for both men and women brackets for 2021 and 2022 with predictioon brackets. The file is broken down in different regions and championship. The program has options to analyze this data in different ways.

    Course: CS 141, Spring 2022.
    System: macOS clion
    Date: 4/12/2022
    Author: Yousef Habeeb
*/
#include <iostream> 
#include <string.h>
#include <vector>
#include <fstream> 
#include <sstream>
#include <assert.h>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <ios>
#include <numeric>
using namespace std;

class info {
  public: 
    //set functions
    void setRegion( string Region) {region = Region;}
    void setRank1( int Rank) {rank1 = Rank;}
    void setTeam1( string Team){team1 = Team;}
    void setScore1( int Score){score1 = Score;}
    void setRank2( int Rank) {rank2 = Rank;}
    void setTeam2( string Team) {team2 = Team;}
    void setScore2( int Score) {score2 = Score;}
    void setWinningTeam(string WT){winningTeam = WT;}
    void setRoundnumber(int RN){roundNumber = RN;}
    void setGameNumber(int GN){gameNumber = GN;}

    //get functions
    string getRegion() const{return region;}
    int getRank1() const {return rank1;}
    string getTeam1() const {return team1;}
    int getScore1() const {return score1;}
    int getRank2() const {return rank2;}
    string getTeam2() const {return team2;}
    int getScore2() const {return score2;}
    string getWinningTeam() const {return winningTeam;}
    int getRoundnumber() const {return roundNumber;}
    int getGameNumber() const {return gameNumber;}
    
  private: 
    // prevents any errors and makes them unchangable
    string region;
    int rank1;
    string team1;
    int score1;
    int rank2;
    string team2;
    int score2;
    string winningTeam;
    int roundNumber;
    int gameNumber;
};

//displays over all information
void display1 (){
  cout<<"Program 5: March Madness Frenzy \n"<<"CS 141, Spring 2022, UIC \n"
    <<endl
    <<"This program reads in data from NCAA Basketball Tournaments (aka March Madness). It provides overall information regarding the data, allows you to see the path taken to the championship, uses rankings of teams to determine which region is expected to win at a given round and to find the best underdog team, and calculates point differences within the games. You can also compare the actual brackets to your own predictions! \n"
    <<endl
    <<"Enter the name of the file with the data for the NCAA tournament: "
    <<endl;
}

// displays menu options
void display2(){
  cout<<"Select a menu option: \n"
    <<"   1. Display overall information about the data \n"
    <<"   2. Display the path of the winning team to the championship \n"
    <<"   3. Determine which region is expected to win the championship based on a given round \n"
    <<"   4. Identify the best underdog within a given round \n"
    <<"   5. Find the shoo-in and nail-biting games within a given round, or overall \n"
    <<"   6. Compare the actual brackets to your predicted brackets \n"<<"   7. Exit \n"
    <<"Your choice -->  ";
}


 //splits the file whereever a ',' appears and pushes it back to a vector
void split(string row,vector<string> &Word){
  string word;
  stringstream sstream(row);
  //runs the file till there is a ','
  while (getline(sstream, word, ',')){
    Word.push_back(word);//adds to the word vector
  }
} //end 

// opens and reads the file
void readFile (vector<string> &words, vector<info> &obj, info rows,string fileName){
  string line;
  ifstream inStream;
  inStream.open(fileName);
  assert(inStream.fail() == false);
  getline(inStream,line);//uses the getline function
  
  while(getline(inStream,line)){//runs thill the statement turns false
    split(line,words);

    //fills empty spots with 0
    if (words.at(3).empty()){ 
      words.at(3) = "0";
    } 
    if (words.at(6).empty()){ 
      words.at(6) = "0";
    } 
    
    //setters to set the words at a given row
    rows.setRegion(words.at(0));
    rows.setRank1(stoi(words.at(1)));
    rows.setTeam1(words.at(2));
    rows.setScore1(stoi(words.at(3)));
    rows.setRank2(stoi(words.at(4)));
    rows.setTeam2(words.at(5));
    rows.setScore2(stoi(words.at(6)));
    rows.setWinningTeam(words.at(7));
    rows.setRoundnumber(stoi(words.at(8)));
    rows.setGameNumber(stoi(words.at(9)));
    
    obj.push_back(rows);//add them into a vector

    words.clear();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////

//displays over all information about the tournament
void option1(vector <info> &dataset){
  vector <string> team; //stores teams

  //loops through the file to add teams to the vector
  for(int i = 0; i < dataset.size();i++){  
    if(dataset.at(i).getRegion() == "Final Four"){
      team.push_back(dataset.at(i).getTeam1());
      team.push_back(dataset.at(i).getTeam2());
    }
  }
  cout << "Total number of games played in tournament: " << dataset.size() << endl;
  cout<<"The Final Four contestants are: "<<endl;

  //comparing new vector with the data
  for(int k = 0; k < dataset.size();k++){
    for(int j = 0; j < team.size();j++){
      if(dataset.at(k).getRegion()== "West"||dataset.at(k).getRegion()== "Midwest"||dataset.at(k).getRegion()== "South"||dataset.at(k).getRegion()== "East"||dataset.at(k).getRegion()== "Wichita"||dataset.at(k).getRegion()== "Greensboro"||dataset.at(k).getRegion()== "Spokane"||dataset.at(k).getRegion()== "Bridgeport"){
        
        //checks if the team in the file matches the one in the vector
        if(dataset.at(k).getTeam1()== team.at(j)||dataset.at(k).getTeam2()== team.at(j)){
          cout<<"        "<<dataset.at(k).getRegion()<<" region: "<< setw(5);  
          cout << team.at(j)<<endl;
          team.erase(team.begin() + j);
        }
      }
    }
  }  
}

///////////////////////////////////////////////

//displays path to the championship
void option2 (vector <info> &dataset){
  // vector <string> empty;
  cout<<"Path to the championship:"<<endl;

  //checking throught the data
  for(int i = dataset.size()-1; i >= 0 ; i--){
    
    //possible round numbers
    for(int j =1; j<7; j++){
      
      if (dataset.at(i).getRoundnumber()==j){

        //checks if either team is the winner of the championship
        if (dataset.at(i).getTeam1()== dataset.at(0).getWinningTeam()|| dataset.at(i).getTeam2()== dataset.at(0).getWinningTeam()){
          
          cout<<"Round "<<dataset.at(i).getRoundnumber()<<", Game "<<dataset.at(i).getGameNumber()<<": "<<dataset.at(i).getTeam1()<<" vs "<<dataset.at(i).getTeam2()<<".  Winner:  "<<dataset.at(i).getWinningTeam()<<endl;
        }
      }
    }
  }
}


///////////////////////////////////////////////

// instructions for option 4
void option4_2(vector <info> dataset,int x){
  vector <string> teams; //team names 
  vector <int> ranks;    //ranks of each team

 // if the round is between 2-5
  if(x <= 5){
    for(int i = 0; i<dataset.size(); i++){
      if(dataset.at(i).getRoundnumber()==x-1){
        
        //if the team matches the winning team, the team and rank are added to the vector
        if(dataset.at(i).getTeam1()==dataset.at(i).getWinningTeam()){
          teams.push_back(dataset.at(i).getTeam1());
          ranks.push_back(dataset.at(i).getRank1());
        }
        else if(dataset.at(i).getTeam2()==dataset.at(i).getWinningTeam()){
          teams.push_back(dataset.at(i).getTeam2());
          ranks.push_back(dataset.at(i).getRank2());
        }
      }
    }

    // method of finding the maximum number in the ranks vector
    int max = ranks.at(0);
    int count = 0;
    for (int j = 0;j<ranks.size();j++){
      if (ranks.at(j)>max){
        max = ranks.at(j);
        count = j;
      }
    }
  
  cout<<"The best underdog team is "<<teams.at(count)<<" which has rank "<<ranks.at(count)<<"."<<endl;
  }
  //round 6 only 
  else{
    for(int l = 0; l < dataset.size();l++){
      if(dataset.at(l).getRoundnumber() == 6){
        
        //checks if the team in the vector is the winning team
        if(dataset.at(l).getWinningTeam() == dataset.at(l).getTeam1()){
          cout<<"The best underdog team is "<<dataset.at(l).getTeam2()<<" which has rank "<<dataset.at(l).getRank2()<<"."<<endl;
        }
        else if(dataset.at(l).getWinningTeam() == dataset.at(l).getTeam2()){
          cout<<"The best underdog team is "<<dataset.at(l).getTeam1()<<" which has rank "<<dataset.at(l).getRank1()<<"."<<endl;
          
        }
      }
    }
  }
}

// displays the underdog for each round
void option4(vector <info> &dataset){
  int x;
  cout<<"Enter a round to be evaluated: \n"<<"   Select 2 for round 2 \n"<<"   Select 3 for round 3 'Sweet 16' \n"<<"   Select 4 for round 4 'Elite 8' \n"<<"   Select 5 for round 5 'Final 4' \n"<<"   Select 6 for round 6 'Championship' \n"<<"Your choice -->  ";
  cin>>x;

  // only checks for rounds 2-6 
  if (x >= 2 && x <= 6){
    option4_2(dataset,x);
  } 
  else{
    cout << "Not part of the selection.";
  }
  
}




//////////////////////////////////////////////////////////////////////////////////////////////



// displays predictions on rounds 2-4
void option3_3(vector <info> dataset, int x,vector <string> team,vector <string> region,vector <int> rank,vector <int> sum1,vector <int> sum2,vector <int> sum3,vector <int> sum4,vector <int> sumTotal){

  // x is the round number 
  for(int o = 3; o < dataset.size(); o++){
    if(dataset.at(o).getRoundnumber()==x){
      //checks to see if the team is a winning team and stores in a vector along with the rank
      if(dataset.at(o).getTeam1()==dataset.at(o).getWinningTeam()){
        region.push_back(dataset.at(o).getRegion());
        rank.push_back(dataset.at(o).getRank1());
      }
      else if(dataset.at(o).getTeam2()==dataset.at(o).getWinningTeam()){
        region.push_back(dataset.at(o).getRegion());
        rank.push_back(dataset.at(o).getRank2());
      }
    }
  }
  //seperately storing different regions ranks 
  for (int i = 0; i<region.size();i++){
    if (region.at(i) == "West" || region.at(i) == "Greensboro"){
      sum1.push_back(rank.at(i));
    }
    if (region.at(i) == "South" || region.at(i) == "Wichita"){
      sum2.push_back(rank.at(i));
    }
    if (region.at(i) == "East" || region.at(i) == "Spokane"){
      sum3.push_back(rank.at(i));
    }
    if (region.at(i) == "Midwest" || region.at(i) == "Bridgeport"){
      sum4.push_back(rank.at(i));
    }
   } 

  //sums up each vectors elements
  int sumOf1 = accumulate(sum1.begin(),sum1.end(),0);    
  int sumOf2 = accumulate(sum2.begin(),sum2.end(),0); 
  int sumOf3 = accumulate(sum3.begin(),sum3.end(),0); 
  int sumOf4 = accumulate(sum4.begin(),sum4.end(),0); 

  //adding the sums of each vector into a new vector
  sumTotal.push_back(sumOf1);
  sumTotal.push_back(sumOf2);
  sumTotal.push_back(sumOf3);
  sumTotal.push_back(sumOf4);

  //earasing duplicate regions in the regions vector
  region.erase( unique( region.begin(), region.end() ), region.end() );
  
  string bestGuess;
  int count = 0;
  int min = sumTotal.at(0);

  //loop that picks the first rank if it has the same rank as another team
  for (int j = 0; j < sumTotal.size();j++){
    for(int s = 1; s < sumTotal.size();s++){
      if (sumTotal.at(j) < min){
        min = sumTotal.at(j);
        count = j;
        if(sumTotal.at(j) == sumTotal.at(s)){
          count = j;
        }
      }
    }
  }
  bestGuess = region.at(count);
  cout<<"The region expected to win is: "<< bestGuess <<endl;
}


//  rounds 2-4 instructions for option 3
void option3_2(vector <info> dataset, int x,vector <string> team,vector <string> region,vector <int> rank){
   
  for(int i = 0; i < dataset.size(); i++){
    // x is the round number
    if(dataset.at(i).getRoundnumber()== x){
      //checks if the ranks are bigger or smaller 
      if(dataset.at(i).getRank1() > dataset.at(i).getRank2()){
        rank.push_back(dataset.at(i).getRank2());
        team.push_back(dataset.at(i).getTeam2());
      }
      else if (dataset.at(i).getRank2() > dataset.at(i).getRank1()){
        rank.push_back(dataset.at(i).getRank1());
        team.push_back(dataset.at(i).getTeam1());
      }
      else if(dataset.at(i).getRank2() == dataset.at(i).getRank1()){
        rank.push_back(dataset.at(i).getRank1());
        team.push_back(dataset.at(i).getTeam1());
      }
    }   //vector contains ranks and teams
  }
  
  //checks if the ranks are the same
  if(rank.at(0) == rank.at(1)){
    for(int k = 3; k < dataset.size(); k++){
      if(dataset.at(k).getTeam1()== team.at(0)){
        region.push_back(dataset.at(k).getRegion());
        break;
      }
    }  //uses the first region if its a match
    cout<<"The region expected to win is: "<<region.at(0)<<endl;
  }
  else{
    //method for finding the minimum value 
    int min = rank.at(0);
    int count = 0;
    for (int j = 0; j < rank.size();j++){
      if (rank.at(j)<min){
        min = rank.at(j);
        count = j;
      }
    }
    //checks the data to see which region the team is from 
    for(int i = 5; i < dataset.size(); i++){
      if(dataset.at(i).getTeam1()== team.at(count)){
        region.push_back(dataset.at(i).getRegion());
      }
    }
      cout<<"The region expected to win is: "<<region.at(0)<<endl;
  }
} 
  /////////////////////////////////////////////////////////////////////////////

//displays match predictions based on rank
void option3(vector <info> &dataset){
  int x;
  vector <string> team,region;
  vector <int> sum1,sum2,sum3,sum4,sumTotal;    
  vector <int> rank;
  cout<<"Enter a round to be evaluated: \n"<<"   Select 2 for round 2 \n"<<"   Select 3 for round 3 'Sweet 16' \n"<<"   Select 4 for round 4 'Elite 8' \n"<<"   Select 5 for round 5 'Final 4' \n"<<"Your choice -->  ";
  cin>>x;
  cout<<"Analyzing round "<<x<<"..."<<endl<<endl;

  //checking through rounds 2-5
  if(x == 5){
    option3_2(dataset,x,team,region,rank);
  }
  else if(x>= 2 || x <= 4){
    option3_3(dataset,x,team,region,rank,sum1,sum2,sum3,sum4,sumTotal);
  }
  else{
    cout<<"Invalid entry";
  }
}
        
//////////////////////////////////////////////////////////////////////////////////////////////

//finds valid matches for specific rounds
void option5_3(vector <info> dataset,int x, vector <string> team1,vector <string> team2,vector <string> winner,vector <int> round,vector <int> game,vector <int> score){

  //adds most info from the dataset into new vectors
  for(int i = 0; i < dataset.size(); i++){
    if(dataset.at(i).getRoundnumber() == x){
      team1.push_back(dataset.at(i).getTeam1());
      team2.push_back(dataset.at(i).getTeam2());
      winner.push_back(dataset.at(i).getWinningTeam());
      round.push_back(dataset.at(i).getRoundnumber());
      game.push_back(dataset.at(i).getGameNumber());
      
      //adds the nonnegative difference of scores
      score.push_back(abs(dataset.at(i).getScore1()-dataset.at(i).getScore2()));
    }
  }

  //finding the max score
  int max = score.at(0);
  int count1 = 0;
  for (int j = 0; j < score.size();j++){
    if (score.at(j)>max){
      max = score.at(j);
      count1 = j;
    }
  }
  cout<<"The shoo-in game was: \n"<<"Round "<<x<<", Game "<<game.at(count1)<<": "<<team1.at(count1)<<" vs "<<team2.at(count1)<<". Winner: "<<winner.at(count1)<<endl<<"The difference was "<<max<<" points."<<endl<<endl;

  //finding the minimun scores
  int min = score.at(0);
  int count2 = 0;
  for (int j = 0; j < score.size();j++){
    if (score.at(j)<min){
      min = score.at(j);
      count2 = j;
    }
  }
  
  cout<<"The nail-biting game was: \n"<<"Round "<<x<<", Game "<<game.at(count2)<<": "<<team1.at(count2)<<" vs "<<team2.at(count2)<<". Winner: "<<winner.at(count2)<<endl<<"The difference was "<<min<<" points."<<endl<<endl<<endl;
}

// finds valid matches for all rounds 1-6
void option5_2(vector <info> dataset,int x, vector <string> team1,vector <string> team2,vector <string> winner,vector <int> round,vector <int> game,vector <int> score){

  //adds most info from the dataset into new vectors
  for(int i = 1; i < dataset.size(); i++){
    team1.push_back(dataset.at(i).getTeam1());
    team2.push_back(dataset.at(i).getTeam2());
    winner.push_back(dataset.at(i).getWinningTeam());
    round.push_back(dataset.at(i).getRoundnumber());
    game.push_back(dataset.at(i).getGameNumber());

    //adds the nonnegative difference of scores
    score.push_back(abs(dataset.at(i).getScore1()-dataset.at(i).getScore2()));
  }

  //finds the maximum score
  int max = score.at(0);
  int count1 = 0;
  for (int j = 0; j < score.size();j++){
    if (score.at(j)>max){
      max = score.at(j);
      count1 = j;
    }
  }
  cout<<"The shoo-in game was: \n"<<"Round "<<round.at(count1)<<", Game "<<game.at(count1)<<": "<<team1.at(count1)<<" vs "<<team2.at(count1)<<". Winner: "<<winner.at(count1)<<endl<<"The difference was "<<max<<" points."<<endl<<endl;

  //finds the minimum score
  int min = score.at(0);
  int count2 = 0;
  for (int j = 0; j < score.size();j++){
    if (score.at(j)<min){
      min = score.at(j);
      count2 = j;
    }
  }
  
  cout<<"The nail-biting game was: \n"<<"Round "<<round.at(count2)<<", Game "<<game.at(count2)<<": "<<team1.at(count2)<<" vs "<<team2.at(count2)<<". Winner: "<<winner.at(count2)<<endl<<"The difference was "<<min<<" points."<<endl<<endl<<endl;
  
}

// displays close and easy games
void option5(vector <info> &dataset){
  int x;
  vector <string> team1,team2,winner;
  vector <int> round,game,score,score1,score2;
  
  cout<<"Enter a round to be evaluated: \n"<<"   Select 1 for round 1 \n"<<"   Select 2 for round 2 \n"<<"   Select 3 for round 3 'Sweet 16' \n"<<"   Select 4 for round 4 'Elite 8' \n"<<"   Select 5 for round 5 'Final 4' \n"<<"   Select 6 for round 6 'Championship' \n"<<"   Select 7 for the overall tournament \n"<<"Your choice --> ";
  cin>>x;

  //chooses whether to evaluate a specific round or all rounds
  if (x == 7){
    cout<<"Analyzing the overall tournament..."<<endl<<endl;
    option5_2(dataset,x,team1,team2,winner,round,game,score);
  }
  else if(x >= 1 || x <= 6){
    cout<<"Analyzing round "<<x<<"..."<<endl<<endl;
    option5_3(dataset,x,team1,team2,winner,round,game,score);
  }
  else{
    cout<<"Invalid entry";
  }  
}
////////////////////////////////////////////////////////////////////

//instrcutions for option 6
void option6_2(vector <info> &data, vector <info> dataset){
  int correctGuesses = 0;
  int points = 0;
  int x = 0; // round number

  //checks if pridcitions for winning teams were accurate and evaluates points
  for (int i = 0; i < dataset.size(); i++){
    if(dataset.at(i).getWinningTeam()==data.at(i).getWinningTeam()){
      
      correctGuesses += 1;
      x = dataset.at(i).getRoundnumber();

      //point system calculation
      if (x == 1){points +=5; }
      else if(x == 2){ points +=10; }
      else if(x == 3){ points +=15; }
      else if(x == 4){ points += 20; }
      else if(x == 5){ points += 25; }
      else if(x == 6){ points += 30; }
    }
  }
  cout<<"You correctly predicted the winner for "<<correctGuesses<<" games."<<endl;
  cout<<"This means that you have a score of "<<points<<"."<<endl;
  if (points >= 250){
    cout<<"Great job! You could consider entering your predictions to win money!";
  } 
  else{
    cout<< "You may want to learn more about basketball to improve your predictions next year.";
  }
  
}

//display prediction accuracy
void option6(vector <info> &dataset){
  string userFile;
  vector <string> words;
  vector <info> data;
  info row;
  cout<<"Enter the name of the file with your predicted brackets: "<<endl;
  
  //reading the prediction file
  cin>>userFile;
  readFile(words,data,row,userFile); 

  //file comparisons
  option6_2(data,dataset);
  
}



int main() {
  int x ;
  int runningProgram = 1; // keeps program running 
  string userFile;
  vector <string> words;
  vector <info> data;
  info row;
 
  display1();
  cin>>userFile;

  //reads file 
  readFile(words,data,row,userFile); 

  while(runningProgram ==1){
    
    display2();
    cin>>x;
    switch(x){
      case 1: option1(data);
      break;
      case 2: option2(data);
      break;
      case 3: option3(data);
      break;
      case 4: option4(data);
      break;
      case 5: option5(data);
      break;
      case 6: option6(data);
      break;
      case 7: cout<<"Exiting program...";
              runningProgram++;
      break;
      default: cout<<"Invalid value.  Please re-enter a value from the menu options below.";
    }
  }
  return 0;
}

