#include <iostream>
#include "LinkedList.h"

using namespace std;

struct Song
{
	string composerName;
	string songName;

	Song()
	{
		composerName = "Unknown";
		songName = "Unknown";
	}

	Song(string composerName, string songName)
		:composerName(composerName),
		songName(songName)
	{
	}
	bool operator ==(Song songs)
	{
		if (composerName == songs.composerName && songName == songs.songName)
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}

	bool operator !=(Song songs)
	{
		if (composerName != songs.composerName || songName != songs.songName)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	friend ostream& operator <<(ostream& os, const Song song)
	{
		os << "\n" << song.composerName << ": " << song.songName << endl;

		return os;
	}
	
};

int main()
{
	LinkedList<Song> songs;
	Node<Song>* place;
	Node<Song>* anotherPlace;

	songs.insertFirst(Song("Bee Gees", "Tragedy"));
	songs.insertFirst(Song("Beatles", "All My Loving"));
	songs.insertFirst(Song("Elvis Presley", "Kentucky Rain"));

	LinkedList<Song> songs1;

	songs1.insertFirst(Song("Bee Gees", "Tragedy"));
	songs1.insertFirst(Song("Beatles", "All My Loving"));
	songs1.insertFirst(Song("Elvis Presley", "Kentucky Rain"));

	songs.merge(songs, songs1);

	cout << "Initial List: " << endl;

	songs.print();

	cout << "\n\"Bee Gees, Tragedy\" is in this list: " << boolalpha 
		 << songs.search(Song("Bee Gees", "Tragedy")) << endl;

	place = songs.getNode(1);

	songs.insertAfter(place, Song("Michael Jackson", "Smooth Criminal"));

	cout << "\n\nNew item added to the list: ";
	cout << "\"" << songs.getNode(2)->data.composerName << ": " << songs.getNode(2)->data.songName << "\"" << endl;

	anotherPlace = songs.getNode(2);

	songs.swap(place, anotherPlace);

	cout << "\n\nUpdated List: " << endl;

	songs.print();

	songs.deleteNodeWithData(Song("Beatles", "All My Loving"));

	cout << "\n\nList after deleting the 3rd node: " << endl;

	songs.print();

	return 0;
}