// PA10 Song Class Client.cpp File

// Stephen Craig
// COSC 1436 F21

#include <iostream>
#include <iomanip>
#include <string>
#include "Song.h"
#include "MyLibrarySC.h"
using namespace std; // include library files for readInt function or add code for it

int main()
{
	const int NUMB_SONGS = 3;

	Song songList[NUMB_SONGS] = {
		// fully initialized Song
		Song("Purple Rain", "Purple Rain", "Prince", Song::MusicGenre::pop,8,44), 
		// partially initialized Song
		Song("Hand In My Pocket", "Jagged Little Pill", "Alanis Morissette"),	
		// note that the 3rd Song is uninitialized
	}; 

	cout << "\nSONG CLASS PROGRAM TEST CLIENT:\n";

	// display content of songList array
	for (int i = 0; i < NUMB_SONGS; i++)
	{
		cout << "\nSong #" << i+1 <<": " << songList[i].getSong() << endl;
	}
	
	int tempInt;   // variables used to store information for a new Song object
	string tempString;
	Song newSong;
	
	while (true)
	{
		// test set member functions
		cout << "\n\nEnter the title of a 4th new song: ";
		getline(cin, tempString);
		newSong.setTitle(tempString);

		cout << "\nWhat album is it on? ";
		getline(cin, tempString);
		newSong.setAlbum(tempString);

		cout << "\nWho is the artist? ";
		getline(cin, tempString);
		newSong.setArtist(tempString);

		cout << "\nWhat music genre is it?\n";
		cout << "\t1. Rock" << endl;
		cout << "\t2. Jazz" << endl;
		cout << "\t3. Classical" << endl;
		cout << "\t4. Blues" << endl;
		cout << "\t5. Pop" << endl;
		tempInt = readInt("Pick a genre:", 1, 5);
		newSong.setGenre(static_cast<Song::MusicGenre>(tempInt));

		cout << "\nHow long is this song? " << endl;
		cout << "\tMinutes: ";
		int min = readInt("\tMinutes:");
		cout << "\tSeconds: ";
		int sec = readInt("\tSeconds:");
		newSong.setPlayingTime(min, sec);

		cout << endl << endl;

		// Test get member functions
		cout << "The new 4th song information:\n";
		cout << "Song Title: " << newSong.getTitle() << endl;
		cout << "Album Name: " << newSong.getAlbum() << endl;
		cout << "Artist Name: " << newSong.getArtist() << endl;
		cout << "Genre: " << newSong.getGenre() << endl;
		cout << "Time: " << newSong.getPlayingTime() << endl;

		// Test == member function
		cout << "\n\nCheck if class objects are equivalent.\n\n"
			<< "Does the first song == the new song?  ";
		if (songList[0] == newSong)
			cout << "Yes, the songs are equal\n";
		else
			cout << "No, the songs are not equal\n";

		cout << "\nAssign the first Song to the new Song"
			<< " and then check equivalency.\n\n";
		newSong = songList[0];

		cout << "Does the first song == the new song?  "
			<< boolalpha << (songList[0] == newSong) << "\n";
	}

	cout << "\nProgram Ended.\n";
	system("pause");
	return 0;
}
