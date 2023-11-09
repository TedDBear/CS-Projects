// Song.h - Specification or Interface File 

// Stephen Craig
// COSC 1436 F21

#ifndef SONG_H     
#define SONG_H

#include <string>
using namespace std;

class Song
{
	// MEMBER FUNCTIONS (or operators) are usually public
	// Code only member function prototypes unless implementation is 
	//    very small - will learn inline functions in COSC 1437
	
	public: 
	enum class MusicGenre { undefined, rock, jazz, classical, blues, pop };

	// CONSTRUCTOR FUNCTION- automatically called when objects are created
	//    uses default arguments to create an object in a STABLE state
	Song(string = "", string = "", string = "", 
		 MusicGenre = MusicGenre::undefined, unsigned short = 0,unsigned short = 0);

	// MUTATOR (or transformer) MEMBER FUNCTIONS - to modify member values
	void setTitle(string newTitle);

	// add prototypes for setAlbum, setArtist and setGenre 
	void setAlbum(string newAlbum);
	void setArtist(string newArtist);
	void setGenre(MusicGenre newGenre);

	void setMinutes(unsigned short newMinutes);

	// add prototypes for setSeconds and setPlayingTime 
	void setSeconds(unsigned short newSeconds);
	void setPlayingTime(unsigned short minutes, unsigned short seconds);

	void setSong(string newTitle, string newAlbum, string newArtist, 
			     MusicGenre newGenre, unsigned short newMinutes,
				 unsigned short newSeconds);

	// ACCESSOR (or observer) MEMBER FUNCTIONS - to return member values
	// const modifier prevents function from changing member data values
	string getTitle() const;

	// add prototypes for getAlbum, getArtist and getGenre 
	string getAlbum() const;
	string getArtist() const;
	string getGenre() const;


	unsigned short getMinutes() const;

	// add prototypes for getSeconds and getPlayingTime 
	unsigned short getSeconds() const;
	string getPlayingTime() const;

	string getSong() const;

	bool operator==(const Song& otherSong) const;

    // Data Members are private, accessible only via public member functions
	private: 
		string title;
		string album;
		string artist;
		MusicGenre genre;
		unsigned short minutes;
		unsigned short seconds;
	};

#endif