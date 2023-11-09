//Song.cpp - Implementation File

// Stephen Craig
// COSC 1436 F21

#include <iostream>
#include <iomanip>
#include <sstream>
#include "Song.h"
using namespace std;

// CONSTRUCTORS are automatically called when objects are created
//    Purpose:  Initialize members so they are in a stable state - no garbage

// A constructor
Song::Song(string newTitle, string newAlbum, string newArtist,
	MusicGenre newGenre, unsigned short newMinutes, unsigned short newSeconds)
{
	setSong(newTitle, newAlbum, newArtist, newGenre, newMinutes, newSeconds);
}

// The following default constructor with no arguments is not necessary when using
// default arguments as the constructor prototype in the Song.h file does making it 
// the default constructor because a call requires no arguments if using all defaults.
// NOTE:  May only have ONE default (no argument) constructor
// Song::Song()  
// {              
//	  setSong("","","",undefined,0,0);
// }

void Song::setSong(string newTitle, string newAlbum, string newArtist, 
		 MusicGenre newGenre, unsigned short newMinutes, unsigned short newSeconds)
{
	setTitle(newTitle);
	setAlbum(newAlbum);
	setArtist(newArtist);
	setGenre(newGenre);
	setPlayingTime(newMinutes,newSeconds);
}

void Song::setTitle(string newTitle) // Note that the parameter has different name than the private
{									 // data member which is required unless using this pointer
	title = newTitle;
}

// add function definitions for setAlbum, setArtist and setGenre 

void Song::setAlbum(string newAlbum)
{
	album = newAlbum;
}

void Song::setArtist(string newArtist)
{
	artist = newArtist;
}

void Song::setGenre(MusicGenre newGenre)
{
	genre = newGenre;
}

// Note that the parameter minutes has the same name as the private data member
// Every object has a hidden pointer to itself named this
// In the code below, minutes is the new parameter value passed to the function
//    this->minutes is the private data member of the object being called
void Song::setMinutes(unsigned short minutes)
{
	if (minutes >= 0 && minutes < 60)
	{
		this->minutes = minutes;
	}
	else
	{
		this->minutes = 0;
	}
}

// add function definitions for setSeconds and setPlayingTime 

void Song::setSeconds(unsigned short newSeconds)
{
	if (newSeconds >= 0 && newSeconds <= 59)
	{
		seconds = newSeconds;
	}
	else
	{
		seconds = newSeconds = 0;
	}
}

void Song::setPlayingTime(unsigned short minutes, unsigned short seconds)
{
	setMinutes(minutes);
	setSeconds(seconds);
}

string Song::getSong() const // member functions may directly access private data members 
							//  and may call other member functions
{
	return title + "; " + album + "; " + artist + "; " + getGenre()
		    + "; " + getPlayingTime();
}

string Song::getTitle() const
{
	return title;
}

// add function definitions for getAlbum and getArtist 

string Song::getAlbum() const
{
	return album;
}

string Song::getArtist() const
{
	return artist;
}

string Song::getGenre() const
{
	switch (genre)
	{
	case MusicGenre::undefined:
		return "Undefined";
	case MusicGenre::rock:
		return "Rock";
	case MusicGenre::jazz:
		return "Jazz";
	case MusicGenre::classical:
		return "Classical";
	case MusicGenre::blues:
		return "Blues";
	case MusicGenre::pop:
		return "Pop";
	default:
		return "Genre error";
	}
}

unsigned short Song::getMinutes() const
{
	return minutes;
}

unsigned short Song::getSeconds() const
{
	return seconds;
}

// Add function definitions for getMinutes and getSeconds 

// A stringstream class object, ss, can contain the minutes and second ints as chars
//   and return them as a string class object using the .str() conversion function. 
// The setfill ostream manipulator changes the default fill character from a blank space
//    to a ‘0’ char to format the m:ss with a leading 0 for any seconds less than 10. 
string Song::getPlayingTime() const
{
	stringstream ss; 
	ss << minutes << ":" << setfill('0') << setw(2)  << seconds << setfill(' ');
	return ss.str();
}

bool Song::operator==(const Song& otherSong) const
{				
	if (title == otherSong.title && album == otherSong.album && 
	    artist == otherSong.artist && genre == otherSong.genre &&
	    getPlayingTime() == otherSong.getPlayingTime())
			return true;
	else
			return false;
}
