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

//this will change all underscores to just normal spaces 
string convert(string word) {
   for (int i = 0; i < word.size(); i++) {
      if (word[i] == '_') word[i] = ' ';
   }
   return word;

}

//this will make all the times into strings to add to file 
string changeTime(int time) {
   int min, sec;
   ostringstream ss;

   min = time / 60;
   sec = time % 60;

   if (sec < 10) ss << min << ":0" << sec;
   else ss << min << ":" << sec;

   return ss.str();

}

int main(int argc, char **argv) {

   ifstream fs;
   string title, artist, album, genre;
   int track = 0, timeMin = 0, timeSec = 0, totalTime = 0;
   char trash; //this is to hold the colons for the times because we do not need them 
   Song *ptrSong;
   Artist *ptrArtist;
   Album *ptrAlbum;
   map <string, Artist * > mapArtist;
   map <string, Artist * >::iterator ait;
   map <string, Album * >::iterator ait2;
   map <int, Song * >::iterator sit;

   //this is checking that there are the right amount of agruments 
   if (argc != 2) {
      cerr << "bad file\n";
      return -1;
   }

   //open the file 
   fs.open(argv[1]);

   //reads the data from the file 
   while (fs >> title >> timeMin >> trash >> timeSec >> artist >> album >> genre >> track) {

      timeMin = timeMin * 60;
      totalTime = timeMin + timeSec;

      //removes all the underscores 
      title = convert(title);
      artist = convert(artist);
      album = convert(album);
      genre = convert(genre);

      //makes a new case of a song 
      ptrSong = new Song();
      ptrSong->title = title;
      ptrSong->time = totalTime;
      ptrSong->track = track;

      //searchs the artist map to see if the artist already exist
      ait = mapArtist.find(artist);
      if (ait == mapArtist.end()) {
         ptrArtist = new Artist;
         ptrArtist->name = artist;
         ptrArtist->time = totalTime;
         ptrArtist->nsongs = 1;
         mapArtist.insert(make_pair(artist, ptrArtist));

         //if the artist already exist just update the info 
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

         //if the ablum already exist updates the info         
      }else {
         ptrAlbum = ait2->second;
         ptrAlbum->time += totalTime;
         ptrAlbum->nsongs++;
      }

      //adds the song to the map 
      ptrAlbum->songs.insert(make_pair(track, ptrSong));

   }

   //this is where the output needs to format the song titles and everything
   fs.close();
   fs.clear();

   return 0;
}
