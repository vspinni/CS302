//Shravan Pinni
//Anthony Sutherland 

#include <iostream>
#include <map>
#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;


//Structs for the solution format provided by Dr. Plank.
struct Song { 
   string title;
   int time;  // could also be a string
   int track;
};

struct Album {
   map <int, Song *> songs;
   string name;
   int time;
   int nsongs;  // optional variable but makes it easier
};

struct Artist {
   map <string, Album *> albums;
   string name;
   int time;
   int nsongs;
};

//This will change all underscores to just normal spaces. 
string convert(string word) {
   for (int i = 0; i < word.size(); i++) {
      if (word[i] == '_') word[i] = ' ';
   }
   return word;

}

//This will change the seconds back into the min:sec format to print at the end. 
string changeTime(int time) {
   int min, sec;
   ostringstream ss;

   min = time / 60;
   sec = time % 60;

   if (sec < 10) ss << min << ":0" << sec;
   else ss << min << ":" << sec;

   return ss.str();

}

//Main section.
int main(int argc, char **argv) {

   ifstream fs;
   string title, artist, album, genre;
   int track = 0, timeMin = 0, timeSec = 0, totalTime = 0;
   char trash; //This is to hold the colons for the times because we do not need them. 
   Song *ptrSong;
   Artist *ptrArtist;
   Album *ptrAlbum;
   
   map <string, Artist * > mapArtist;
   map <string, Artist * >::iterator ait;
   map <string, Album * >::iterator ait2;
   map <int, Song * >::iterator sit;

   //This is checking that there are the right amount of arguments. 
   if (argc != 2) {
      cerr << "bad file\n";
      return -1;
   }

   //Opens the file. 
   fs.open(argv[1]);

   //Reads the data from the file. 
   while (fs >> title >> timeMin >> trash >> timeSec >> artist >> album >> genre >> track) {

      timeMin = timeMin * 60;
      totalTime = timeMin + timeSec;

      //Removes all the underscores. 
      title = convert(title);
      artist = convert(artist);
      album = convert(album);
      genre = convert(genre);

      //Makes a new case of a song. 
      ptrSong = new Song();
      ptrSong->title = title;
      ptrSong->time = totalTime;
      ptrSong->track = track;

      //Searchs the artist map to see if the artist already exist.
      ait = mapArtist.find(artist);
      if (ait == mapArtist.end()) {
         ptrArtist = new Artist;
         ptrArtist->name = artist;
         ptrArtist->time = totalTime;
         ptrArtist->nsongs = 1;
         mapArtist.insert(make_pair(artist, ptrArtist));

	  //If the artist already exist just update the info. 
      }else {
         ptrArtist = ait->second;
         ptrArtist->time += totalTime;
         ptrArtist->nsongs++;
      }

      //seaches the album map to see if the album already exist 
      ait2 = ptrArtist->albums.find(album);
      if (ait2 == ptrArtist->albums.end()) {
         ptrAlbum = new Album;
         ptrAlbum->name = album;
         ptrAlbum->time = totalTime;
         ptrAlbum->nsongs = 1;
         ptrArtist->albums.insert(make_pair(album, ptrAlbum));

	  //If the ablum already exist updates the info.      
      }else {
         ptrAlbum = ait2->second;
         ptrAlbum->time += totalTime;
         ptrAlbum->nsongs++;
      }

      //Adds the song to the map. 
      ptrAlbum->songs.insert(make_pair(track, ptrSong));

   }


	//This is the section where everything is outputted in proper format.
	//For loop to access the map of artists.
	for (ait = mapArtist.begin(); ait != mapArtist.end(); ait++){
	
		//Temporary variables 1, 2, 3 allow me to save the time from inside the map and then use the changeTime function to put it
		//back to its proper format.
		int tmp = ait -> second -> time;

		//Output of artist.
		cout << ait -> first << ": " << ait -> second -> nsongs << ", " << changeTime(tmp) << endl;
			
		//For loop to access the map of albums.
		for (ait2 = ait -> second -> albums.begin(); ait2 != ait -> second -> albums.end(); ait2++){
			
			//Temporary variable for reason above.
			int tmp2 = ait2 -> second -> time;
			
			//Output of albums.
			cout << "        " << ait2 -> first << ": " << ait2 -> second -> nsongs << ", " << changeTime(tmp2) << endl ;
		
			//For loop to access the map of songs.
			for (sit = ait2 -> second -> songs.begin(); sit != ait2 -> second -> songs.end();sit++){
				
				//Temporary variable for reason above.
				int tmp3 = sit -> second -> time;
				//Output of songs.
				cout << "                " << sit -> second -> track << ". " << sit -> second -> title <<  ": " << changeTime(tmp3) << endl;

			}
		}

	}
	
	//Closing the file stream and clearing it.
	fs.close();
	fs.clear();

	return 0;
}
